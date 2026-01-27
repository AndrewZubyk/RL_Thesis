/*
 * Thesis_C__.h
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Thesis_C__".
 *
 * Model version              : 32.4
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C++ source code generated on : Tue Jan 27 12:17:27 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef Thesis_C___h_
#define Thesis_C___h_
#include <cmath>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_nonfinite.h"
#include "Thesis_C___types.h"
#include <cstring>

extern "C"
{

#include "rtGetInf.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

#include "zero_crossing_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
struct B_Thesis_C___T {
  real_T AlttitudeDot;                 /* '<S24>/Alttitude Dot' */
  real_T GetAoA;                       /* '<S9>/Get AoA' */
  real_T GetBeta;                      /* '<S9>/Get Beta' */
  real_T activewaypoint[3];            /* '<S4>/Multiport Switch' */
  real_T ManualSwitch;                 /* '<Root>/Manual Switch' */
  real_T h_err;                        /* '<S2>/Sum2' */
  real_T EastDot;                      /* '<S24>/East Dot' */
  real_T NorthDot;                     /* '<S24>/North Dot' */
  real_T Sum1;                         /* '<S25>/Sum1' */
  real_T Sum2;                         /* '<S25>/Sum2' */
  real_T Sum3;                         /* '<S25>/Sum3' */
  real_T Yawrate;                      /* '<S28>/Yaw rate' */
  real_T pitchrate;                    /* '<S28>/pitch rate' */
  real_T rollrate;                     /* '<S28>/roll rate' */
  real_T c1;                           /* '<S33>/c1' */
  real_T c2;                           /* '<S33>/c2' */
  real_T c3;                           /* '<S33>/c3' */
  real_T c4;                           /* '<S33>/c4' */
  real_T c5;                           /* '<S33>/c5' */
  real_T c6;                           /* '<S33>/c6' */
  real_T c7;                           /* '<S33>/c7' */
  real_T c8;                           /* '<S33>/c8' */
  real_T c9;                           /* '<S33>/c9' */
  real_T Sum5[3];                      /* '<S10>/Sum5' */
  real_T Sum2_b[3];                    /* '<S10>/Sum2' */
  real_T pdot;                         /* '<S29>/pdot' */
  real_T qdot;                         /* '<S29>/qdot' */
  real_T rdot;                         /* '<S29>/rdot' */
  real_T IntegralGain;                 /* '<S294>/Integral Gain' */
  real_T IntegralGain_m;               /* '<S242>/Integral Gain' */
  real_T IntegralGain_l;               /* '<S177>/Integral Gain' */
  real_T IntegralGain_e;               /* '<S124>/Integral Gain' */
  real_T IntegralGain_mn;              /* '<S71>/Integral Gain' */
  boolean_T RelationalOperator;        /* '<Root>/Relational Operator' */
  boolean_T increment;                 /* '<S4>/Less Than' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_Thesis_C___T {
  real_T TimeStampA;                   /* '<S9>/Derivative' */
  real_T LastUAtTimeA[2];              /* '<S9>/Derivative' */
  real_T TimeStampB;                   /* '<S9>/Derivative' */
  real_T LastUAtTimeB[2];              /* '<S9>/Derivative' */
  real_T Memory_PreviousInput;         /* '<S4>/Memory' */
  uint32_T Counter_ClkEphState;        /* '<S4>/Counter' */
  int8_T If_ActiveSubsystem;           /* '<S2>/If' */
  uint8_T Counter_Count;               /* '<S4>/Counter' */
};

/* Continuous states (default storage) */
struct X_Thesis_C___T {
  real_T North_CSTATE;                 /* '<S24>/North' */
  real_T East_CSTATE;                  /* '<S24>/East' */
  real_T Alt_CSTATE;                   /* '<S24>/Alt' */
  real_T bank_CSTATE;                  /* '<S28>/bank' */
  real_T pitch_CSTATE;                 /* '<S28>/pitch' */
  real_T heading_CSTATE;               /* '<S28>/heading' */
  real_T uintegrate_CSTATE;            /* '<S25>/u integrate' */
  real_T vintegrate_CSTATE;            /* '<S25>/v integrate' */
  real_T wintegrate_CSTATE;            /* '<S25>/w integrate' */
  real_T qintegrate_CSTATE;            /* '<S29>/q integrate' */
  real_T pintegrate_CSTATE;            /* '<S29>/p integrate' */
  real_T rintegrate_CSTATE;            /* '<S29>/r integrate' */
  real_T Integrator_CSTATE;            /* '<S297>/Integrator' */
  real_T Integrator_CSTATE_a;          /* '<S245>/Integrator' */
  real_T Integrator_CSTATE_h;          /* '<S180>/Integrator' */
  real_T Integrator_CSTATE_n;          /* '<S127>/Integrator' */
  real_T Integrator_CSTATE_k;          /* '<S74>/Integrator' */
};

/* State derivatives (default storage) */
struct XDot_Thesis_C___T {
  real_T North_CSTATE;                 /* '<S24>/North' */
  real_T East_CSTATE;                  /* '<S24>/East' */
  real_T Alt_CSTATE;                   /* '<S24>/Alt' */
  real_T bank_CSTATE;                  /* '<S28>/bank' */
  real_T pitch_CSTATE;                 /* '<S28>/pitch' */
  real_T heading_CSTATE;               /* '<S28>/heading' */
  real_T uintegrate_CSTATE;            /* '<S25>/u integrate' */
  real_T vintegrate_CSTATE;            /* '<S25>/v integrate' */
  real_T wintegrate_CSTATE;            /* '<S25>/w integrate' */
  real_T qintegrate_CSTATE;            /* '<S29>/q integrate' */
  real_T pintegrate_CSTATE;            /* '<S29>/p integrate' */
  real_T rintegrate_CSTATE;            /* '<S29>/r integrate' */
  real_T Integrator_CSTATE;            /* '<S297>/Integrator' */
  real_T Integrator_CSTATE_a;          /* '<S245>/Integrator' */
  real_T Integrator_CSTATE_h;          /* '<S180>/Integrator' */
  real_T Integrator_CSTATE_n;          /* '<S127>/Integrator' */
  real_T Integrator_CSTATE_k;          /* '<S74>/Integrator' */
};

/* State disabled  */
struct XDis_Thesis_C___T {
  boolean_T North_CSTATE;              /* '<S24>/North' */
  boolean_T East_CSTATE;               /* '<S24>/East' */
  boolean_T Alt_CSTATE;                /* '<S24>/Alt' */
  boolean_T bank_CSTATE;               /* '<S28>/bank' */
  boolean_T pitch_CSTATE;              /* '<S28>/pitch' */
  boolean_T heading_CSTATE;            /* '<S28>/heading' */
  boolean_T uintegrate_CSTATE;         /* '<S25>/u integrate' */
  boolean_T vintegrate_CSTATE;         /* '<S25>/v integrate' */
  boolean_T wintegrate_CSTATE;         /* '<S25>/w integrate' */
  boolean_T qintegrate_CSTATE;         /* '<S29>/q integrate' */
  boolean_T pintegrate_CSTATE;         /* '<S29>/p integrate' */
  boolean_T rintegrate_CSTATE;         /* '<S29>/r integrate' */
  boolean_T Integrator_CSTATE;         /* '<S297>/Integrator' */
  boolean_T Integrator_CSTATE_a;       /* '<S245>/Integrator' */
  boolean_T Integrator_CSTATE_h;       /* '<S180>/Integrator' */
  boolean_T Integrator_CSTATE_n;       /* '<S127>/Integrator' */
  boolean_T Integrator_CSTATE_k;       /* '<S74>/Integrator' */
};

/* Zero-crossing (trigger) state */
struct PrevZCX_Thesis_C___T {
  ZCSigState North_Reset_ZCE;          /* '<S24>/North' */
  ZCSigState East_Reset_ZCE;           /* '<S24>/East' */
  ZCSigState Alt_Reset_ZCE;            /* '<S24>/Alt' */
  ZCSigState bank_Reset_ZCE;           /* '<S28>/bank' */
  ZCSigState pitch_Reset_ZCE;          /* '<S28>/pitch' */
  ZCSigState heading_Reset_ZCE;        /* '<S28>/heading' */
  ZCSigState uintegrate_Reset_ZCE;     /* '<S25>/u integrate' */
  ZCSigState vintegrate_Reset_ZCE;     /* '<S25>/v integrate' */
  ZCSigState wintegrate_Reset_ZCE;     /* '<S25>/w integrate' */
  ZCSigState qintegrate_Reset_ZCE;     /* '<S29>/q integrate' */
  ZCSigState pintegrate_Reset_ZCE;     /* '<S29>/p integrate' */
  ZCSigState rintegrate_Reset_ZCE;     /* '<S29>/r integrate' */
};

#ifndef ODE4_INTG
#define ODE4_INTG

/* ODE4 Integration Data */
struct ODE4_IntgData {
  real_T *y;                           /* output */
  real_T *f[4];                        /* derivatives */
};

#endif

/* External inputs (root inport signals with default storage) */
struct ExtU_Thesis_C___T {
  real_T In1[5];                       /* '<Root>/In1' */
};

/* External outputs (root outports fed by signals with default storage) */
struct ExtY_Thesis_C___T {
  real32_T Out1[9];                    /* '<Root>/Out1' */
};

/* Parameters (default storage) */
struct P_Thesis_C___T_ {
  struct_iC9oEOXNrspZ70YHzXYOmE wp;    /* Variable: wp
                                        * Referenced by:
                                        *   '<S4>/WP1'
                                        *   '<S4>/WP2'
                                        *   '<S4>/WP3'
                                        */
  real_T ac[3];                        /* Variable: ac
                                        * Referenced by: '<S10>/Aero Center'
                                        */
  real_T cda2;                         /* Variable: cda2
                                        * Referenced by: '<S14>/cda2'
                                        */
  real_T cdo;                          /* Variable: cdo
                                        * Referenced by: '<S14>/cdo'
                                        */
  real_T cg[3];                        /* Variable: cg
                                        * Referenced by: '<S11>/cg'
                                        */
  real_T cla;                          /* Variable: cla
                                        * Referenced by: '<S15>/cla'
                                        */
  real_T cladot;                       /* Variable: cladot
                                        * Referenced by: '<S15>/cladot'
                                        */
  real_T clb;                          /* Variable: clb
                                        * Referenced by: '<S19>/clb'
                                        */
  real_T clda;                         /* Variable: clda
                                        * Referenced by: '<S19>/clda'
                                        */
  real_T clde;                         /* Variable: clde
                                        * Referenced by: '<S15>/clde'
                                        */
  real_T cldr;                         /* Variable: cldr
                                        * Referenced by: '<S19>/cldr'
                                        */
  real_T clo;                          /* Variable: clo
                                        * Referenced by: '<S15>/clo'
                                        */
  real_T clp;                          /* Variable: clp
                                        * Referenced by: '<S19>/clp'
                                        */
  real_T clq;                          /* Variable: clq
                                        * Referenced by: '<S15>/clq'
                                        */
  real_T clr;                          /* Variable: clr
                                        * Referenced by: '<S19>/clr'
                                        */
  real_T cma;                          /* Variable: cma
                                        * Referenced by: '<S16>/cma'
                                        */
  real_T cmadot;                       /* Variable: cmadot
                                        * Referenced by: '<S16>/cmadot'
                                        */
  real_T cmde;                         /* Variable: cmde
                                        * Referenced by: '<S16>/cmde'
                                        */
  real_T cmq;                          /* Variable: cmq
                                        * Referenced by: '<S16>/cmq'
                                        */
  real_T cnb;                          /* Variable: cnb
                                        * Referenced by: '<S17>/cnb'
                                        */
  real_T cnda;                         /* Variable: cnda
                                        * Referenced by: '<S17>/cnda'
                                        */
  real_T cndr;                         /* Variable: cndr
                                        * Referenced by: '<S17>/cndr'
                                        */
  real_T cnp;                          /* Variable: cnp
                                        * Referenced by: '<S17>/cnp'
                                        */
  real_T cnr;                          /* Variable: cnr
                                        * Referenced by: '<S17>/cnr'
                                        */
  real_T cyb;                          /* Variable: cyb
                                        * Referenced by: '<S18>/cyb'
                                        */
  real_T cydr;                         /* Variable: cydr
                                        * Referenced by: '<S18>/cydr'
                                        */
  real_T eng[3];                       /* Variable: eng
                                        * Referenced by: '<S10>/DngPOS'
                                        */
  real_T initbank;                     /* Variable: initbank
                                        * Referenced by: '<S28>/bank'
                                        */
  real_T inithead;                     /* Variable: inithead
                                        * Referenced by: '<S28>/heading'
                                        */
  real_T initp;                        /* Variable: initp
                                        * Referenced by: '<S29>/p integrate'
                                        */
  real_T initq;                        /* Variable: initq
                                        * Referenced by: '<S29>/q integrate'
                                        */
  real_T initr;                        /* Variable: initr
                                        * Referenced by: '<S29>/r integrate'
                                        */
  real_T initv;                        /* Variable: initv
                                        * Referenced by: '<S25>/v integrate'
                                        */
  real_T initw;                        /* Variable: initw
                                        * Referenced by: '<S25>/w integrate'
                                        */
  real_T jx;                           /* Variable: jx
                                        * Referenced by: '<S11>/jx'
                                        */
  real_T jxz;                          /* Variable: jxz
                                        * Referenced by: '<S11>/jxz'
                                        */
  real_T jy;                           /* Variable: jy
                                        * Referenced by: '<S11>/jy'
                                        */
  real_T jz;                           /* Variable: jz
                                        * Referenced by: '<S11>/jz'
                                        */
  real_T sw;                           /* Variable: sw
                                        * Referenced by: '<S20>/Gain2'
                                        */
  real_T weight;                       /* Variable: weight
                                        * Referenced by: '<S11>/mass2'
                                        */
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S71>/Integral Gain'
                                        */
  real_T PIDController_I_o;            /* Mask Parameter: PIDController_I_o
                                        * Referenced by: '<S124>/Integral Gain'
                                        */
  real_T PIDController_I_a;            /* Mask Parameter: PIDController_I_a
                                        * Referenced by: '<S177>/Integral Gain'
                                        */
  real_T PIDController1_I;             /* Mask Parameter: PIDController1_I
                                        * Referenced by: '<S294>/Integral Gain'
                                        */
  real_T PIDController_I_n;            /* Mask Parameter: PIDController_I_n
                                        * Referenced by: '<S242>/Integral Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S74>/Integrator'
                               */
  real_T PIDController_InitialConditio_e;
                              /* Mask Parameter: PIDController_InitialConditio_e
                               * Referenced by: '<S127>/Integrator'
                               */
  real_T PIDController_InitialConditio_k;
                              /* Mask Parameter: PIDController_InitialConditio_k
                               * Referenced by: '<S180>/Integrator'
                               */
  real_T PIDController1_InitialCondition;
                              /* Mask Parameter: PIDController1_InitialCondition
                               * Referenced by: '<S297>/Integrator'
                               */
  real_T PIDController_InitialConditi_kv;
                              /* Mask Parameter: PIDController_InitialConditi_kv
                               * Referenced by: '<S245>/Integrator'
                               */
  real_T PIDController_P;              /* Mask Parameter: PIDController_P
                                        * Referenced by: '<S79>/Proportional Gain'
                                        */
  real_T PIDController_P_n;            /* Mask Parameter: PIDController_P_n
                                        * Referenced by: '<S132>/Proportional Gain'
                                        */
  real_T PIDController_P_b;            /* Mask Parameter: PIDController_P_b
                                        * Referenced by: '<S185>/Proportional Gain'
                                        */
  real_T PIDController1_P;             /* Mask Parameter: PIDController1_P
                                        * Referenced by: '<S302>/Proportional Gain'
                                        */
  uint8_T Counter_HitValue;            /* Mask Parameter: Counter_HitValue
                                        * Referenced by: '<S4>/Counter'
                                        */
  uint8_T Counter_InitialCount;        /* Mask Parameter: Counter_InitialCount
                                        * Referenced by: '<S4>/Counter'
                                        */
  real_T RoC_CMD_Value;                /* Expression: 1
                                        * Referenced by: '<S36>/RoC_CMD'
                                        */
  real_T RoC_CMD1_Value;               /* Expression: 1
                                        * Referenced by: '<S36>/RoC_CMD1'
                                        */
  real_T RoC_CMD_Value_e;              /* Expression: -1
                                        * Referenced by: '<S37>/RoC_CMD'
                                        */
  real_T RoC_CMD1_Value_k;             /* Expression: 2
                                        * Referenced by: '<S37>/RoC_CMD1'
                                        */
  real_T Tohelpidentifywhichcontrollawis;/* Expression: 3
                                          * Referenced by: '<S38>/To help identify which control  law is running'
                                          */
  real_T Check_Value;                  /* Expression: .5
                                        * Referenced by: '<Root>/Check'
                                        */
  real_T North_IC;                     /* Expression: 0
                                        * Referenced by: '<S24>/North'
                                        */
  real_T East_IC;                      /* Expression: 0
                                        * Referenced by: '<S24>/East'
                                        */
  real_T Alt_IC;                       /* Expression: 1000
                                        * Referenced by: '<S24>/Alt'
                                        */
  real_T pitch_IC;                     /* Expression: 0
                                        * Referenced by: '<S28>/pitch'
                                        */
  real_T uintegrate_IC;                /* Expression: 226
                                        * Referenced by: '<S25>/u integrate'
                                        */
  real_T vy_Value;                     /* Expression: 0
                                        * Referenced by: '<Root>/v(y)'
                                        */
  real_T Gain_Gain;                    /* Expression: -1
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Aileron_Value;                /* Expression: 0
                                        * Referenced by: '<Root>/Aileron'
                                        */
  real_T AoASat_UpperSat;              /* Expression: 0.3
                                        * Referenced by: '<S9>/AoA Sat'
                                        */
  real_T AoASat_LowerSat;              /* Expression: -0.2
                                        * Referenced by: '<S9>/AoA Sat'
                                        */
  real_T BetaSat_UpperSat;             /* Expression: 0.4
                                        * Referenced by: '<S9>/Beta Sat'
                                        */
  real_T BetaSat_LowerSat;             /* Expression: -0.4
                                        * Referenced by: '<S9>/Beta Sat'
                                        */
  real_T Gain_Gain_n;                  /* Expression: -1
                                        * Referenced by: '<S20>/Gain'
                                        */
  real_T AirspeedSat_UpperSat;         /* Expression: 1100
                                        * Referenced by: '<S9>/Airspeed Sat'
                                        */
  real_T AirspeedSat_LowerSat;         /* Expression: 0
                                        * Referenced by: '<S9>/Airspeed Sat'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant1'
                                        */
  real_T Memory_InitialCondition;      /* Expression: 1
                                        * Referenced by: '<S4>/Memory'
                                        */
  real_T Elevator_Value;               /* Expression: .02193
                                        * Referenced by: '<Root>/Elevator'
                                        */
  real_T Gain1_Gain;                   /* Expression: -1
                                        * Referenced by: '<S20>/Gain1'
                                        */
  real_T Rudder_Value;                 /* Expression: 0
                                        * Referenced by: '<Root>/Rudder'
                                        */
  real_T Gain_Gain_o;                  /* Expression: 180/pi
                                        * Referenced by: '<S198>/Gain'
                                        */
  real_T Gain1_Gain_g;                 /* Expression: pi/180
                                        * Referenced by: '<S208>/Gain1'
                                        */
  real_T uDLookupTable2_tableData[629];
                                  /* Expression: deg2rad(52)*tanh([-pi:0.01:pi])
                                   * Referenced by: '<S5>/1-D Lookup Table2'
                                   */
  real_T uDLookupTable2_bp01Data[629]; /* Expression: [-pi:0.01:pi]
                                        * Referenced by: '<S5>/1-D Lookup Table2'
                                        */
  real_T uDLookupTable3_tableData[629];
                                /* Expression: -deg2rad(120)*tanh([-pi:0.01:pi])
                                 * Referenced by: '<S5>/1-D Lookup Table3'
                                 */
  real_T uDLookupTable3_bp01Data[629]; /* Expression: [-pi:0.01:pi]
                                        * Referenced by: '<S5>/1-D Lookup Table3'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant2'
                                        */
  real_T MaxPower_Value;               /* Expression: 200*550
                                        * Referenced by: '<S7>/Max Power'
                                        */
  real_T Throttle_Value;               /* Expression: 1
                                        * Referenced by: '<Root>/Throttle'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S26>/Constant'
                                        */
  real_T Constant1_Value_a;            /* Expression: 32.2
                                        * Referenced by: '<S26>/Constant1'
                                        */
  real_T ThrustYZ_Value;               /* Expression: 0
                                        * Referenced by: '<S10>/Thrust Y&Z'
                                        */
  real_T Checkprobnotzero_Value;       /* Expression: 0
                                        * Referenced by: '<S34>/Check prob not zero'
                                        */
  real_T MinRange_Value;               /* Expression: 100
                                        * Referenced by: '<S4>/Min Range'
                                        */
  uint8_T ManualSwitch_CurrentSetting;
                              /* Computed Parameter: ManualSwitch_CurrentSetting
                               * Referenced by: '<Root>/Manual Switch'
                               */
  uint8_T longitudinalautopilot_CurrentSe;
                          /* Computed Parameter: longitudinalautopilot_CurrentSe
                           * Referenced by: '<Root>/longitudinal autopilot'
                           */
  uint8_T switch_CurrentSetting;    /* Computed Parameter: switch_CurrentSetting
                                     * Referenced by: '<Root>/switch'
                                     */
  uint8_T switch2_CurrentSetting;  /* Computed Parameter: switch2_CurrentSetting
                                    * Referenced by: '<Root>/switch2'
                                    */
  uint8_T switch1_CurrentSetting;  /* Computed Parameter: switch1_CurrentSetting
                                    * Referenced by: '<Root>/switch1'
                                    */
  uint8_T trackwaypoints_CurrentSetting;
                            /* Computed Parameter: trackwaypoints_CurrentSetting
                             * Referenced by: '<Root>/track waypoints'
                             */
  uint8_T switch3_CurrentSetting;  /* Computed Parameter: switch3_CurrentSetting
                                    * Referenced by: '<Root>/switch3'
                                    */
};

/* Real-time Model Data Structure */
struct tag_RTM_Thesis_C___T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_Thesis_C___T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_Thesis_C___T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[17];
  real_T odeF[4][17];
  ODE4_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Class declaration for model Thesis_C__ */
class Thesis_C__ final
{
  /* public data and function members */
 public:
  /* Copy Constructor */
  Thesis_C__(Thesis_C__ const&) = delete;

  /* Assignment Operator */
  Thesis_C__& operator= (Thesis_C__ const&) & = delete;

  /* Move Constructor */
  Thesis_C__(Thesis_C__ &&) = delete;

  /* Move Assignment Operator */
  Thesis_C__& operator= (Thesis_C__ &&) = delete;

  /* Real-Time Model get method */
  RT_MODEL_Thesis_C___T * getRTM();

  /* Root inports set method */
  void setExternalInputs(const ExtU_Thesis_C___T *pExtU_Thesis_C___T)
  {
    Thesis_C___U = *pExtU_Thesis_C___T;
  }

  /* Root outports get method */
  const ExtY_Thesis_C___T &getExternalOutputs() const
  {
    return Thesis_C___Y;
  }

  void ModelPrevZCStateInit();

  /* model start function */
  void start();

  /* Initial conditions function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  static void terminate();

  /* Constructor */
  Thesis_C__();

  /* Destructor */
  ~Thesis_C__();

  /* private data and function members */
 private:
  /* External inputs */
  ExtU_Thesis_C___T Thesis_C___U;

  /* External outputs */
  ExtY_Thesis_C___T Thesis_C___Y;

  /* Block signals */
  B_Thesis_C___T Thesis_C___B;

  /* Block states */
  DW_Thesis_C___T Thesis_C___DW;

  /* Tunable parameters */
  static P_Thesis_C___T Thesis_C___P;

  /* Block continuous states */
  X_Thesis_C___T Thesis_C___X;

  /* Block Continuous state disabled vector */
  XDis_Thesis_C___T Thesis_C___XDis;

  /* Triggered events */
  PrevZCX_Thesis_C___T Thesis_C___PrevZCX;

  /* Global mass matrix */

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void Thesis_C___derivatives();

  /* Real-Time Model */
  RT_MODEL_Thesis_C___T Thesis_C___M;
};

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Thesis_C__'
 * '<S1>'   : 'Thesis_C__/Aircraft_Dynamics'
 * '<S2>'   : 'Thesis_C__/Longitudinal Autopilot'
 * '<S3>'   : 'Thesis_C__/Waypoints'
 * '<S4>'   : 'Thesis_C__/waypoint switching'
 * '<S5>'   : 'Thesis_C__/waypoint tracking'
 * '<S6>'   : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics'
 * '<S7>'   : 'Thesis_C__/Aircraft_Dynamics/Engines'
 * '<S8>'   : 'Thesis_C__/Aircraft_Dynamics/Equations of motion numerical integration '
 * '<S9>'   : 'Thesis_C__/Aircraft_Dynamics/Flight Parameters'
 * '<S10>'  : 'Thesis_C__/Aircraft_Dynamics/Linear Acc and Moments'
 * '<S11>'  : 'Thesis_C__/Aircraft_Dynamics/Mass, CG & inertia'
 * '<S12>'  : 'Thesis_C__/Aircraft_Dynamics/Standard Atmosphere'
 * '<S13>'  : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics/Aero Forces and Moments'
 * '<S14>'  : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics/CD'
 * '<S15>'  : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics/CL'
 * '<S16>'  : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics/CM'
 * '<S17>'  : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics/CN'
 * '<S18>'  : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics/CY'
 * '<S19>'  : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics/Croll'
 * '<S20>'  : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics/Aero Forces and Moments/Aerodynamic Forces'
 * '<S21>'  : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics/Aero Forces and Moments/Aerodynamic Moments'
 * '<S22>'  : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics/Aero Forces and Moments/Aerodynamic Forces/Body to Wind'
 * '<S23>'  : 'Thesis_C__/Aircraft_Dynamics/Aerodynamics/CD/Get Alpha'
 * '<S24>'  : 'Thesis_C__/Aircraft_Dynamics/Equations of motion numerical integration /Flat Earth Navigation'
 * '<S25>'  : 'Thesis_C__/Aircraft_Dynamics/Equations of motion numerical integration /Force Equations'
 * '<S26>'  : 'Thesis_C__/Aircraft_Dynamics/Equations of motion numerical integration /Gravity Model'
 * '<S27>'  : 'Thesis_C__/Aircraft_Dynamics/Equations of motion numerical integration /Inert-body'
 * '<S28>'  : 'Thesis_C__/Aircraft_Dynamics/Equations of motion numerical integration /Kinematic Equiations'
 * '<S29>'  : 'Thesis_C__/Aircraft_Dynamics/Equations of motion numerical integration /Moment Equations'
 * '<S30>'  : 'Thesis_C__/Aircraft_Dynamics/Equations of motion numerical integration /Kinematic Equiations/2pi Bound'
 * '<S31>'  : 'Thesis_C__/Aircraft_Dynamics/Equations of motion numerical integration /Kinematic Equiations/pi Bound'
 * '<S32>'  : 'Thesis_C__/Aircraft_Dynamics/Equations of motion numerical integration /Kinematic Equiations/pi Bound1'
 * '<S33>'  : 'Thesis_C__/Aircraft_Dynamics/Equations of motion numerical integration /Moment Equations/Inertia Coefs'
 * '<S34>'  : 'Thesis_C__/Aircraft_Dynamics/Linear Acc and Moments/Cross Prod Moment due Leng'
 * '<S35>'  : 'Thesis_C__/Aircraft_Dynamics/Linear Acc and Moments/Cross Prod Moment due to Aero'
 * '<S36>'  : 'Thesis_C__/Longitudinal Autopilot/Climb'
 * '<S37>'  : 'Thesis_C__/Longitudinal Autopilot/Decend'
 * '<S38>'  : 'Thesis_C__/Longitudinal Autopilot/Level'
 * '<S39>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller'
 * '<S40>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Anti-windup'
 * '<S41>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/D Gain'
 * '<S42>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/External Derivative'
 * '<S43>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Filter'
 * '<S44>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Filter ICs'
 * '<S45>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/I Gain'
 * '<S46>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Ideal P Gain'
 * '<S47>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Ideal P Gain Fdbk'
 * '<S48>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Integrator'
 * '<S49>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Integrator ICs'
 * '<S50>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/N Copy'
 * '<S51>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/N Gain'
 * '<S52>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/P Copy'
 * '<S53>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Parallel P Gain'
 * '<S54>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Reset Signal'
 * '<S55>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Saturation'
 * '<S56>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Saturation Fdbk'
 * '<S57>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Sum'
 * '<S58>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Sum Fdbk'
 * '<S59>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Tracking Mode'
 * '<S60>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Tracking Mode Sum'
 * '<S61>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Tsamp - Integral'
 * '<S62>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Tsamp - Ngain'
 * '<S63>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/postSat Signal'
 * '<S64>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/preInt Signal'
 * '<S65>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/preSat Signal'
 * '<S66>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Anti-windup/Passthrough'
 * '<S67>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/D Gain/Disabled'
 * '<S68>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/External Derivative/Disabled'
 * '<S69>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Filter/Disabled'
 * '<S70>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Filter ICs/Disabled'
 * '<S71>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/I Gain/Internal Parameters'
 * '<S72>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Ideal P Gain/Passthrough'
 * '<S73>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S74>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Integrator/Continuous'
 * '<S75>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Integrator ICs/Internal IC'
 * '<S76>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S77>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/N Gain/Disabled'
 * '<S78>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/P Copy/Disabled'
 * '<S79>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S80>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Reset Signal/Disabled'
 * '<S81>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Saturation/Passthrough'
 * '<S82>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Saturation Fdbk/Disabled'
 * '<S83>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Sum/Sum_PI'
 * '<S84>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Sum Fdbk/Disabled'
 * '<S85>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Tracking Mode/Disabled'
 * '<S86>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S87>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S88>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S89>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/postSat Signal/Forward_Path'
 * '<S90>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/preInt Signal/Internal PreInt'
 * '<S91>'  : 'Thesis_C__/Longitudinal Autopilot/Climb/PID Controller/preSat Signal/Forward_Path'
 * '<S92>'  : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller'
 * '<S93>'  : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Anti-windup'
 * '<S94>'  : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/D Gain'
 * '<S95>'  : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/External Derivative'
 * '<S96>'  : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Filter'
 * '<S97>'  : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Filter ICs'
 * '<S98>'  : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/I Gain'
 * '<S99>'  : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Ideal P Gain'
 * '<S100>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Ideal P Gain Fdbk'
 * '<S101>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Integrator'
 * '<S102>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Integrator ICs'
 * '<S103>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/N Copy'
 * '<S104>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/N Gain'
 * '<S105>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/P Copy'
 * '<S106>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Parallel P Gain'
 * '<S107>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Reset Signal'
 * '<S108>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Saturation'
 * '<S109>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Saturation Fdbk'
 * '<S110>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Sum'
 * '<S111>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Sum Fdbk'
 * '<S112>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Tracking Mode'
 * '<S113>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Tracking Mode Sum'
 * '<S114>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Tsamp - Integral'
 * '<S115>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Tsamp - Ngain'
 * '<S116>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/postSat Signal'
 * '<S117>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/preInt Signal'
 * '<S118>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/preSat Signal'
 * '<S119>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Anti-windup/Passthrough'
 * '<S120>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/D Gain/Disabled'
 * '<S121>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/External Derivative/Disabled'
 * '<S122>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Filter/Disabled'
 * '<S123>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Filter ICs/Disabled'
 * '<S124>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/I Gain/Internal Parameters'
 * '<S125>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Ideal P Gain/Passthrough'
 * '<S126>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S127>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Integrator/Continuous'
 * '<S128>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Integrator ICs/Internal IC'
 * '<S129>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S130>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/N Gain/Disabled'
 * '<S131>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/P Copy/Disabled'
 * '<S132>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S133>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Reset Signal/Disabled'
 * '<S134>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Saturation/Passthrough'
 * '<S135>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Saturation Fdbk/Disabled'
 * '<S136>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Sum/Sum_PI'
 * '<S137>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Sum Fdbk/Disabled'
 * '<S138>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Tracking Mode/Disabled'
 * '<S139>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S140>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S141>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S142>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/postSat Signal/Forward_Path'
 * '<S143>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/preInt Signal/Internal PreInt'
 * '<S144>' : 'Thesis_C__/Longitudinal Autopilot/Decend/PID Controller/preSat Signal/Forward_Path'
 * '<S145>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller'
 * '<S146>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Anti-windup'
 * '<S147>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/D Gain'
 * '<S148>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/External Derivative'
 * '<S149>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Filter'
 * '<S150>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Filter ICs'
 * '<S151>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/I Gain'
 * '<S152>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Ideal P Gain'
 * '<S153>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Ideal P Gain Fdbk'
 * '<S154>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Integrator'
 * '<S155>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Integrator ICs'
 * '<S156>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/N Copy'
 * '<S157>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/N Gain'
 * '<S158>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/P Copy'
 * '<S159>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Parallel P Gain'
 * '<S160>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Reset Signal'
 * '<S161>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Saturation'
 * '<S162>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Saturation Fdbk'
 * '<S163>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Sum'
 * '<S164>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Sum Fdbk'
 * '<S165>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Tracking Mode'
 * '<S166>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Tracking Mode Sum'
 * '<S167>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Tsamp - Integral'
 * '<S168>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Tsamp - Ngain'
 * '<S169>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/postSat Signal'
 * '<S170>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/preInt Signal'
 * '<S171>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/preSat Signal'
 * '<S172>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Anti-windup/Passthrough'
 * '<S173>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/D Gain/Disabled'
 * '<S174>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/External Derivative/Disabled'
 * '<S175>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Filter/Disabled'
 * '<S176>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Filter ICs/Disabled'
 * '<S177>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/I Gain/Internal Parameters'
 * '<S178>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Ideal P Gain/Passthrough'
 * '<S179>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S180>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Integrator/Continuous'
 * '<S181>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Integrator ICs/Internal IC'
 * '<S182>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S183>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/N Gain/Disabled'
 * '<S184>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/P Copy/Disabled'
 * '<S185>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S186>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Reset Signal/Disabled'
 * '<S187>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Saturation/Passthrough'
 * '<S188>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Saturation Fdbk/Disabled'
 * '<S189>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Sum/Sum_PI'
 * '<S190>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Sum Fdbk/Disabled'
 * '<S191>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Tracking Mode/Disabled'
 * '<S192>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S193>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S194>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S195>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/postSat Signal/Forward_Path'
 * '<S196>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/preInt Signal/Internal PreInt'
 * '<S197>' : 'Thesis_C__/Longitudinal Autopilot/Level/PID Controller/preSat Signal/Forward_Path'
 * '<S198>' : 'Thesis_C__/Waypoints/Radians to Degrees'
 * '<S199>' : 'Thesis_C__/Waypoints/Range Finding'
 * '<S200>' : 'Thesis_C__/Waypoints/Rel_bearing'
 * '<S201>' : 'Thesis_C__/Waypoints/Rel_bearing/Relative bearing matlab function'
 * '<S202>' : 'Thesis_C__/Waypoints/Rel_bearing/old relative bearing'
 * '<S203>' : 'Thesis_C__/Waypoints/Rel_bearing/old relative bearing/0 to 2pi'
 * '<S204>' : 'Thesis_C__/Waypoints/Rel_bearing/old relative bearing/Radians to Degrees'
 * '<S205>' : 'Thesis_C__/Waypoints/Rel_bearing/old relative bearing/Radians to Degrees1'
 * '<S206>' : 'Thesis_C__/Waypoints/Rel_bearing/old relative bearing/Radians to Degrees2'
 * '<S207>' : 'Thesis_C__/Waypoints/Rel_bearing/old relative bearing/pibound'
 * '<S208>' : 'Thesis_C__/waypoint tracking/Degrees to Radians'
 * '<S209>' : 'Thesis_C__/waypoint tracking/PID Controller'
 * '<S210>' : 'Thesis_C__/waypoint tracking/PID Controller1'
 * '<S211>' : 'Thesis_C__/waypoint tracking/PID Controller/Anti-windup'
 * '<S212>' : 'Thesis_C__/waypoint tracking/PID Controller/D Gain'
 * '<S213>' : 'Thesis_C__/waypoint tracking/PID Controller/External Derivative'
 * '<S214>' : 'Thesis_C__/waypoint tracking/PID Controller/Filter'
 * '<S215>' : 'Thesis_C__/waypoint tracking/PID Controller/Filter ICs'
 * '<S216>' : 'Thesis_C__/waypoint tracking/PID Controller/I Gain'
 * '<S217>' : 'Thesis_C__/waypoint tracking/PID Controller/Ideal P Gain'
 * '<S218>' : 'Thesis_C__/waypoint tracking/PID Controller/Ideal P Gain Fdbk'
 * '<S219>' : 'Thesis_C__/waypoint tracking/PID Controller/Integrator'
 * '<S220>' : 'Thesis_C__/waypoint tracking/PID Controller/Integrator ICs'
 * '<S221>' : 'Thesis_C__/waypoint tracking/PID Controller/N Copy'
 * '<S222>' : 'Thesis_C__/waypoint tracking/PID Controller/N Gain'
 * '<S223>' : 'Thesis_C__/waypoint tracking/PID Controller/P Copy'
 * '<S224>' : 'Thesis_C__/waypoint tracking/PID Controller/Parallel P Gain'
 * '<S225>' : 'Thesis_C__/waypoint tracking/PID Controller/Reset Signal'
 * '<S226>' : 'Thesis_C__/waypoint tracking/PID Controller/Saturation'
 * '<S227>' : 'Thesis_C__/waypoint tracking/PID Controller/Saturation Fdbk'
 * '<S228>' : 'Thesis_C__/waypoint tracking/PID Controller/Sum'
 * '<S229>' : 'Thesis_C__/waypoint tracking/PID Controller/Sum Fdbk'
 * '<S230>' : 'Thesis_C__/waypoint tracking/PID Controller/Tracking Mode'
 * '<S231>' : 'Thesis_C__/waypoint tracking/PID Controller/Tracking Mode Sum'
 * '<S232>' : 'Thesis_C__/waypoint tracking/PID Controller/Tsamp - Integral'
 * '<S233>' : 'Thesis_C__/waypoint tracking/PID Controller/Tsamp - Ngain'
 * '<S234>' : 'Thesis_C__/waypoint tracking/PID Controller/postSat Signal'
 * '<S235>' : 'Thesis_C__/waypoint tracking/PID Controller/preInt Signal'
 * '<S236>' : 'Thesis_C__/waypoint tracking/PID Controller/preSat Signal'
 * '<S237>' : 'Thesis_C__/waypoint tracking/PID Controller/Anti-windup/Passthrough'
 * '<S238>' : 'Thesis_C__/waypoint tracking/PID Controller/D Gain/Disabled'
 * '<S239>' : 'Thesis_C__/waypoint tracking/PID Controller/External Derivative/Disabled'
 * '<S240>' : 'Thesis_C__/waypoint tracking/PID Controller/Filter/Disabled'
 * '<S241>' : 'Thesis_C__/waypoint tracking/PID Controller/Filter ICs/Disabled'
 * '<S242>' : 'Thesis_C__/waypoint tracking/PID Controller/I Gain/Internal Parameters'
 * '<S243>' : 'Thesis_C__/waypoint tracking/PID Controller/Ideal P Gain/Passthrough'
 * '<S244>' : 'Thesis_C__/waypoint tracking/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S245>' : 'Thesis_C__/waypoint tracking/PID Controller/Integrator/Continuous'
 * '<S246>' : 'Thesis_C__/waypoint tracking/PID Controller/Integrator ICs/Internal IC'
 * '<S247>' : 'Thesis_C__/waypoint tracking/PID Controller/N Copy/Disabled wSignal Specification'
 * '<S248>' : 'Thesis_C__/waypoint tracking/PID Controller/N Gain/Disabled'
 * '<S249>' : 'Thesis_C__/waypoint tracking/PID Controller/P Copy/Disabled'
 * '<S250>' : 'Thesis_C__/waypoint tracking/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S251>' : 'Thesis_C__/waypoint tracking/PID Controller/Reset Signal/Disabled'
 * '<S252>' : 'Thesis_C__/waypoint tracking/PID Controller/Saturation/Passthrough'
 * '<S253>' : 'Thesis_C__/waypoint tracking/PID Controller/Saturation Fdbk/Disabled'
 * '<S254>' : 'Thesis_C__/waypoint tracking/PID Controller/Sum/Sum_PI'
 * '<S255>' : 'Thesis_C__/waypoint tracking/PID Controller/Sum Fdbk/Disabled'
 * '<S256>' : 'Thesis_C__/waypoint tracking/PID Controller/Tracking Mode/Disabled'
 * '<S257>' : 'Thesis_C__/waypoint tracking/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S258>' : 'Thesis_C__/waypoint tracking/PID Controller/Tsamp - Integral/TsSignalSpecification'
 * '<S259>' : 'Thesis_C__/waypoint tracking/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S260>' : 'Thesis_C__/waypoint tracking/PID Controller/postSat Signal/Forward_Path'
 * '<S261>' : 'Thesis_C__/waypoint tracking/PID Controller/preInt Signal/Internal PreInt'
 * '<S262>' : 'Thesis_C__/waypoint tracking/PID Controller/preSat Signal/Forward_Path'
 * '<S263>' : 'Thesis_C__/waypoint tracking/PID Controller1/Anti-windup'
 * '<S264>' : 'Thesis_C__/waypoint tracking/PID Controller1/D Gain'
 * '<S265>' : 'Thesis_C__/waypoint tracking/PID Controller1/External Derivative'
 * '<S266>' : 'Thesis_C__/waypoint tracking/PID Controller1/Filter'
 * '<S267>' : 'Thesis_C__/waypoint tracking/PID Controller1/Filter ICs'
 * '<S268>' : 'Thesis_C__/waypoint tracking/PID Controller1/I Gain'
 * '<S269>' : 'Thesis_C__/waypoint tracking/PID Controller1/Ideal P Gain'
 * '<S270>' : 'Thesis_C__/waypoint tracking/PID Controller1/Ideal P Gain Fdbk'
 * '<S271>' : 'Thesis_C__/waypoint tracking/PID Controller1/Integrator'
 * '<S272>' : 'Thesis_C__/waypoint tracking/PID Controller1/Integrator ICs'
 * '<S273>' : 'Thesis_C__/waypoint tracking/PID Controller1/N Copy'
 * '<S274>' : 'Thesis_C__/waypoint tracking/PID Controller1/N Gain'
 * '<S275>' : 'Thesis_C__/waypoint tracking/PID Controller1/P Copy'
 * '<S276>' : 'Thesis_C__/waypoint tracking/PID Controller1/Parallel P Gain'
 * '<S277>' : 'Thesis_C__/waypoint tracking/PID Controller1/Reset Signal'
 * '<S278>' : 'Thesis_C__/waypoint tracking/PID Controller1/Saturation'
 * '<S279>' : 'Thesis_C__/waypoint tracking/PID Controller1/Saturation Fdbk'
 * '<S280>' : 'Thesis_C__/waypoint tracking/PID Controller1/Sum'
 * '<S281>' : 'Thesis_C__/waypoint tracking/PID Controller1/Sum Fdbk'
 * '<S282>' : 'Thesis_C__/waypoint tracking/PID Controller1/Tracking Mode'
 * '<S283>' : 'Thesis_C__/waypoint tracking/PID Controller1/Tracking Mode Sum'
 * '<S284>' : 'Thesis_C__/waypoint tracking/PID Controller1/Tsamp - Integral'
 * '<S285>' : 'Thesis_C__/waypoint tracking/PID Controller1/Tsamp - Ngain'
 * '<S286>' : 'Thesis_C__/waypoint tracking/PID Controller1/postSat Signal'
 * '<S287>' : 'Thesis_C__/waypoint tracking/PID Controller1/preInt Signal'
 * '<S288>' : 'Thesis_C__/waypoint tracking/PID Controller1/preSat Signal'
 * '<S289>' : 'Thesis_C__/waypoint tracking/PID Controller1/Anti-windup/Passthrough'
 * '<S290>' : 'Thesis_C__/waypoint tracking/PID Controller1/D Gain/Disabled'
 * '<S291>' : 'Thesis_C__/waypoint tracking/PID Controller1/External Derivative/Disabled'
 * '<S292>' : 'Thesis_C__/waypoint tracking/PID Controller1/Filter/Disabled'
 * '<S293>' : 'Thesis_C__/waypoint tracking/PID Controller1/Filter ICs/Disabled'
 * '<S294>' : 'Thesis_C__/waypoint tracking/PID Controller1/I Gain/Internal Parameters'
 * '<S295>' : 'Thesis_C__/waypoint tracking/PID Controller1/Ideal P Gain/Passthrough'
 * '<S296>' : 'Thesis_C__/waypoint tracking/PID Controller1/Ideal P Gain Fdbk/Disabled'
 * '<S297>' : 'Thesis_C__/waypoint tracking/PID Controller1/Integrator/Continuous'
 * '<S298>' : 'Thesis_C__/waypoint tracking/PID Controller1/Integrator ICs/Internal IC'
 * '<S299>' : 'Thesis_C__/waypoint tracking/PID Controller1/N Copy/Disabled wSignal Specification'
 * '<S300>' : 'Thesis_C__/waypoint tracking/PID Controller1/N Gain/Disabled'
 * '<S301>' : 'Thesis_C__/waypoint tracking/PID Controller1/P Copy/Disabled'
 * '<S302>' : 'Thesis_C__/waypoint tracking/PID Controller1/Parallel P Gain/Internal Parameters'
 * '<S303>' : 'Thesis_C__/waypoint tracking/PID Controller1/Reset Signal/Disabled'
 * '<S304>' : 'Thesis_C__/waypoint tracking/PID Controller1/Saturation/Passthrough'
 * '<S305>' : 'Thesis_C__/waypoint tracking/PID Controller1/Saturation Fdbk/Disabled'
 * '<S306>' : 'Thesis_C__/waypoint tracking/PID Controller1/Sum/Sum_PI'
 * '<S307>' : 'Thesis_C__/waypoint tracking/PID Controller1/Sum Fdbk/Disabled'
 * '<S308>' : 'Thesis_C__/waypoint tracking/PID Controller1/Tracking Mode/Disabled'
 * '<S309>' : 'Thesis_C__/waypoint tracking/PID Controller1/Tracking Mode Sum/Passthrough'
 * '<S310>' : 'Thesis_C__/waypoint tracking/PID Controller1/Tsamp - Integral/TsSignalSpecification'
 * '<S311>' : 'Thesis_C__/waypoint tracking/PID Controller1/Tsamp - Ngain/Passthrough'
 * '<S312>' : 'Thesis_C__/waypoint tracking/PID Controller1/postSat Signal/Forward_Path'
 * '<S313>' : 'Thesis_C__/waypoint tracking/PID Controller1/preInt Signal/Internal PreInt'
 * '<S314>' : 'Thesis_C__/waypoint tracking/PID Controller1/preSat Signal/Forward_Path'
 */
#endif                                 /* Thesis_C___h_ */
