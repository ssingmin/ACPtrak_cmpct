/* Automation Studio generated header file */
/* Do not edit ! */
/* MpAxis 5.26.1 */

#ifndef _MPAXIS_
#define _MPAXIS_
#ifdef __cplusplus
extern "C" 
{
#endif
#ifndef _MpAxis_VERSION
#define _MpAxis_VERSION 5.26.1
#endif

#include <bur/plctypes.h>

#ifndef _BUR_PUBLIC
#define _BUR_PUBLIC
#endif

#ifdef _SG4
#include <McAxis.h> 
#include <MpBase.h> 
#include <McBase.h>
#endif
 
#ifdef _SG3
#include <McAxis.h> 
#include <MpBase.h> 
#include <McBase.h>
#endif
 
#ifdef _SGC
#include <McAxis.h> 
#include <MpBase.h> 
#include <McBase.h>
#endif

/* Datatypes and datatypes of function blocks */
typedef enum MpAxisErrorEnum
{	mcAXIS_NO_ERROR = 0,
	mcAXIS_ERR_PLC_OPEN = -1067278080,
	mcAXIS_WRN_PLC_OPEN = -2141019903,
	mcAXIS_WRN_MULTIPLE_COMMAND = -2141019902,
	mcAXIS_ERR_RECOVERY_NOT_ALLOWED = -1067278072,
	mcAXIS_WRN_RESTOREPOS_INVALID = -2141019895,
	mcAXIS_ERR_ACTIVATION = -1064239103,
	mcAXIS_ERR_MPLINK_NULL = -1064239102,
	mcAXIS_ERR_MPLINK_INVALID = -1064239101,
	mcAXIS_ERR_MPLINK_CHANGED = -1064239100,
	mcAXIS_ERR_MPLINK_CORRUPT = -1064239099,
	mcAXIS_ERR_MPLINK_IN_USE = -1064239098,
	mcAXIS_ERR_PAR_NULL = -1064239097
} MpAxisErrorEnum;

typedef enum MpAxisGetCamPositionModeEnum
{	mcAXIS_GET_CAM_POSITION_SLAVE,
	mcAXIS_GET_CAM_POSITION_MASTER,
	mcAXIS_MOVE_CAM_POSITION_SLAVE
} MpAxisGetCamPositionModeEnum;

typedef enum MpAxisSequenceSetModeEnum
{	mcAXIS_CAM_SEQ_SET_INACTIVE,
	mcAXIS_CAM_SEQ_SET_ON_UPDATE,
	mcAXIS_CAM_SEQ_SET_ON_START
} MpAxisSequenceSetModeEnum;

typedef enum MpAxisExecutingCmdEnum
{	mcAXIS_CMD_IDLE = 0,
	mcAXIS_CMD_HOMING,
	mcAXIS_CMD_STOP,
	mcAXIS_CMD_HALT,
	mcAXIS_CMD_MOVE_VELOCITY,
	mcAXIS_CMD_MOVE_ABSOLUTE,
	mcAXIS_CMD_MOVE_ADDITIVE,
	mcAXIS_CMD_JOG_POSITIVE,
	mcAXIS_CMD_JOG_NEGATIVE,
	mcAXIS_CMD_REMOTE_CONTROL,
	mcAXIS_CMD_ERROR_RESET,
	mcAXIS_CMD_GEAR,
	mcAXIS_CMD_CAM,
	mcAXIS_CMD_GEAR_IN_POS,
	mcAXIS_CMD_OFFSET_SHIFT,
	mcAXIS_CMD_PHASE_SHIFT,
	mcAXIS_CMD_GET_CAM_POSITION,
	mcAXIS_CMD_CAM_PREPARE,
	mcAXIS_CMD_CAM_RECOVERY,
	mcAXIS_CMD_CAM_SEQUENCE,
	mcAXIS_CMD_PARLOCK,
	mcAXIS_CMD_GET_SEQUENCE,
	mcAXIS_CMD_SET_SEQUENCE,
	mcAXIS_CMD_SIMULATION,
	mcAXIS_CMD_STOP_AT_POSITION,
	mcAXIS_CMD_POWER,
	mcAXIS_CMD_AUTOTUNE,
	mcAXIS_CMD_MOVE_CYCLIC_POSITION,
	mcAXIS_CMD_MOVE_CYCLIC_VELOCITY,
	mcAXIS_CMD_VELOCITY_CONTROL,
	mcAXIS_CMD_TORQUE_CONTROL,
	mcAXIS_CMD_TORQUE_FF
} MpAxisExecutingCmdEnum;

typedef enum MpAxisCamStartModeEnum
{	mcAXIS_CAM_START_ENTER_CAM,
	mcAXIS_CAM_START_RESTART
} MpAxisCamStartModeEnum;

typedef enum MpAxisAutoTuneModeEnum
{	mcAXIS_TUNE_AUTOMATIC,
	mcAXIS_TUNE_SPEED,
	mcAXIS_TUNE_POSITION,
	mcAXIS_TUNE_TEST,
	mcAXIS_TUNE_LOOP_FILTER,
	mcAXIS_TUNE_FEED_FORWARD
} MpAxisAutoTuneModeEnum;

typedef enum MpAxisAutoTuneLoopFilterModeEnum
{	mcAXIS_TUNE_LOOP_FILTER_F1,
	mcAXIS_TUNE_LOOP_FILTER_F1_F2,
	mcAXIS_TUNE_LOOP_FILTER_F1_F2_F3
} MpAxisAutoTuneLoopFilterModeEnum;

typedef enum MpAxisMoveCyclicVelocityModeEnum
{	mcAXIS_MCV_MODE_MOVE_CYC_VEL,
	mcAXIS_MCV_MODE_MOVE_VEL_CTRL
} MpAxisMoveCyclicVelocityModeEnum;

typedef struct MpAxisHomingAddTorqLimParType
{	float PositiveDirection;
	float NegativeDirection;
} MpAxisHomingAddTorqLimParType;

typedef struct MpAxisHomingOptionsType
{	float StartVelocity;
	float HomingVelocity;
	float Acceleration;
	enum McDirectionEnum SwitchEdge;
	enum McDirectionEnum StartDirection;
	enum McDirectionEnum HomingDirection;
	enum McSwitchEnum ReferencePulse;
	enum McSwitchEnum KeepDirection;
	float ReferencePulseBlockingDistance;
	float TorqueLimit;
	float BlockDetectionPositionError;
	float PositionErrorStopLimit;
	unsigned long RestorePositionVariableAddress;
	enum McSwitchEnum DriveSpecificHoming;
	signed char DriveSpecificHomingMode;
	double SensorOffset;
	enum McDirectionEnum SensorOffsetDirection;
	enum McSwitchEnum DisableRestorePositionOnEnable;
	struct MpAxisHomingAddTorqLimParType AdditionalTorqueLimit;
} MpAxisHomingOptionsType;

typedef struct MpAxisHomingType
{	enum McHomingModeEnum Mode;
	double Position;
	struct MpAxisHomingOptionsType Options;
} MpAxisHomingType;

typedef struct MpAxisJogLimitPositionType
{	double FirstPosition;
	double LastPosition;
} MpAxisJogLimitPositionType;

typedef struct MpAxisJogType
{	float Velocity;
	float Acceleration;
	float Deceleration;
	struct MpAxisJogLimitPositionType LimitPosition;
	float Jerk;
} MpAxisJogType;

typedef struct MpAxisStopAtPositionType
{	plcbit Activate;
	float Deceleration;
	double Position;
} MpAxisStopAtPositionType;

typedef struct MpAxisStopType
{	float Deceleration;
	float Jerk;
	struct MpAxisStopAtPositionType StopAtPosition;
} MpAxisStopType;

typedef struct MpAxisLimitLoadType
{	float Load;
	enum McDirectionEnum Direction;
} MpAxisLimitLoadType;

typedef struct MpAxisAutoTuneOptionsType
{	float MaxProportionalGain;
	enum McAcpAxLoopFilterModeEnum SpeedTuneLoopFilter1Mode;
	enum McAcpAxFilterTimeModeEnum SpeedTuneFilterTmeMode;
} MpAxisAutoTuneOptionsType;

typedef struct MpAxisAutoTuneFFOptionsType
{	enum McAcpAxAutoTuneFeedFwdModeEnum Mode;
	enum McDirectionEnum Direction;
	float MaxVelocityPercent;
	float Acceleration;
} MpAxisAutoTuneFFOptionsType;

typedef struct MpAxisAutoTuneType
{	enum MpAxisAutoTuneModeEnum Mode;
	enum McAcpAxAutoTuneOrientationEnum Orientation;
	float MaxCurrentPercent;
	double MaxDistance;
	double MaxPositionError;
	plcbit SaveControllerSettings;
	enum MpAxisAutoTuneLoopFilterModeEnum LoopFilterMode;
	struct MpAxisAutoTuneOptionsType Options;
	struct MpAxisAutoTuneFFOptionsType FeedForward;
} MpAxisAutoTuneType;

typedef struct MpAxisBasicParType
{	double Position;
	double Distance;
	float Velocity;
	float Acceleration;
	float Deceleration;
	enum McDirectionEnum Direction;
	struct MpAxisHomingType Homing;
	struct MpAxisJogType Jog;
	struct MpAxisStopType Stop;
	struct MpAxisLimitLoadType LimitLoad;
	struct MpAxisAutoTuneType AutoTune;
	float Jerk;
} MpAxisBasicParType;

typedef struct MpAxisStatusIDType
{	enum MpAxisErrorEnum ID;
	enum MpComSeveritiesEnum Severity;
	unsigned short Code;
} MpAxisStatusIDType;

typedef struct MpAxisInternalType
{	signed long ID;
	enum MpComSeveritiesEnum Severity;
	enum MpComFacilitiesEnum Facility;
	unsigned short Code;
} MpAxisInternalType;

typedef struct MpAxisDiagExtType
{	struct MpAxisStatusIDType StatusID;
	struct MpAxisInternalType Internal;
	enum MpAxisExecutingCmdEnum ExecutingCommand;
} MpAxisDiagExtType;

typedef struct MpAxisBasicInfoType
{	plcbit CommunicationReady;
	plcbit ReadyToPowerOn;
	plcbit Simulation;
	plcbit Jogging;
	plcbit JogLimitReached;
	plcbit LimitLoadActive;
	enum McAxisPLCopenStateEnum PLCopenState;
	struct McDigitalInputStatusType DigitalInputsStatus;
	struct MpAxisDiagExtType Diag;
	struct McLibraryInfoType LibraryInfo;
	enum McCommunicationStateEnum CommunicationState;
	unsigned long StartupCount;
	plcbit AutoTuneDone;
	float AutoTuneQuality;
	struct McHardwareInfoType HardwareInfo;
	enum McAutoTuneStateEnum AutoTuneState;
	enum McMechDevCompStateEnum MechDeviationCompState;
} MpAxisBasicInfoType;

typedef struct MpAxisOffsetParType
{	double Shift;
	float Velocity;
	float Acceleration;
	struct McAdvOffsetParType Options;
	plcbit CmdIndependentActivation;
} MpAxisOffsetParType;

typedef struct MpAxisPhasingParType
{	double Shift;
	float Velocity;
	float Acceleration;
	struct McAdvPhasingParType Options;
	plcbit CmdIndependentActivation;
} MpAxisPhasingParType;

typedef struct MpAxisCamInfoType
{	plcbit StandBy;
	plcbit InLeadIn;
	plcbit InCam;
	plcbit InLeadOut;
	plcbit EndOfProfile;
	plcbit DataInitialized;
} MpAxisCamInfoType;

typedef struct MpAxisGetCamPositionInfoType
{	double MasterPosition;
	double SlavePosition;
} MpAxisGetCamPositionInfoType;

typedef struct MpAxisRecoveryInfoType
{	double RestartPosition;
} MpAxisRecoveryInfoType;

typedef struct MpAxisCouplingInfoType
{	plcbit SlaveReady;
	plcbit MasterReady;
	struct MpAxisCamInfoType Cam;
	double ActualOffsetShift;
	double ActualPhaseShift;
	struct MpAxisGetCamPositionInfoType GetCamPosition;
	struct MpAxisRecoveryInfoType Recovery;
	struct MpAxisDiagExtType Diag;
	plcbit OffsetValid;
	plcbit PhasingValid;
} MpAxisCouplingInfoType;

typedef struct MpAxisGetCamPositionMoveParType
{	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	enum McDirectionEnum Direction;
} MpAxisGetCamPositionMoveParType;

typedef struct MpAxisGetCamPositionParType
{	enum MpAxisGetCamPositionModeEnum Mode;
	struct McCamDefineType Cam;
	signed long MasterFactor;
	signed long SlaveFactor;
	double MasterPosition;
	double SlavePosition;
	double MasterStartPosition;
	struct MpAxisGetCamPositionMoveParType Move;
} MpAxisGetCamPositionParType;

typedef struct MpAxisCamSequencerInfoType
{	plcbit SlaveReady;
	plcbit MasterReady;
	plcbit OffsetValid;
	double ActualOffsetShift;
	plcbit PhasingValid;
	double ActualPhaseShift;
	struct MpAxisDiagExtType Diag;
	struct MpAxisRecoveryInfoType Recovery;
	plcbit ActiveSignal1;
	plcbit ActiveSignal2;
	plcbit ActiveSignal3;
	plcbit ActiveSignal4;
} MpAxisCamSequencerInfoType;

typedef struct MpAxisCamSequenceGetType
{	enum McCamAutGetParCmdEnum Command;
	plcbit GetOnEnable;
} MpAxisCamSequenceGetType;

typedef struct MpAxisCamSequenceSetType
{	enum MpAxisSequenceSetModeEnum Mode;
	enum McCamAutSetParCmdEnum Command;
	plcbit UpdateCamList;
} MpAxisCamSequenceSetType;

typedef struct MpAxisCamSequenceDataType
{	struct McCamAutDefineType Data;
	struct MpAxisCamSequenceGetType Get;
	struct MpAxisCamSequenceSetType Set;
} MpAxisCamSequenceDataType;

typedef struct MpAxisCamListType
{	unsigned short Index;
	struct McCamDefineType Cam;
} MpAxisCamListType;

typedef struct MpAxisSequencerRecoveryParType
{	enum McCamAutPrepRestartModeEnum Mode;
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	struct McAdvCamAutPrepRestartParType Options;
	double MasterPositionOffset;
} MpAxisSequencerRecoveryParType;

typedef struct MpAxisCamSequencerParType
{	float Deceleration;
	struct MpAxisCamSequenceDataType CamSequence;
	enum McCamAutParLockCmdEnum ParLockCommand;
	struct MpAxisOffsetParType Offset;
	struct MpAxisPhasingParType Phasing;
	struct MpAxisCamListType CamList[14];
	struct MpAxisSequencerRecoveryParType Recovery;
} MpAxisCamSequencerParType;

typedef struct MpAxisGearParType
{	signed long RatioNumerator;
	signed long RatioDenominator;
	enum McValueSrcEnum MasterValueSource;
	float Acceleration;
	float Deceleration;
	float Jerk;
	struct McAdvGearInParType Options;
} MpAxisGearParType;

typedef struct MpAxisCamParType
{	unsigned short ID;
	double MasterStartPosition;
	signed long MasterScaling;
	signed long SlaveScaling;
	struct McAdvBrCamInParType Options;
	enum MpAxisCamStartModeEnum Mode;
} MpAxisCamParType;

typedef struct MpAxisGearInPosParType
{	signed long RatioNumerator;
	signed long RatioDenominator;
	enum McValueSrcEnum MasterValueSource;
	double MasterSyncPosition;
	double SlaveSyncPosition;
	enum McSyncModeEnum SyncMode;
	double MasterStartDistance;
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	struct McAdvGearInPosParType Options;
} MpAxisGearInPosParType;

typedef struct MpAxisCouplingRecoveryParType
{	enum McCamAutPrepRestartModeEnum Mode;
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	struct McAdvCamAutPrepRestartParType Options;
	double MasterPositionOffset;
} MpAxisCouplingRecoveryParType;

typedef struct MpAxisCouplingParType
{	struct MpAxisGearParType Gear;
	struct MpAxisCamParType Cam;
	struct MpAxisGearInPosParType GearInPos;
	struct MpAxisOffsetParType Offset;
	struct MpAxisPhasingParType Phasing;
	struct MpAxisGetCamPositionParType GetCamPosition;
	struct MpAxisCamListType CamList[14];
	struct MpAxisCouplingRecoveryParType Recovery;
} MpAxisCouplingParType;

typedef struct MpAxisTorqueControlInfoType
{	plcbit InTorque;
	plcbit DataInitialized;
	plcbit Ready;
	plcbit AxisLimitActive;
} MpAxisTorqueControlInfoType;

typedef struct MpAxisCyclicSetInfoType
{	plcbit AxisReady;
	struct MpAxisTorqueControlInfoType TorqueControl;
	struct MpAxisDiagExtType Diag;
} MpAxisCyclicSetInfoType;

typedef struct MpAxisMoveCyclicPositionParType
{	enum McIplModeEnum InterpolationMode;
	float Velocity;
	float Acceleration;
	float Deceleration;
	float Jerk;
	enum McSwitchEnum DisableJoltLimitation;
	enum McAltValueSrcEnum AlternativeValueSource;
} MpAxisMoveCyclicPositionParType;

typedef struct MpAxisMoveCyclicVelocityParType
{	enum MpAxisMoveCyclicVelocityModeEnum Mode;
	enum McIplModeEnum InterpolationMode;
	float Acceleration;
	float Deceleration;
	float Jerk;
	enum McSwitchEnum DisableJoltLimitation;
	enum McAltValueSrcEnum AlternativeValueSource;
} MpAxisMoveCyclicVelocityParType;

typedef struct MpAxisTorqueControlParType
{	plcbit CmdIndependentActivation;
	float TorqueResolution;
	float TorqueRamp;
	float MaximumVelocity;
	float MinimumVelocity;
	float Acceleration;
	float Jerk;
	struct McAdvBrTorqueControlParType Options;
} MpAxisTorqueControlParType;

typedef struct MpAxisTorqueFFParType
{	enum McIplModeEnum InterpolationMode;
	struct McAdvCyclicTorqueFFParType Options;
} MpAxisTorqueFFParType;

typedef struct MpAxisCyclicSetParType
{	struct MpAxisMoveCyclicPositionParType MoveCyclicPosition;
	struct MpAxisMoveCyclicVelocityParType MoveCyclicVelocity;
	struct MpAxisTorqueControlParType TorqueControl;
	struct MpAxisTorqueFFParType TorqueFeedForward;
} MpAxisCyclicSetParType;

typedef struct MpAxisBasic
{
	/* VAR_INPUT (analog) */
	struct McAxisType* MpLink;
	struct MpAxisBasicParType* Parameters;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	double Position;
	float Velocity;
	struct MpAxisBasicInfoType Info;
	/* VAR (analog) */
	struct MpComInternalDataType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ErrorReset;
	plcbit Update;
	plcbit Power;
	plcbit Home;
	plcbit MoveVelocity;
	plcbit MoveAbsolute;
	plcbit MoveAdditive;
	plcbit Stop;
	plcbit JogPositive;
	plcbit JogNegative;
	plcbit LimitLoad;
	plcbit ReleaseBrake;
	plcbit Simulate;
	plcbit AutoTune;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit UpdateDone;
	plcbit CommandBusy;
	plcbit CommandAborted;
	plcbit PowerOn;
	plcbit IsHomed;
	plcbit InVelocity;
	plcbit InPosition;
	plcbit MoveActive;
	plcbit MoveDone;
	plcbit Stopped;
	plcbit LimitLoadReady;
	plcbit BrakeReleased;
} MpAxisBasic_typ;

typedef struct MpAxisCamSequencer
{
	/* VAR_INPUT (analog) */
	struct McAxisType* MpLink;
	struct MpAxisCamSequencerParType* Parameters;
	struct McAxisType* MpLinkMaster;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	unsigned char ActualStateIndex;
	unsigned short ActualStateCamIndex;
	struct MpAxisCamSequencerInfoType Info;
	/* VAR (analog) */
	struct MpComInternalDataType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ErrorReset;
	plcbit Update;
	plcbit Signal1;
	plcbit Signal2;
	plcbit Signal3;
	plcbit Signal4;
	plcbit StartSequence;
	plcbit Continue;
	plcbit EndSequence;
	plcbit GetSequence;
	plcbit ParLock;
	plcbit OffsetShift;
	plcbit PhaseShift;
	plcbit CamPrepare;
	plcbit Recovery;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit UpdateDone;
	plcbit Running;
	plcbit Standby;
	plcbit InCompensation;
	plcbit InCam;
	plcbit CommandBusy;
	plcbit CommandAborted;
	plcbit GetSequenceDone;
	plcbit ParLockDone;
	plcbit OffsetDone;
	plcbit PhasingDone;
	plcbit CamPrepareDone;
	plcbit RecoveryDone;
} MpAxisCamSequencer_typ;

typedef struct MpAxisCoupling
{
	/* VAR_INPUT (analog) */
	struct McAxisType* MpLink;
	struct MpAxisCouplingParType* Parameters;
	struct McAxisType* MpLinkMaster;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	struct MpAxisCouplingInfoType Info;
	/* VAR (analog) */
	struct MpComInternalDataType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ErrorReset;
	plcbit Update;
	plcbit Gear;
	plcbit Cam;
	plcbit GearInPos;
	plcbit OffsetShift;
	plcbit PhaseShift;
	plcbit GetCamPosition;
	plcbit CamPrepare;
	plcbit Recovery;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit UpdateDone;
	plcbit CommandBusy;
	plcbit CommandAborted;
	plcbit InCompensation;
	plcbit InSync;
	plcbit OffsetDone;
	plcbit PhasingDone;
	plcbit RecoveryDone;
	plcbit GetCamPositionDone;
	plcbit CamPrepareDone;
} MpAxisCoupling_typ;

typedef struct MpAxisCyclicSet
{
	/* VAR_INPUT (analog) */
	struct McAxisType* MpLink;
	struct MpAxisCyclicSetParType* Parameters;
	double CyclicPosition;
	float CyclicVelocity;
	float CyclicTorque;
	float CyclicTorqueFeedForward;
	/* VAR_OUTPUT (analog) */
	signed long StatusID;
	struct MpAxisCyclicSetInfoType Info;
	/* VAR (analog) */
	struct MpComInternalDataType Internal;
	/* VAR_INPUT (digital) */
	plcbit Enable;
	plcbit ErrorReset;
	plcbit Update;
	plcbit MoveCyclicPosition;
	plcbit MoveCyclicVelocity;
	plcbit TorqueControl;
	plcbit TorqueFeedForward;
	/* VAR_OUTPUT (digital) */
	plcbit Active;
	plcbit Error;
	plcbit UpdateDone;
	plcbit CommandBusy;
	plcbit CommandAborted;
	plcbit MoveCyclicPositionActive;
	plcbit MoveCyclicVelocityActive;
	plcbit TorqueControlActive;
	plcbit TorqueFeedForwardActive;
} MpAxisCyclicSet_typ;



/* Prototyping of functions and function blocks */
_BUR_PUBLIC void MpAxisBasic(struct MpAxisBasic* inst);
_BUR_PUBLIC void MpAxisCamSequencer(struct MpAxisCamSequencer* inst);
_BUR_PUBLIC void MpAxisCoupling(struct MpAxisCoupling* inst);
_BUR_PUBLIC void MpAxisCyclicSet(struct MpAxisCyclicSet* inst);


#ifdef __cplusplus
};
#endif
#endif /* _MPAXIS_ */

