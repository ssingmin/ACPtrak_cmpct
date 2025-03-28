
PROGRAM _INIT
	(* Insert code here *)
	
	gRotary.par.Acceleration := 10;
	gRotary.par.Deceleration := 10;
	gRotary.par.Velocity := 1.5;
	
	MpAxisBasicPar.Acceleration := gRotary.par.Acceleration;
	MpAxisBasicPar.Deceleration := gRotary.par.Deceleration;
	MpAxisBasicPar.Velocity := gRotary.par.Velocity;
	
	fbMpAxisBasic.MpLink := ADR(gAxis_1);
	fbMpAxisBasic.Parameters := ADR(MpAxisBasicPar);
	fbMpAxisBasic.Enable := TRUE;
	fbMpAxisBasic();
	

	
END_PROGRAM

PROGRAM _CYCLIC
	(* Insert code here *)
 
	MpAxisBasicPar.Acceleration := gRotary.par.Acceleration;
	MpAxisBasicPar.Deceleration := gRotary.par.Deceleration;
	MpAxisBasicPar.Velocity := gRotary.par.Velocity;
	
	fbMpAxisBasic.Power := gRotary.cmd.Power;
	fbMpAxisBasic.Update := gRotary.cmd.Update;
	fbMpAxisBasic.Home := gRotary.cmd.Home;
	fbMpAxisBasic.MoveVelocity := gRotary.cmd.MoveVelocity;
	fbMpAxisBasic.ErrorReset := gRotary.cmd.ErrorReset;
	
	gRotary.sts.InPosition := fbMpAxisBasic.InPosition;
	gRotary.sts.PowerOn := fbMpAxisBasic.PowerOn;
	gRotary.sts.Position := fbMpAxisBasic.Position;
	gRotary.sts.Velocity := fbMpAxisBasic.Velocity;
	gRotary.sts.IsHomed := fbMpAxisBasic.IsHomed;
	gRotary.sts.InVelocity := fbMpAxisBasic.InVelocity;
	gRotary.sts.MoveActive := fbMpAxisBasic.MoveActive;
	gRotary.sts.Info := fbMpAxisBasic.Info;
	
	fbMpAxisBasic();
END_PROGRAM

PROGRAM _EXIT
	(* Insert code here *)
	 fbMpAxisBasic(Enable := FALSE);
END_PROGRAM

