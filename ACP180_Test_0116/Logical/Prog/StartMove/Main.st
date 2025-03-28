PROGRAM _INIT
    (* Initialize parameters for shuttle movements. *)
	gTrakAsm.Parameter.Velocity := 1.0;
	gTrakAsm.Parameter.Acceleration := 10.0;
	gTrakAsm.Parameter.Deceleration := 10.0;
    
	(* Write this value into the size of user data in the shuttle stereotype configuration. *)
	UserDataSize := SIZEOF(gShuttleUserData);

	(* Set the assembly reference for all assembly function blocks. *)
	MC_BR_AsmPowerOn_AcpTrak_0.Assembly     := ADR(gAssembly_1);
	MC_BR_AsmPowerOff_AcpTrak_0.Assembly    := ADR(gAssembly_1);
	MC_BR_AsmStop_AcpTrak_0.Assembly        := ADR(gAssembly_1);
	MC_BR_AsmGetShuttle_AcpTrak_0.Assembly  := ADR(gAssembly_1);
	MC_BR_AsmReadStatus_AcpTrak_0.Assembly  := ADR(gAssembly_1);
	MC_BR_AsmReset_AcpTrak_0.Assembly       := ADR(gAssembly_1);

	(* Enable reading of current status of the assembly. *)
	MC_BR_AsmReadStatus_AcpTrak_0.Enable := TRUE;

	(* Initialize constant parameters for routed moves. *)
	MC_BR_RoutedMoveVel_AcpTrak_0.Sector        := ADR(SectorTrackA);
	MC_BR_RoutedMoveVel_AcpTrak_0.Jerk          := 0.0;
	MC_BR_RoutedMoveVel_AcpTrak_0.BufferMode    := mcABORTING;
	MC_BR_RoutedMoveVel_AcpTrak_0.AdvancedParameters.StartDirection     := mcDIR_UNDEFINED;
	MC_BR_RoutedMoveVel_AcpTrak_0.AdvancedParameters.EndDirection       := mcDIR_POSITIVE;
	MC_BR_RoutedMoveVel_AcpTrak_0.AdvancedParameters.ShuttleOrientation := mcDIR_UNDEFINED;

	(* Initialize constant parameter for assembly stop command. *)
//	MC_BR_AsmStop_AcpTrak_0.AdvancedParameters.StopMode := mcSTOPMODE_JERK_LIMIT;
END_PROGRAM

PROGRAM _CYCLIC
	
	gRotary;
	
	
	IF gTrakAsm.Status.ErrorStop THEN
		Step := ERROR;
	END_IF

	CASE Step OF
    
		(* Power off assembly and wait for power on command *)
		POWER_OFF:
			(* Assembly is already powered off. *)
			IF gTrakAsm.Status.Disabled THEN
				Step := POWERED_OFF;
			ELSE
				MC_BR_AsmPowerOff_AcpTrak_0.Execute := TRUE;
				Step := WAIT_POWER_OFF;
			END_IF

			(* The assembly is being powered off. *)
		WAIT_POWER_OFF:
			(* Power off is done. *)
			IF MC_BR_AsmPowerOff_AcpTrak_0.Done THEN
				MC_BR_AsmPowerOff_AcpTrak_0.Execute := FALSE;
				Step := POWERED_OFF;
			ELSIF MC_BR_AsmPowerOff_AcpTrak_0.Error THEN
				Step := ERROR;
			END_IF

			(* The assembly is powered off, wait for a command to power it on. *)
		POWERED_OFF:
			(* The assembly is to be powered on. *)
			IF gTrakAsm.Command.Power THEN 
				Step := POWER_ON;
			END_IF

			(* Power on assembly *)
		POWER_ON:
			MC_BR_AsmPowerOn_AcpTrak_0.Execute := TRUE;
			Step := WAIT_POWER_ON;

			(* The assembly is being powered on. *)
		WAIT_POWER_ON:
			(* Assembly is not yet powered on. *)
			IF MC_BR_AsmPowerOn_AcpTrak_0.Done THEN
				MC_BR_AsmPowerOn_AcpTrak_0.Execute := FALSE;
                
				(* Store the shuttles in the shuttle array. On real hardware, the set of shuttles might have changed. *)
				CurrentShuttleNumber := 1;
				brsmemset(ADR(ShuttleReferences), 0, SIZEOF(ShuttleReferences));
				Step := GET_SHUTTLE;
			ELSIF MC_BR_AsmPowerOn_AcpTrak_0.Error THEN
				Step := ERROR;
			END_IF

			(* Get all shuttles on the assembly (those physically available on the real hardware or the added ones in the simulation, resp.). *)
		GET_SHUTTLE:
			MC_BR_AsmGetShuttle_AcpTrak_0.Enable := TRUE;

			IF MC_BR_AsmGetShuttle_AcpTrak_0.Valid THEN
				(* There are no shuttles on the assembly. *)
				IF MC_BR_AsmGetShuttle_AcpTrak_0.TotalCount = 0 THEN
					gTrakAsm.ShuttleCnt := 0;
					MC_BR_AsmGetShuttle_AcpTrak_0.Enable := FALSE;
					MC_BR_AsmGetShuttle_AcpTrak_0.Next := FALSE;

					Step := READY;
                (* As soon as the next shuttle has been output by the function block, RemainingCount
                   is reduced and this condition becomes true. *)
				ELSIF (MC_BR_AsmGetShuttle_AcpTrak_0.RemainingCount <> (MC_BR_AsmGetShuttle_AcpTrak_0.TotalCount - CurrentShuttleNumber)) THEN
					CurrentShuttleNumber := CurrentShuttleNumber + 1;
					MC_BR_AsmGetShuttle_AcpTrak_0.Next := FALSE;
				ELSE
					(* Store all axis references in an array for global movement commands. *)
					ShuttleReferences[CurrentShuttleNumber] := MC_BR_AsmGetShuttle_AcpTrak_0.Axis;
					(* Get next shuttle reference with positive edge on .Next. *)
					MC_BR_AsmGetShuttle_AcpTrak_0.Next := TRUE;
                
					(* All shuttles have been stored. *)
					IF (MC_BR_AsmGetShuttle_AcpTrak_0.RemainingCount = 0) THEN
						gTrakAsm.ShuttleCnt := MC_BR_AsmGetShuttle_AcpTrak_0.TotalCount;
						MC_BR_AsmGetShuttle_AcpTrak_0.Enable := FALSE;
						MC_BR_AsmGetShuttle_AcpTrak_0.Next := FALSE;
                        
						Step := READY;
					END_IF
				END_IF
			END_IF

			(* Assembly is active and ready for movement. *)
		READY:
			(* Power off the assembly. *)
			IF NOT gTrakAsm.Command.Power THEN 
				Step := POWER_OFF;
				(* Wait for movement command if shuttles are present. *)
			ELSIF gTrakAsm.Command.ShuttleStart AND gTrakAsm.ShuttleCnt > 0 THEN 
				gTrakAsm.Command.ShuttleStart := FALSE;
				CurrentShuttleNumber := 1;
				Step := START_MOVEMENT;
			END_IF
    
			(* Move all shuttles on assembly to the same target position with the same velocity. *)
			(* Used for startup to accelerate all shuttles to an initial velocity in order to
			pass the first process-point. *)
		START_MOVEMENT:
			IF CurrentShuttleNumber <= gTrakAsm.ShuttleCnt THEN 
				MC_BR_RoutedMoveVel_AcpTrak_0.Axis          := ADR(ShuttleReferences[CurrentShuttleNumber]);
				MC_BR_RoutedMoveVel_AcpTrak_0.Position      := 0.3 + gTrakAsm.ShuttleCnt * 0.15;
				MC_BR_RoutedMoveVel_AcpTrak_0.Velocity      := gTrakAsm.Parameter.Velocity;
				MC_BR_RoutedMoveVel_AcpTrak_0.RouteVelocity := gTrakAsm.Parameter.Velocity;
				MC_BR_RoutedMoveVel_AcpTrak_0.Acceleration  := gTrakAsm.Parameter.Acceleration;
				MC_BR_RoutedMoveVel_AcpTrak_0.Deceleration  := gTrakAsm.Parameter.Deceleration;
				MC_BR_RoutedMoveVel_AcpTrak_0.Execute       := TRUE;
                
				Step := WAIT_START_MOVEMENT;
			ELSE
				Step := MOVING;
			END_IF

			(* Wait until a shuttle movement is active. *)
		WAIT_START_MOVEMENT:
			IF MC_BR_RoutedMoveVel_AcpTrak_0.Active THEN
				MC_BR_RoutedMoveVel_AcpTrak_0.Execute := FALSE;
				CurrentShuttleNumber := CurrentShuttleNumber + 1;
				Step := START_MOVEMENT;
				(* There is invalid speed or acceleration setting or shuttle caused an error stop. *)
			ELSIF MC_BR_RoutedMoveVel_AcpTrak_0.Error THEN
				Step := ERROR;
			END_IF

			(* A movement has been started for all shuttles. *)
		MOVING:
			(* Wait for Stop command. *)
			IF gTrakAsm.Command.ShuttleStop THEN
				gTrakAsm.Command.ShuttleStop := FALSE;
				Step := STOPPING;
			END_IF

			(* Stop all shuttles with specified deceleration at their current locations. *)
		STOPPING:
			MC_BR_AsmStop_AcpTrak_0.Execute := TRUE;
			Step := WAIT_STOPPING;

			(* Wait until all shuttles are stopped. *)
		WAIT_STOPPING:
			IF MC_BR_AsmStop_AcpTrak_0.Done THEN
				MC_BR_AsmStop_AcpTrak_0.Execute := FALSE;
				Step := READY;
				(* A shuttle caused an error stop. *)
			ELSIF MC_BR_AsmStop_AcpTrak_0.Error THEN
				Step := ERROR;
			END_IF

			(* An error occured on the assembly. *)
		ERROR:
			(* Wait for the user to trigger the error reset. *)
			IF gTrakAsm.Command.Reset THEN
				gTrakAsm.Command.Reset := FALSE;
				MC_BR_AsmReset_AcpTrak_0.Execute := TRUE;
				Step := RESET;
			END_IF

			(* Reset assembly due to an error. *)
		RESET:
			IF MC_BR_AsmReset_AcpTrak_0.Done THEN
				gTrakAsm.Command.ShuttleStart           := FALSE;
				gTrakAsm.Command.ShuttleStop            := FALSE;
				MC_BR_AsmReset_AcpTrak_0.Execute        := FALSE;
				MC_BR_AsmPowerOn_AcpTrak_0.Execute      := FALSE;
				MC_BR_AsmPowerOff_AcpTrak_0.Execute     := FALSE;
				MC_BR_AsmStop_AcpTrak_0.Execute         := FALSE;
				MC_BR_RoutedMoveVel_AcpTrak_0.Execute   := FALSE;
                
				Step := READY;
			END_IF
	END_CASE

	(* Read assembly status cyclically to assembly interface. *)
	gTrakAsm.Status.Disabled  := MC_BR_AsmReadStatus_AcpTrak_0.AssemblyDisabled;
	gTrakAsm.Status.Ready     := MC_BR_AsmReadStatus_AcpTrak_0.AssemblyReady;
	gTrakAsm.Status.Homing    := MC_BR_AsmReadStatus_AcpTrak_0.AssemblyHoming;
	gTrakAsm.Status.Stopping  := MC_BR_AsmReadStatus_AcpTrak_0.AssemblyStopping;
	gTrakAsm.Status.ErrorStop := MC_BR_AsmReadStatus_AcpTrak_0.AssemblyErrorStop;

	(* Cyclic function blocks calls *)
	MC_BR_AsmPowerOn_AcpTrak_0();
	MC_BR_AsmGetShuttle_AcpTrak_0();
	MC_BR_AsmPowerOff_AcpTrak_0();
	MC_BR_AsmStop_AcpTrak_0();
	MC_BR_RoutedMoveVel_AcpTrak_0();
	MC_BR_AsmReadStatus_AcpTrak_0();
	MC_BR_AsmReset_AcpTrak_0();
END_PROGRAM