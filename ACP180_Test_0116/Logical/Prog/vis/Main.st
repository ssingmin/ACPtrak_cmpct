PROGRAM _INIT 
    (* Size of Vis structure - this value has to be entered in B&R scene viewer (PVI -> Options -> Size) *)
	SizeOfVis := SIZEOF(Vis);
	(* Maximum number of displayed shuttles *) 
	VisShuttleCnt := SIZEOF(Vis.Shuttle) / SIZEOF(Vis.Shuttle[0]);
END_PROGRAM

PROGRAM _CYCLIC 
	FOR i := 0 TO (VisShuttleCnt - 1) DO 
		IF gShuttleMon.Shuttle[i].Available THEN
			(* Format selected monitor data to fit B&R scene viewer. *) 
			Vis.Shuttle[i].Available     := 1;
			Vis.Shuttle[i].PositionX     := LREAL_TO_REAL(gShuttleMon.Shuttle[i].Position.X);
			Vis.Shuttle[i].PositionY     := LREAL_TO_REAL(gShuttleMon.Shuttle[i].Position.Y);
			Vis.Shuttle[i].RotationZ     := LREAL_TO_REAL(gShuttleMon.Shuttle[i].Orientation.Angle1);
			Vis.Shuttle[i].ExtentToFront := LREAL_TO_REAL(gShuttleMon.Shuttle[i].ExtentToFront);
			Vis.Shuttle[i].ExtentToBack  := LREAL_TO_REAL(gShuttleMon.Shuttle[i].ExtentToBack);
			Vis.Shuttle[i].Width         := LREAL_TO_REAL(gShuttleMon.Shuttle[i].Width);  
			brsitoa(gShuttleMon.Shuttle[i].Index, ADR(Vis.Shuttle[i].Text));
            
			(* Color is defined with RGB values between 0 and 1. The default shuttle color is gray. *)
			Vis.Shuttle[i].ColorRed      := 0.5; 
			Vis.Shuttle[i].ColorGreen    := 0.5; 
			Vis.Shuttle[i].ColorBlue     := 0.5;
            
			(* Example: Set shuttle colour via user data. *)
			IF gShuttleMon.Shuttle[i].UserData <> 0 THEN  
				(* Set access to user data of this shuttle. *)
				UserData ACCESS gShuttleMon.Shuttle[i].UserData;
                
				(* Set RGB values for specific colors. *)
				IF UserData.Color = ORANGE THEN 
					Vis.Shuttle[i].ColorRed     := 1.000;
					Vis.Shuttle[i].ColorGreen   := 0.5451;
					Vis.Shuttle[i].ColorBlue    := 0.000;
				ELSIF UserData.Color = GREEN THEN
					Vis.Shuttle[i].ColorRed     := 0.000;
					Vis.Shuttle[i].ColorGreen   := 1.000;
					Vis.Shuttle[i].ColorBlue    := 0.000;
				ELSIF UserData.Color = RED THEN
					Vis.Shuttle[i].ColorRed     := 1.000;
					Vis.Shuttle[i].ColorGreen   := 0.000;
					Vis.Shuttle[i].ColorBlue    := 0.000;
				ELSIF UserData.Color = BLUE THEN
					Vis.Shuttle[i].ColorRed     := 0.000;
					Vis.Shuttle[i].ColorGreen   := 0.000;
					Vis.Shuttle[i].ColorBlue    := 1.000;
				ELSIF UserData.Color = WHITE THEN
					Vis.Shuttle[i].ColorRed     := 1.000;
					Vis.Shuttle[i].ColorGreen   := 1.000;
					Vis.Shuttle[i].ColorBlue    := 1.000;
				END_IF  
			END_IF
		ELSE
			(* If the selected shuttle is not available, it will be invisible in the Scene Viewer. *)
			brsmemset(ADR(Vis.Shuttle[i]), 0, SIZEOF(Vis.Shuttle[0]));
		END_IF
	END_FOR
END_PROGRAM

