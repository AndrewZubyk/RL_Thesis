/*
 * Thesis_C__.cpp
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

#include "Thesis_C__.h"
#include "Thesis_C___private.h"
#include <cmath>
#include "rtwtypes.h"
#include "cmath"
#include "zero_crossing_types.h"
#include "rt_defines.h"

real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

/*
 * This function updates continuous states using the ODE4 fixed-step
 * solver algorithm
 */
void Thesis_C__::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T t { rtsiGetT(si) };

  time_T tnew { rtsiGetSolverStopTime(si) };

  time_T h { rtsiGetStepSize(si) };

  real_T *x { rtsiGetContStates(si) };

  ODE4_IntgData *id { static_cast<ODE4_IntgData *>(rtsiGetSolverData(si)) };

  real_T *y { id->y };

  real_T *f0 { id->f[0] };

  real_T *f1 { id->f[1] };

  real_T *f2 { id->f[2] };

  real_T *f3 { id->f[3] };

  real_T temp;
  int_T i;
  int_T nXc { 17 };

  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Thesis_C___derivatives();

  /* f1 = f(t + (h/2), y + (h/2)*f0) */
  temp = 0.5 * h;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f0[i]);
  }

  rtsiSetT(si, t + temp);
  rtsiSetdX(si, f1);
  this->step();
  Thesis_C___derivatives();

  /* f2 = f(t + (h/2), y + (h/2)*f1) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (temp*f1[i]);
  }

  rtsiSetdX(si, f2);
  this->step();
  Thesis_C___derivatives();

  /* f3 = f(t + h, y + h*f2) */
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (h*f2[i]);
  }

  rtsiSetT(si, tnew);
  rtsiSetdX(si, f3);
  this->step();
  Thesis_C___derivatives();

  /* tnew = t + h
     ynew = y + (h/6)*(f0 + 2*f1 + 2*f2 + 2*f3) */
  temp = h / 6.0;
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + temp*(f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]);
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else {
    real_T tmp;
    real_T tmp_0;
    tmp = std::abs(u0);
    tmp_0 = std::abs(u1);
    if (std::isinf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = (rtNaN);
    } else {
      y = std::pow(u0, u1);
    }
  }

  return y;
}

real_T rt_atan2d_snf(real_T u0, real_T u1)
{
  real_T y;
  if (std::isnan(u0) || std::isnan(u1)) {
    y = (rtNaN);
  } else if (std::isinf(u0) && std::isinf(u1)) {
    int32_T tmp;
    int32_T tmp_0;
    if (u0 > 0.0) {
      tmp = 1;
    } else {
      tmp = -1;
    }

    if (u1 > 0.0) {
      tmp_0 = 1;
    } else {
      tmp_0 = -1;
    }

    y = std::atan2(static_cast<real_T>(tmp), static_cast<real_T>(tmp_0));
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = std::atan2(u0, u1);
  }

  return y;
}

uint32_T MWDSP_EPH_R_B(boolean_T evt, uint32_T *sta)
{
  uint32_T curState;
  uint32_T lastzcevent;
  uint32_T newState;
  uint32_T newStateR;
  uint32_T previousState;
  uint32_T retVal;

  /* S-Function (sdspcount2): '<S4>/Counter' */
  /* Detect rising edge events */
  previousState = *sta;
  retVal = 0U;
  lastzcevent = 0U;
  newState = 5U;
  newStateR = 5U;
  if (evt) {
    curState = 2U;
  } else {
    curState = 1U;
  }

  if (*sta == 5U) {
    newStateR = curState;
  } else if (curState != *sta) {
    if (*sta == 3U) {
      if (curState == 1U) {
        newStateR = 1U;
      } else {
        lastzcevent = 2U;
        previousState = 1U;
      }
    }

    if (previousState == 4U) {
      if (curState == 1U) {
        newStateR = 1U;
      } else {
        lastzcevent = 3U;
        previousState = 1U;
      }
    }

    if ((previousState == 1U) && (curState == 2U)) {
      retVal = 2U;
    }

    if (previousState == 0U) {
      retVal = 2U;
    }

    if (retVal == lastzcevent) {
      retVal = 0U;
    }

    if ((curState == 1U) && (retVal == 2U)) {
      newState = 3U;
    } else {
      newState = curState;
    }
  }

  if (newStateR != 5U) {
    *sta = newStateR;
    retVal = 0U;
  }

  if (newState != 5U) {
    *sta = newState;
  }

  /* End of S-Function (sdspcount2): '<S4>/Counter' */
  return retVal;
}

/* Model step function */
void Thesis_C__::step()
{
  /* local block i/o variables */
  real_T rtb_counter;
  if (rtmIsMajorTimeStep((&Thesis_C___M))) {
    /* set solver stop time */
    if (!((&Thesis_C___M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&Thesis_C___M)->solverInfo, (((&Thesis_C___M)
        ->Timing.clockTickH0 + 1) * (&Thesis_C___M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&Thesis_C___M)->solverInfo, (((&Thesis_C___M)
        ->Timing.clockTick0 + 1) * (&Thesis_C___M)->Timing.stepSize0 +
        (&Thesis_C___M)->Timing.clockTickH0 * (&Thesis_C___M)->Timing.stepSize0 *
        4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&Thesis_C___M))) {
    (&Thesis_C___M)->Timing.t[0] = rtsiGetT(&(&Thesis_C___M)->solverInfo);
  }

  {
    real_T rtb_MatrixConcatenation3[9];
    real_T rtb_Product1[3];
    real_T tmp_0[3];
    real_T (*lastU)[2];
    real_T EastDot_tmp;
    real_T EastDot_tmp_0;
    real_T EastDot_tmp_1;
    real_T NorthDot_tmp;
    real_T rtb_Del_Y;
    real_T rtb_Del_x;
    real_T rtb_Derivative_idx_0;
    real_T rtb_Jaxis;
    real_T rtb_Jaxis_j;
    real_T rtb_Product1_a;
    real_T rtb_Roll;
    real_T rtb_Sum_b;
    real_T rtb_bank;
    real_T rtb_bearrad;
    real_T rtb_cla;
    real_T rtb_heading;
    real_T rtb_iaxis;
    real_T rtb_iaxis_b;
    real_T rtb_kaxis;
    real_T rtb_kaxis_b;
    real_T rtb_pitch;
    real_T rtb_qintegrate;
    real_T rtb_rintegrate;
    real_T rtb_rintegrate_tmp;
    real_T rtb_switch2;
    int32_T i;
    int8_T rtAction;
    int8_T rtPrevAction;
    boolean_T didZcEventOccur;
    boolean_T rtb_Counter_o2;
    boolean_T tmp;

    /* RelationalOperator: '<Root>/Relational Operator' incorporates:
     *  Constant: '<Root>/Check'
     *  Inport: '<Root>/In1'
     */
    Thesis_C___B.RelationalOperator = (Thesis_C___U.In1[4] >
      Thesis_C___P.Check_Value);

    /* If: '<S2>/If' incorporates:
     *  Integrator: '<S24>/Alt'
     *  Integrator: '<S24>/East'
     *  Integrator: '<S24>/North'
     *  Integrator: '<S25>/u integrate'
     *  Integrator: '<S25>/v integrate'
     *  Integrator: '<S25>/w integrate'
     *  Integrator: '<S28>/bank'
     *  Integrator: '<S28>/heading'
     *  Integrator: '<S28>/pitch'
     *  Integrator: '<S29>/p integrate'
     *  Integrator: '<S29>/q integrate'
     */
    rtb_Counter_o2 = rtsiIsModeUpdateTimeStep(&(&Thesis_C___M)->solverInfo);

    /* Integrator: '<S24>/North' incorporates:
     *  Integrator: '<S24>/Alt'
     *  Integrator: '<S24>/East'
     *  Integrator: '<S25>/u integrate'
     *  Integrator: '<S25>/v integrate'
     *  Integrator: '<S25>/w integrate'
     *  Integrator: '<S28>/bank'
     *  Integrator: '<S28>/heading'
     *  Integrator: '<S28>/pitch'
     */
    if (rtb_Counter_o2) {
      didZcEventOccur = (((Thesis_C___PrevZCX.North_Reset_ZCE == POS_ZCSIG) !=
                          Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.North_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.North_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.North_CSTATE = Thesis_C___P.North_IC;
      }

      didZcEventOccur = (((Thesis_C___PrevZCX.East_Reset_ZCE == POS_ZCSIG) !=
                          Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.East_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.East_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.East_CSTATE = Thesis_C___P.East_IC;
      }

      didZcEventOccur = (((Thesis_C___PrevZCX.Alt_Reset_ZCE == POS_ZCSIG) !=
                          Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.Alt_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.Alt_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.Alt_CSTATE = Thesis_C___P.Alt_IC;
      }

      didZcEventOccur = (((Thesis_C___PrevZCX.bank_Reset_ZCE == POS_ZCSIG) !=
                          Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.bank_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.bank_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.bank_CSTATE = Thesis_C___P.initbank;
      }

      didZcEventOccur = (((Thesis_C___PrevZCX.pitch_Reset_ZCE == POS_ZCSIG) !=
                          Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.pitch_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.pitch_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.pitch_CSTATE = Thesis_C___P.pitch_IC;
      }

      didZcEventOccur = (((Thesis_C___PrevZCX.heading_Reset_ZCE == POS_ZCSIG) !=
                          Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.heading_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.heading_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.heading_CSTATE = Thesis_C___P.inithead;
      }

      didZcEventOccur = (((Thesis_C___PrevZCX.uintegrate_Reset_ZCE == POS_ZCSIG)
                          != Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.uintegrate_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.uintegrate_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.uintegrate_CSTATE = Thesis_C___P.uintegrate_IC;
      }

      didZcEventOccur = (((Thesis_C___PrevZCX.vintegrate_Reset_ZCE == POS_ZCSIG)
                          != Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.vintegrate_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.vintegrate_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.vintegrate_CSTATE = Thesis_C___P.initv;
      }

      didZcEventOccur = (((Thesis_C___PrevZCX.wintegrate_Reset_ZCE == POS_ZCSIG)
                          != Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.wintegrate_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.wintegrate_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.wintegrate_CSTATE = Thesis_C___P.initw;
      }
    }

    rtb_Del_x = Thesis_C___X.North_CSTATE;

    /* Integrator: '<S24>/East' */
    rtb_Del_Y = Thesis_C___X.East_CSTATE;

    /* Integrator: '<S24>/Alt' */
    rtb_switch2 = Thesis_C___X.Alt_CSTATE;

    /* Integrator: '<S28>/bank' */
    rtb_bank = Thesis_C___X.bank_CSTATE;

    /* Integrator: '<S28>/pitch' */
    rtb_pitch = Thesis_C___X.pitch_CSTATE;

    /* Integrator: '<S28>/heading' */
    rtb_heading = Thesis_C___X.heading_CSTATE;

    /* Integrator: '<S25>/u integrate' */
    rtb_kaxis = Thesis_C___X.uintegrate_CSTATE;

    /* Integrator: '<S25>/v integrate' */
    rtb_Jaxis = Thesis_C___X.vintegrate_CSTATE;

    /* Integrator: '<S25>/w integrate' */
    rtb_iaxis = Thesis_C___X.wintegrate_CSTATE;

    /* Fcn: '<S9>/Get Airspeed' incorporates:
     *  Integrator: '<S25>/u integrate'
     *  Integrator: '<S25>/v integrate'
     *  Integrator: '<S25>/w integrate'
     */
    rtb_bearrad = std::sqrt((rt_powd_snf(Thesis_C___X.uintegrate_CSTATE, 2.0) +
      rt_powd_snf(Thesis_C___X.vintegrate_CSTATE, 2.0)) + rt_powd_snf
      (Thesis_C___X.wintegrate_CSTATE, 2.0));

    /* Fcn: '<S24>/Alttitude Dot' incorporates:
     *  Integrator: '<S25>/u integrate'
     *  Integrator: '<S25>/v integrate'
     *  Integrator: '<S25>/w integrate'
     *  Integrator: '<S28>/bank'
     *  Integrator: '<S28>/pitch'
     */
    Thesis_C___B.AlttitudeDot = (Thesis_C___X.uintegrate_CSTATE * std::sin
      (Thesis_C___X.pitch_CSTATE) - Thesis_C___X.vintegrate_CSTATE * std::sin
      (Thesis_C___X.bank_CSTATE) * std::cos(Thesis_C___X.pitch_CSTATE)) -
      Thesis_C___X.wintegrate_CSTATE * std::cos(Thesis_C___X.bank_CSTATE) * std::
      cos(Thesis_C___X.pitch_CSTATE);

    /* Outport: '<Root>/Out1' incorporates:
     *  Constant: '<Root>/v(y)'
     *  DataTypeConversion: '<Root>/Data Type Conversion'
     *  Fcn: '<S9>/Get Airspeed'
     *  Gain: '<Root>/Gain'
     *  Integrator: '<S24>/Alt'
     *  Integrator: '<S24>/East'
     *  Integrator: '<S24>/North'
     *  Integrator: '<S28>/bank'
     *  Integrator: '<S28>/heading'
     *  Integrator: '<S28>/pitch'
     */
    Thesis_C___Y.Out1[0] = static_cast<real32_T>(Thesis_C___X.North_CSTATE);
    Thesis_C___Y.Out1[1] = static_cast<real32_T>(Thesis_C___X.East_CSTATE);
    Thesis_C___Y.Out1[2] = static_cast<real32_T>(Thesis_C___X.Alt_CSTATE);
    Thesis_C___Y.Out1[3] = static_cast<real32_T>(Thesis_C___X.bank_CSTATE);
    Thesis_C___Y.Out1[4] = static_cast<real32_T>(Thesis_C___X.pitch_CSTATE);
    Thesis_C___Y.Out1[5] = static_cast<real32_T>(Thesis_C___X.heading_CSTATE);
    Thesis_C___Y.Out1[6] = static_cast<real32_T>(rtb_bearrad);
    Thesis_C___Y.Out1[7] = static_cast<real32_T>(Thesis_C___P.vy_Value);
    Thesis_C___Y.Out1[8] = static_cast<real32_T>(Thesis_C___P.Gain_Gain *
      Thesis_C___B.AlttitudeDot);

    /* Fcn: '<S9>/Get AoA' incorporates:
     *  Integrator: '<S25>/u integrate'
     *  Integrator: '<S25>/w integrate'
     */
    Thesis_C___B.GetAoA = std::atan(Thesis_C___X.wintegrate_CSTATE /
      Thesis_C___X.uintegrate_CSTATE);

    /* Saturate: '<S9>/AoA Sat' */
    if (Thesis_C___B.GetAoA > Thesis_C___P.AoASat_UpperSat) {
      rtb_Roll = Thesis_C___P.AoASat_UpperSat;
    } else if (Thesis_C___B.GetAoA < Thesis_C___P.AoASat_LowerSat) {
      rtb_Roll = Thesis_C___P.AoASat_LowerSat;
    } else {
      rtb_Roll = Thesis_C___B.GetAoA;
    }

    /* End of Saturate: '<S9>/AoA Sat' */

    /* Fcn: '<S9>/Get Beta' incorporates:
     *  Integrator: '<S25>/u integrate'
     *  Integrator: '<S25>/v integrate'
     *  Integrator: '<S25>/w integrate'
     */
    rtb_qintegrate = Thesis_C___X.vintegrate_CSTATE / std::sqrt((rt_powd_snf
      (Thesis_C___X.uintegrate_CSTATE, 2.0) + rt_powd_snf
      (Thesis_C___X.vintegrate_CSTATE, 2.0)) + rt_powd_snf
      (Thesis_C___X.wintegrate_CSTATE, 2.0));
    if (rtb_qintegrate > 1.0) {
      rtb_qintegrate = 1.0;
    } else if (rtb_qintegrate < -1.0) {
      rtb_qintegrate = -1.0;
    }

    /* Fcn: '<S9>/Get Beta' */
    Thesis_C___B.GetBeta = std::asin(rtb_qintegrate);

    /* Saturate: '<S9>/Beta Sat' */
    if (Thesis_C___B.GetBeta > Thesis_C___P.BetaSat_UpperSat) {
      rtb_kaxis_b = Thesis_C___P.BetaSat_UpperSat;
    } else if (Thesis_C___B.GetBeta < Thesis_C___P.BetaSat_LowerSat) {
      rtb_kaxis_b = Thesis_C___P.BetaSat_LowerSat;
    } else {
      rtb_kaxis_b = Thesis_C___B.GetBeta;
    }

    /* End of Saturate: '<S9>/Beta Sat' */

    /* Fcn: '<S22>/-ca sb' incorporates:
     *  Fcn: '<S22>/-sa sb'
     *  Fcn: '<S22>/Fcn8'
     *  Fcn: '<S22>/ca cb'
     *  Fcn: '<S22>/sb'
     */
    rtb_qintegrate = std::sin(rtb_kaxis_b);
    rtb_Product1_a = std::cos(rtb_Roll);
    rtb_MatrixConcatenation3[1] = -rtb_Product1_a * rtb_qintegrate;

    /* Fcn: '<S22>/-sa' incorporates:
     *  Fcn: '<S22>/-sa sb'
     *  Fcn: '<S22>/sa cb'
     */
    rtb_cla = std::sin(rtb_Roll);
    rtb_MatrixConcatenation3[2] = -rtb_cla;

    /* Fcn: '<S22>/-sa sb' */
    rtb_MatrixConcatenation3[7] = -rtb_cla * rtb_qintegrate;

    /* Fcn: '<S22>/Fcn8' */
    rtb_MatrixConcatenation3[8] = rtb_Product1_a;

    /* Fcn: '<S22>/ca cb' incorporates:
     *  Fcn: '<S22>/cb'
     *  Fcn: '<S22>/sa cb'
     */
    rtb_Sum_b = std::cos(rtb_kaxis_b);
    rtb_MatrixConcatenation3[0] = rtb_Product1_a * rtb_Sum_b;

    /* Fcn: '<S22>/sb' */
    rtb_MatrixConcatenation3[3] = rtb_qintegrate;

    /* Fcn: '<S22>/cb' */
    rtb_MatrixConcatenation3[4] = rtb_Sum_b;

    /* Fcn: '<S22>/zero' */
    rtb_MatrixConcatenation3[5] = rtb_Roll * 0.0;

    /* Fcn: '<S22>/sa cb' */
    rtb_MatrixConcatenation3[6] = rtb_cla * rtb_Sum_b;

    /* Gain: '<S20>/Gain' incorporates:
     *  Constant: '<S14>/cdo'
     *  Gain: '<S14>/cda2'
     *  Math: '<S14>/Math Function'
     *  Sum: '<S14>/Sum'
     */
    rtb_Jaxis_j = (rtb_Roll * rtb_Roll * Thesis_C___P.cda2 + Thesis_C___P.cdo) *
      Thesis_C___P.Gain_Gain_n;

    /* Gain: '<S15>/cla' */
    rtb_cla = Thesis_C___P.cla * rtb_Roll;

    /* Derivative: '<S9>/Derivative' */
    rtb_Sum_b = (&Thesis_C___M)->Timing.t[0];
    if ((Thesis_C___DW.TimeStampA >= rtb_Sum_b) && (Thesis_C___DW.TimeStampB >=
         rtb_Sum_b)) {
      rtb_Derivative_idx_0 = 0.0;
    } else {
      rtb_qintegrate = Thesis_C___DW.TimeStampA;
      lastU = &Thesis_C___DW.LastUAtTimeA;
      if (Thesis_C___DW.TimeStampA < Thesis_C___DW.TimeStampB) {
        if (Thesis_C___DW.TimeStampB < rtb_Sum_b) {
          rtb_qintegrate = Thesis_C___DW.TimeStampB;
          lastU = &Thesis_C___DW.LastUAtTimeB;
        }
      } else if (Thesis_C___DW.TimeStampA >= rtb_Sum_b) {
        rtb_qintegrate = Thesis_C___DW.TimeStampB;
        lastU = &Thesis_C___DW.LastUAtTimeB;
      }

      rtb_Derivative_idx_0 = (Thesis_C___B.GetAoA - (*lastU)[0]) / (rtb_Sum_b -
        rtb_qintegrate);
    }

    /* End of Derivative: '<S9>/Derivative' */

    /* Integrator: '<S29>/q integrate' */
    if (rtb_Counter_o2) {
      didZcEventOccur = (((Thesis_C___PrevZCX.qintegrate_Reset_ZCE == POS_ZCSIG)
                          != Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.qintegrate_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.qintegrate_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.qintegrate_CSTATE = Thesis_C___P.initq;
      }
    }

    rtb_qintegrate = Thesis_C___X.qintegrate_CSTATE;

    /* Saturate: '<S9>/Airspeed Sat' incorporates:
     *  Fcn: '<S9>/Get Airspeed'
     */
    if (rtb_bearrad > Thesis_C___P.AirspeedSat_UpperSat) {
      rtb_Product1_a = Thesis_C___P.AirspeedSat_UpperSat;
    } else if (rtb_bearrad < Thesis_C___P.AirspeedSat_LowerSat) {
      rtb_Product1_a = Thesis_C___P.AirspeedSat_LowerSat;
    } else {
      rtb_Product1_a = rtb_bearrad;
    }

    /* End of Saturate: '<S9>/Airspeed Sat' */

    /* Fcn: '<S15>/Fcn' incorporates:
     *  Fcn: '<S16>/Fcn'
     *  Fcn: '<S17>/Fcn'
     *  Fcn: '<S19>/Fcn1'
     *  Gain: '<S15>/cladot'
     *  Gain: '<S15>/clq'
     *  Integrator: '<S29>/q integrate'
     */
    rtb_rintegrate_tmp = 2.0 * rtb_Product1_a;
    rtb_rintegrate = (Thesis_C___P.cladot * rtb_Derivative_idx_0 +
                      Thesis_C___P.clq * Thesis_C___X.qintegrate_CSTATE) * 5.7 /
      rtb_rintegrate_tmp;
    tmp = rtmIsMajorTimeStep((&Thesis_C___M));
    if (tmp) {
      /* MultiPortSwitch: '<S4>/Multiport Switch' incorporates:
       *  Memory: '<S4>/Memory'
       */
      switch (static_cast<int32_T>(Thesis_C___DW.Memory_PreviousInput)) {
       case 1:
        /* MultiPortSwitch: '<S4>/Multiport Switch' incorporates:
         *  Constant: '<S4>/WP1'
         */
        Thesis_C___B.activewaypoint[0] = Thesis_C___P.wp.a[0];
        Thesis_C___B.activewaypoint[1] = Thesis_C___P.wp.a[1];
        Thesis_C___B.activewaypoint[2] = Thesis_C___P.wp.a[2];
        break;

       case 2:
        /* MultiPortSwitch: '<S4>/Multiport Switch' incorporates:
         *  Constant: '<S4>/WP2'
         */
        Thesis_C___B.activewaypoint[0] = Thesis_C___P.wp.b[0];
        Thesis_C___B.activewaypoint[1] = Thesis_C___P.wp.b[1];
        Thesis_C___B.activewaypoint[2] = Thesis_C___P.wp.b[2];
        break;

       default:
        /* MultiPortSwitch: '<S4>/Multiport Switch' incorporates:
         *  Constant: '<S4>/WP3'
         */
        Thesis_C___B.activewaypoint[0] = Thesis_C___P.wp.c[0];
        Thesis_C___B.activewaypoint[1] = Thesis_C___P.wp.c[1];
        Thesis_C___B.activewaypoint[2] = Thesis_C___P.wp.c[2];
        break;
      }

      /* End of MultiPortSwitch: '<S4>/Multiport Switch' */

      /* ManualSwitch: '<Root>/Manual Switch' */
      if (Thesis_C___P.ManualSwitch_CurrentSetting == 1) {
        /* ManualSwitch: '<Root>/Manual Switch' */
        Thesis_C___B.ManualSwitch = 0.0;
      } else {
        /* ManualSwitch: '<Root>/Manual Switch' */
        Thesis_C___B.ManualSwitch = Thesis_C___B.activewaypoint[2];
      }

      /* End of ManualSwitch: '<Root>/Manual Switch' */
    }

    /* Sum: '<S2>/Sum2' incorporates:
     *  Integrator: '<S24>/Alt'
     */
    Thesis_C___B.h_err = Thesis_C___X.Alt_CSTATE - Thesis_C___B.ManualSwitch;

    /* If: '<S2>/If' */
    rtPrevAction = Thesis_C___DW.If_ActiveSubsystem;
    if (rtb_Counter_o2) {
      if (Thesis_C___B.h_err < -100.0) {
        rtAction = 0;
      } else if (Thesis_C___B.h_err > 100.0) {
        rtAction = 1;
      } else {
        rtAction = 2;
      }

      Thesis_C___DW.If_ActiveSubsystem = rtAction;
    } else {
      rtAction = Thesis_C___DW.If_ActiveSubsystem;
    }

    if (rtPrevAction != rtAction) {
      rtsiSetBlockStateForSolverChangedAtMajorStep(&(&Thesis_C___M)->solverInfo,
        true);
      if ((&Thesis_C___M)->Timing.t[0] == rtmGetTStart((&Thesis_C___M))) {
        (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_k), 1,
                           1*sizeof(boolean_T));
        (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_n), 1,
                           1*sizeof(boolean_T));
        (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_h), 1,
                           1*sizeof(boolean_T));
      }

      switch (rtPrevAction) {
       case 0:
        (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_k), 1,
                           1*sizeof(boolean_T));
        break;

       case 1:
        (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_n), 1,
                           1*sizeof(boolean_T));
        break;

       case 2:
        (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_h), 1,
                           1*sizeof(boolean_T));
        break;
      }
    }

    switch (rtAction) {
     case 0:
      if (rtAction != rtPrevAction) {
        /* Enable for IfAction SubSystem: '<S2>/Climb' incorporates:
         *  ActionPort: '<S36>/Action Port'
         */
        /* Enable for If: '<S2>/If' */
        (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_k), 0,
                           1*sizeof(boolean_T));

        /* End of Enable for SubSystem: '<S2>/Climb' */
      }

      /* Outputs for IfAction SubSystem: '<S2>/Climb' incorporates:
       *  ActionPort: '<S36>/Action Port'
       */
      /* Sum: '<S36>/Sum' incorporates:
       *  Constant: '<S36>/RoC_CMD'
       */
      rtb_Sum_b = Thesis_C___B.AlttitudeDot - Thesis_C___P.RoC_CMD_Value;

      /* Gain: '<S71>/Integral Gain' */
      Thesis_C___B.IntegralGain_mn = Thesis_C___P.PIDController_I * rtb_Sum_b;

      /* Sum: '<S83>/Sum' incorporates:
       *  Gain: '<S79>/Proportional Gain'
       *  Integrator: '<S74>/Integrator'
       */
      rtb_iaxis_b = Thesis_C___P.PIDController_P * rtb_Sum_b +
        Thesis_C___X.Integrator_CSTATE_k;

      /* End of Outputs for SubSystem: '<S2>/Climb' */
      break;

     case 1:
      if (rtAction != rtPrevAction) {
        /* Enable for IfAction SubSystem: '<S2>/Decend' incorporates:
         *  ActionPort: '<S37>/Action Port'
         */
        /* Enable for If: '<S2>/If' */
        (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_n), 0,
                           1*sizeof(boolean_T));

        /* End of Enable for SubSystem: '<S2>/Decend' */
      }

      /* Outputs for IfAction SubSystem: '<S2>/Decend' incorporates:
       *  ActionPort: '<S37>/Action Port'
       */
      /* Sum: '<S37>/Sum' incorporates:
       *  Constant: '<S37>/RoC_CMD'
       */
      rtb_Sum_b = Thesis_C___B.AlttitudeDot - Thesis_C___P.RoC_CMD_Value_e;

      /* Gain: '<S124>/Integral Gain' */
      Thesis_C___B.IntegralGain_e = Thesis_C___P.PIDController_I_o * rtb_Sum_b;

      /* Sum: '<S136>/Sum' incorporates:
       *  Gain: '<S132>/Proportional Gain'
       *  Integrator: '<S127>/Integrator'
       */
      rtb_iaxis_b = Thesis_C___P.PIDController_P_n * rtb_Sum_b +
        Thesis_C___X.Integrator_CSTATE_n;

      /* End of Outputs for SubSystem: '<S2>/Decend' */
      break;

     default:
      if (rtAction != rtPrevAction) {
        /* Enable for IfAction SubSystem: '<S2>/Level' incorporates:
         *  ActionPort: '<S38>/Action Port'
         */
        /* Enable for If: '<S2>/If' */
        (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_h), 0,
                           1*sizeof(boolean_T));

        /* End of Enable for SubSystem: '<S2>/Level' */
      }

      /* Outputs for IfAction SubSystem: '<S2>/Level' incorporates:
       *  ActionPort: '<S38>/Action Port'
       */
      /* Gain: '<S177>/Integral Gain' */
      Thesis_C___B.IntegralGain_l = Thesis_C___P.PIDController_I_a *
        Thesis_C___B.h_err;

      /* Sum: '<S189>/Sum' incorporates:
       *  Gain: '<S185>/Proportional Gain'
       *  Integrator: '<S180>/Integrator'
       */
      rtb_iaxis_b = Thesis_C___P.PIDController_P_b * Thesis_C___B.h_err +
        Thesis_C___X.Integrator_CSTATE_h;

      /* End of Outputs for SubSystem: '<S2>/Level' */
      break;
    }

    /* ManualSwitch: '<Root>/switch' incorporates:
     *  Constant: '<Root>/Elevator'
     *  Inport: '<Root>/In1'
     */
    if (Thesis_C___P.switch_CurrentSetting == 1) {
      EastDot_tmp = Thesis_C___U.In1[0];
    } else {
      EastDot_tmp = Thesis_C___P.Elevator_Value;
    }

    /* ManualSwitch: '<Root>/longitudinal autopilot' incorporates:
     *  Constant: '<Root>/Constant1'
     */
    if (Thesis_C___P.longitudinalautopilot_CurrentSe == 1) {
      rtb_iaxis_b = Thesis_C___P.Constant1_Value;
    }

    /* Sum: '<Root>/Sum' incorporates:
     *  ManualSwitch: '<Root>/longitudinal autopilot'
     *  ManualSwitch: '<Root>/switch'
     */
    rtb_iaxis_b = EastDot_tmp - rtb_iaxis_b;

    /* Gain: '<S20>/Gain1' incorporates:
     *  Constant: '<S15>/clo'
     *  Gain: '<S15>/clde'
     *  Sum: '<S15>/Sum'
     */
    rtb_cla = (((Thesis_C___P.clo + rtb_cla) + rtb_rintegrate) +
               Thesis_C___P.clde * rtb_iaxis_b) * Thesis_C___P.Gain1_Gain;

    /* Fcn: '<S12>/Density' */
    rtb_Sum_b = 1.0 - 7.03e-6 * rtb_switch2;
    if (rtb_Sum_b < 0.0) {
      EastDot_tmp = -rt_powd_snf(-rtb_Sum_b, 4.14);
    } else {
      EastDot_tmp = rt_powd_snf(rtb_Sum_b, 4.14);
    }

    /* Fcn: '<S9>/Get Mach1' incorporates:
     *  Fcn: '<S12>/Density'
     *  Fcn: '<S9>/Get Airspeed'
     */
    rtb_Sum_b = 0.5 * rt_powd_snf(rtb_bearrad, 2.0) * (0.0023769 * EastDot_tmp);

    /* Gain: '<S20>/Gain2' */
    rtb_rintegrate = Thesis_C___P.sw * rtb_Sum_b;

    /* ManualSwitch: '<Root>/switch2' incorporates:
     *  Constant: '<Root>/Rudder'
     *  Inport: '<Root>/In1'
     */
    if (Thesis_C___P.switch2_CurrentSetting == 1) {
      rtb_switch2 = Thesis_C___U.In1[2];
    } else {
      rtb_switch2 = Thesis_C___P.Rudder_Value;
    }

    /* End of ManualSwitch: '<Root>/switch2' */

    /* Product: '<S20>/Product' incorporates:
     *  Gain: '<S18>/cyb'
     *  Gain: '<S18>/cydr'
     *  Sum: '<S18>/Sum'
     */
    rtb_Jaxis_j *= rtb_rintegrate;
    rtb_bearrad = (Thesis_C___P.cyb * rtb_kaxis_b + Thesis_C___P.cydr *
                   rtb_switch2) * rtb_rintegrate;
    rtb_cla *= rtb_rintegrate;

    /* Product: '<S20>/Product1' incorporates:
     *  Concatenate: '<S27>/Matrix Concatenation3'
     *  Math: '<S20>/Math Function'
     */
    for (i = 0; i < 3; i++) {
      rtb_Product1[i] = (rtb_MatrixConcatenation3[3 * i + 1] * rtb_bearrad +
                         rtb_MatrixConcatenation3[3 * i] * rtb_Jaxis_j) +
        rtb_MatrixConcatenation3[3 * i + 2] * rtb_cla;
    }

    /* End of Product: '<S20>/Product1' */

    /* Fcn: '<S21>/Pitch' incorporates:
     *  Fcn: '<S16>/Fcn'
     *  Fcn: '<S21>/Roll'
     *  Gain: '<S16>/cma'
     *  Gain: '<S16>/cmadot'
     *  Gain: '<S16>/cmde'
     *  Gain: '<S16>/cmq'
     *  Sum: '<S16>/Sum'
     */
    rtb_Sum_b *= 184.0;
    rtb_cla = (((Thesis_C___P.cmadot * rtb_Derivative_idx_0 + Thesis_C___P.cmq *
                 rtb_qintegrate) * 5.7 / rtb_rintegrate_tmp + Thesis_C___P.cma *
                rtb_Roll) + Thesis_C___P.cmde * rtb_iaxis_b) * (rtb_Sum_b * 5.7);

    /* Integrator: '<S29>/p integrate' incorporates:
     *  Integrator: '<S29>/r integrate'
     */
    if (rtb_Counter_o2) {
      didZcEventOccur = (((Thesis_C___PrevZCX.pintegrate_Reset_ZCE == POS_ZCSIG)
                          != Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.pintegrate_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.pintegrate_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.pintegrate_CSTATE = Thesis_C___P.initp;
      }

      didZcEventOccur = (((Thesis_C___PrevZCX.rintegrate_Reset_ZCE == POS_ZCSIG)
                          != Thesis_C___B.RelationalOperator) &&
                         (Thesis_C___PrevZCX.rintegrate_Reset_ZCE !=
                          UNINITIALIZED_ZCSIG));
      Thesis_C___PrevZCX.rintegrate_Reset_ZCE = Thesis_C___B.RelationalOperator;

      /* evaluate zero-crossings and the level of the reset signal */
      if (didZcEventOccur || Thesis_C___B.RelationalOperator) {
        Thesis_C___X.rintegrate_CSTATE = Thesis_C___P.initr;
      }
    }

    /* Trigonometry: '<S202>/Bearing' incorporates:
     *  Sum: '<S202>/Del_x'
     *  Sum: '<S202>/Del_y'
     */
    rtb_bearrad = rt_atan2d_snf(Thesis_C___B.activewaypoint[1] - rtb_Del_Y,
      Thesis_C___B.activewaypoint[0] - rtb_Del_x);

    /* MATLAB Function: '<S202>/0 to 2pi' */
    /* MATLAB Function 'Waypoints/Rel_bearing/old relative bearing/0 to 2pi': '<S203>:1' */
    /* '<S203>:1:6' */
    if (std::isnan(rtb_bearrad) || std::isinf(rtb_bearrad)) {
      rtb_Roll = (rtNaN);
    } else {
      rtb_Roll = std::abs(rtb_bearrad / 6.2831853071795862);
      if (std::abs(rtb_Roll - std::floor(rtb_Roll + 0.5)) >
          2.2204460492503131E-16 * rtb_Roll) {
        rtb_Roll = std::fmod(rtb_bearrad, 6.2831853071795862);
      } else {
        rtb_Roll = 0.0;
      }

      if (rtb_Roll == 0.0) {
        rtb_Roll = 0.0;
      } else if (rtb_Roll < 0.0) {
        rtb_Roll += 6.2831853071795862;
      }
    }

    /* End of MATLAB Function: '<S202>/0 to 2pi' */

    /* Sum: '<S202>/Rel_bearing' */
    rtb_bearrad = rtb_Roll - rtb_heading;

    /* MATLAB Function: '<S202>/pibound' */
    /* MATLAB Function 'Waypoints/Rel_bearing/old relative bearing/pibound': '<S207>:1' */
    /* '<S207>:1:6' */
    if (std::isnan(rtb_bearrad + 3.1415926535897931) || std::isinf(rtb_bearrad +
         3.1415926535897931)) {
      rtb_Roll = (rtNaN);
    } else {
      rtb_Roll = std::abs((rtb_bearrad + 3.1415926535897931) /
                          6.2831853071795862);
      if (std::abs(rtb_Roll - std::floor(rtb_Roll + 0.5)) >
          2.2204460492503131E-16 * rtb_Roll) {
        rtb_Roll = std::fmod(rtb_bearrad + 3.1415926535897931,
                             6.2831853071795862);
      } else {
        rtb_Roll = 0.0;
      }

      if (rtb_Roll == 0.0) {
        rtb_Roll = 0.0;
      } else if (rtb_Roll < 0.0) {
        rtb_Roll += 6.2831853071795862;
      }
    }

    /* Sum: '<S5>/Sum' incorporates:
     *  Gain: '<S198>/Gain'
     *  Gain: '<S208>/Gain1'
     *  Integrator: '<S29>/p integrate'
     *  Lookup_n-D: '<S5>/1-D Lookup Table2'
     *  Lookup_n-D: '<S5>/1-D Lookup Table3'
     *  MATLAB Function: '<S202>/pibound'
     *  Sum: '<S5>/Sum1'
     */
    rtb_rintegrate = Thesis_C___X.pintegrate_CSTATE - look1_binlxpw(rtb_bank -
      look1_binlxpw((rtb_Roll - 3.1415926535897931) * Thesis_C___P.Gain_Gain_o *
                    Thesis_C___P.Gain1_Gain_g,
                    Thesis_C___P.uDLookupTable2_bp01Data,
                    Thesis_C___P.uDLookupTable2_tableData, 628U),
      Thesis_C___P.uDLookupTable3_bp01Data,
      Thesis_C___P.uDLookupTable3_tableData, 628U);

    /* ManualSwitch: '<Root>/switch1' incorporates:
     *  Constant: '<Root>/Aileron'
     *  Inport: '<Root>/In1'
     */
    if (Thesis_C___P.switch1_CurrentSetting == 1) {
      EastDot_tmp = Thesis_C___U.In1[1];
    } else {
      EastDot_tmp = Thesis_C___P.Aileron_Value;
    }

    /* ManualSwitch: '<Root>/track waypoints' incorporates:
     *  Constant: '<Root>/Constant2'
     *  Gain: '<S302>/Proportional Gain'
     *  Integrator: '<S297>/Integrator'
     *  Sum: '<S306>/Sum'
     */
    if (Thesis_C___P.trackwaypoints_CurrentSetting == 1) {
      rtb_Roll = Thesis_C___P.PIDController1_P * rtb_rintegrate +
        Thesis_C___X.Integrator_CSTATE;
    } else {
      rtb_Roll = Thesis_C___P.Constant2_Value;
    }

    /* Sum: '<Root>/Sum3' incorporates:
     *  ManualSwitch: '<Root>/switch1'
     *  ManualSwitch: '<Root>/track waypoints'
     */
    rtb_Jaxis_j = EastDot_tmp - rtb_Roll;

    /* Fcn: '<S21>/Roll' incorporates:
     *  Fcn: '<S19>/Fcn1'
     *  Fcn: '<S21>/Yaw'
     *  Gain: '<S19>/clb'
     *  Gain: '<S19>/clda'
     *  Gain: '<S19>/cldr'
     *  Gain: '<S19>/clp'
     *  Gain: '<S19>/clr'
     *  Integrator: '<S29>/p integrate'
     *  Integrator: '<S29>/r integrate'
     *  Sum: '<S19>/Sum'
     */
    rtb_Sum_b *= 33.4;
    rtb_Roll = ((((Thesis_C___P.clp * Thesis_C___X.pintegrate_CSTATE +
                   Thesis_C___P.clr * Thesis_C___X.rintegrate_CSTATE) * 33.4 /
                  rtb_rintegrate_tmp + Thesis_C___P.clb * rtb_kaxis_b) +
                 Thesis_C___P.clda * rtb_Jaxis_j) + Thesis_C___P.cldr *
                rtb_switch2) * rtb_Sum_b;

    /* Fcn: '<S21>/Yaw' incorporates:
     *  Fcn: '<S17>/Fcn'
     *  Gain: '<S17>/cnb'
     *  Gain: '<S17>/cnda'
     *  Gain: '<S17>/cndr'
     *  Gain: '<S17>/cnp'
     *  Gain: '<S17>/cnr'
     *  Integrator: '<S29>/p integrate'
     *  Integrator: '<S29>/r integrate'
     *  Sum: '<S17>/Sum'
     */
    rtb_Sum_b *= (((Thesis_C___P.cnp * Thesis_C___X.pintegrate_CSTATE +
                    Thesis_C___P.cnr * Thesis_C___X.rintegrate_CSTATE) * 33.4 /
                   rtb_rintegrate_tmp + Thesis_C___P.cnb * rtb_kaxis_b) +
                  Thesis_C___P.cnda * rtb_Jaxis_j) + Thesis_C___P.cndr *
      rtb_switch2;

    /* ManualSwitch: '<Root>/switch3' incorporates:
     *  Constant: '<Root>/Throttle'
     *  Inport: '<Root>/In1'
     */
    if (Thesis_C___P.switch3_CurrentSetting == 1) {
      EastDot_tmp = Thesis_C___U.In1[3];
    } else {
      EastDot_tmp = Thesis_C___P.Throttle_Value;
    }

    /* Product: '<S7>/Product1' incorporates:
     *  Constant: '<S7>/Max Power'
     *  ManualSwitch: '<Root>/switch3'
     *  Product: '<S7>/Product'
     */
    rtb_Product1_a = EastDot_tmp * Thesis_C___P.MaxPower_Value / rtb_Product1_a;

    /* Fcn: '<S24>/East Dot' incorporates:
     *  Fcn: '<S24>/North Dot'
     *  Fcn: '<S27>/11'
     *  Fcn: '<S27>/12'
     *  Fcn: '<S27>/13'
     *  Fcn: '<S27>/21'
     *  Fcn: '<S27>/22'
     *  Fcn: '<S27>/23'
     *  Fcn: '<S27>/31'
     *  Fcn: '<S27>/32'
     *  Fcn: '<S27>/33'
     *  Fcn: '<S28>/Yaw rate'
     *  Fcn: '<S28>/pitch rate'
     *  Fcn: '<S28>/roll rate'
     */
    rtb_kaxis_b = std::sin(rtb_heading);
    rtb_switch2 = std::sin(rtb_bank);
    rtb_heading = std::cos(rtb_heading);
    rtb_bank = std::cos(rtb_bank);
    rtb_bearrad = std::sin(rtb_pitch);
    rtb_Jaxis_j = std::cos(rtb_pitch);
    rtb_rintegrate_tmp = rtb_switch2 * rtb_bearrad;
    EastDot_tmp = rtb_rintegrate_tmp * rtb_kaxis_b;
    rtb_Derivative_idx_0 = rtb_kaxis * rtb_Jaxis_j;
    EastDot_tmp_0 = rtb_bank * rtb_bearrad;
    rtb_iaxis_b = rtb_bank * rtb_heading + EastDot_tmp;
    EastDot_tmp_1 = EastDot_tmp_0 * rtb_kaxis_b + -rtb_switch2 * rtb_heading;

    /* Fcn: '<S24>/East Dot' */
    Thesis_C___B.EastDot = (rtb_iaxis_b * rtb_Jaxis + rtb_Derivative_idx_0 *
      rtb_kaxis_b) + EastDot_tmp_1 * rtb_iaxis;

    /* Fcn: '<S24>/North Dot' incorporates:
     *  Fcn: '<S27>/12'
     *  Fcn: '<S27>/13'
     */
    NorthDot_tmp = -rtb_bank * rtb_kaxis_b;
    EastDot_tmp_0 = EastDot_tmp_0 * rtb_heading + rtb_switch2 * rtb_kaxis_b;

    /* Fcn: '<S24>/North Dot' */
    Thesis_C___B.NorthDot = ((EastDot_tmp + NorthDot_tmp) * rtb_Jaxis +
      rtb_Derivative_idx_0 * rtb_heading) + EastDot_tmp_0 * rtb_iaxis;

    /* Fcn: '<S27>/11' */
    rtb_MatrixConcatenation3[0] = rtb_Jaxis_j * rtb_heading;

    /* Fcn: '<S27>/12' */
    rtb_MatrixConcatenation3[1] = rtb_rintegrate_tmp * rtb_heading +
      NorthDot_tmp;

    /* Fcn: '<S27>/13' */
    rtb_MatrixConcatenation3[2] = EastDot_tmp_0;

    /* Fcn: '<S27>/21' */
    rtb_MatrixConcatenation3[3] = rtb_Jaxis_j * rtb_kaxis_b;

    /* Fcn: '<S27>/22' */
    rtb_MatrixConcatenation3[4] = rtb_iaxis_b;

    /* Fcn: '<S27>/23' */
    rtb_MatrixConcatenation3[5] = EastDot_tmp_1;

    /* Fcn: '<S27>/31' */
    rtb_MatrixConcatenation3[6] = -rtb_bearrad;

    /* Fcn: '<S27>/32' */
    rtb_MatrixConcatenation3[7] = rtb_switch2 * rtb_Jaxis_j;

    /* Fcn: '<S27>/33' */
    rtb_MatrixConcatenation3[8] = rtb_bank * rtb_Jaxis_j;

    /* Product: '<S10>/F//m' incorporates:
     *  Constant: '<S11>/mass2'
     */
    rtb_bearrad = Thesis_C___P.weight / 32.2;

    /* SignalConversion generated from: '<S25>/Product' incorporates:
     *  Constant: '<S26>/Constant'
     *  Constant: '<S26>/Constant1'
     */
    tmp_0[0] = Thesis_C___P.Constant_Value;
    tmp_0[1] = Thesis_C___P.Constant_Value;
    tmp_0[2] = Thesis_C___P.Constant1_Value_a;

    /* Product: '<S25>/Product' incorporates:
     *  Concatenate: '<S27>/Matrix Concatenation3'
     */
    rtb_heading = 0.0;
    rtb_kaxis_b = 0.0;
    rtb_rintegrate_tmp = 0.0;
    for (i = 0; i < 3; i++) {
      EastDot_tmp = tmp_0[i];
      rtb_heading += rtb_MatrixConcatenation3[3 * i] * EastDot_tmp;
      rtb_kaxis_b += rtb_MatrixConcatenation3[3 * i + 1] * EastDot_tmp;
      rtb_rintegrate_tmp += rtb_MatrixConcatenation3[3 * i + 2] * EastDot_tmp;
    }

    /* End of Product: '<S25>/Product' */

    /* Sum: '<S25>/Sum1' incorporates:
     *  Integrator: '<S29>/r integrate'
     *  Product: '<S10>/F//m'
     *  Product: '<S25>/QW'
     *  Product: '<S25>/RV'
     *  Sum: '<S10>/Sum1'
     *  Sum: '<S25>/Sum'
     */
    Thesis_C___B.Sum1 = ((rtb_Product1[0] + rtb_Product1_a) / rtb_bearrad +
                         rtb_heading) + (Thesis_C___X.rintegrate_CSTATE *
      rtb_Jaxis - rtb_qintegrate * rtb_iaxis);

    /* Sum: '<S25>/Sum2' incorporates:
     *  Constant: '<S10>/Thrust Y&Z'
     *  Integrator: '<S29>/p integrate'
     *  Integrator: '<S29>/r integrate'
     *  Product: '<S10>/F//m'
     *  Product: '<S25>/PW'
     *  Product: '<S25>/RU'
     *  Sum: '<S10>/Sum1'
     *  Sum: '<S25>/Sum'
     */
    Thesis_C___B.Sum2 = ((rtb_Product1[1] + Thesis_C___P.ThrustYZ_Value) /
                         rtb_bearrad + rtb_kaxis_b) +
      (Thesis_C___X.pintegrate_CSTATE * rtb_iaxis -
       Thesis_C___X.rintegrate_CSTATE * rtb_kaxis);

    /* Sum: '<S25>/Sum3' incorporates:
     *  Constant: '<S10>/Thrust Y&Z'
     *  Integrator: '<S29>/p integrate'
     *  Product: '<S10>/F//m'
     *  Product: '<S25>/PV'
     *  Product: '<S25>/QU'
     *  Sum: '<S10>/Sum1'
     *  Sum: '<S25>/Sum'
     */
    Thesis_C___B.Sum3 = ((rtb_Product1[2] + Thesis_C___P.ThrustYZ_Value) /
                         rtb_bearrad + rtb_rintegrate_tmp) + (rtb_qintegrate *
      rtb_kaxis - Thesis_C___X.pintegrate_CSTATE * rtb_Jaxis);

    /* Fcn: '<S28>/Yaw rate' incorporates:
     *  Fcn: '<S28>/roll rate'
     */
    rtb_kaxis = rtb_qintegrate * rtb_switch2;

    /* Fcn: '<S28>/Yaw rate' incorporates:
     *  Integrator: '<S29>/r integrate'
     */
    Thesis_C___B.Yawrate = (Thesis_C___X.rintegrate_CSTATE * rtb_bank +
      rtb_kaxis) / rtb_Jaxis_j;

    /* Fcn: '<S28>/pitch rate' incorporates:
     *  Integrator: '<S29>/r integrate'
     */
    Thesis_C___B.pitchrate = rtb_qintegrate * rtb_bank -
      Thesis_C___X.rintegrate_CSTATE * rtb_switch2;

    /* Fcn: '<S28>/roll rate' incorporates:
     *  Integrator: '<S29>/p integrate'
     *  Integrator: '<S29>/r integrate'
     */
    Thesis_C___B.rollrate = (Thesis_C___X.rintegrate_CSTATE * rtb_bank +
      rtb_kaxis) * std::tan(rtb_pitch) + Thesis_C___X.pintegrate_CSTATE;
    if (tmp) {
      /* Fcn: '<S33>/c1' incorporates:
       *  Constant: '<S11>/jx'
       *  Constant: '<S11>/jxz'
       *  Constant: '<S11>/jy'
       *  Constant: '<S11>/jz'
       */
      Thesis_C___B.c1 = ((Thesis_C___P.jy - Thesis_C___P.jz) * Thesis_C___P.jz -
                         rt_powd_snf(Thesis_C___P.jxz, 2.0)) / (Thesis_C___P.jx *
        Thesis_C___P.jz - rt_powd_snf(Thesis_C___P.jxz, 2.0));

      /* Fcn: '<S33>/c2' incorporates:
       *  Constant: '<S11>/jx'
       *  Constant: '<S11>/jxz'
       *  Constant: '<S11>/jy'
       *  Constant: '<S11>/jz'
       */
      Thesis_C___B.c2 = ((Thesis_C___P.jx - Thesis_C___P.jy) + Thesis_C___P.jz) *
        Thesis_C___P.jxz / (Thesis_C___P.jx * Thesis_C___P.jz - rt_powd_snf
                            (Thesis_C___P.jxz, 2.0));

      /* Fcn: '<S33>/c3' incorporates:
       *  Constant: '<S11>/jx'
       *  Constant: '<S11>/jxz'
       *  Constant: '<S11>/jz'
       */
      Thesis_C___B.c3 = Thesis_C___P.jz / (Thesis_C___P.jx * Thesis_C___P.jz -
        rt_powd_snf(Thesis_C___P.jxz, 2.0));

      /* Fcn: '<S33>/c4' incorporates:
       *  Constant: '<S11>/jx'
       *  Constant: '<S11>/jxz'
       *  Constant: '<S11>/jz'
       */
      Thesis_C___B.c4 = Thesis_C___P.jxz / (Thesis_C___P.jx * Thesis_C___P.jz -
        rt_powd_snf(Thesis_C___P.jxz, 2.0));

      /* Fcn: '<S33>/c5' incorporates:
       *  Constant: '<S11>/jx'
       *  Constant: '<S11>/jy'
       *  Constant: '<S11>/jz'
       */
      Thesis_C___B.c5 = (Thesis_C___P.jz - Thesis_C___P.jx) / Thesis_C___P.jy;

      /* Fcn: '<S33>/c6' incorporates:
       *  Constant: '<S11>/jxz'
       *  Constant: '<S11>/jy'
       */
      Thesis_C___B.c6 = Thesis_C___P.jxz / Thesis_C___P.jy;

      /* Fcn: '<S33>/c7' incorporates:
       *  Constant: '<S11>/jy'
       */
      Thesis_C___B.c7 = 1.0 / Thesis_C___P.jy;

      /* Fcn: '<S33>/c8' incorporates:
       *  Constant: '<S11>/jx'
       *  Constant: '<S11>/jxz'
       *  Constant: '<S11>/jy'
       *  Constant: '<S11>/jz'
       */
      Thesis_C___B.c8 = ((Thesis_C___P.jx - Thesis_C___P.jy) * Thesis_C___P.jx +
                         rt_powd_snf(Thesis_C___P.jxz, 2.0)) / (Thesis_C___P.jx *
        Thesis_C___P.jz - rt_powd_snf(Thesis_C___P.jxz, 2.0));

      /* Fcn: '<S33>/c9' incorporates:
       *  Constant: '<S11>/jx'
       *  Constant: '<S11>/jxz'
       *  Constant: '<S11>/jz'
       */
      Thesis_C___B.c9 = Thesis_C___P.jx / (Thesis_C___P.jx * Thesis_C___P.jz -
        rt_powd_snf(Thesis_C___P.jxz, 2.0));

      /* Sum: '<S10>/Sum5' incorporates:
       *  Constant: '<S10>/Aero Center'
       *  Constant: '<S11>/cg'
       */
      Thesis_C___B.Sum5[0] = Thesis_C___P.ac[0] - Thesis_C___P.cg[0];

      /* Sum: '<S10>/Sum2' incorporates:
       *  Constant: '<S10>/DngPOS'
       *  Constant: '<S11>/cg'
       *  Sum: '<S10>/Sum5'
       */
      Thesis_C___B.Sum2_b[0] = Thesis_C___P.eng[0] - Thesis_C___P.cg[0];

      /* Sum: '<S10>/Sum5' incorporates:
       *  Constant: '<S10>/Aero Center'
       *  Constant: '<S11>/cg'
       */
      Thesis_C___B.Sum5[1] = Thesis_C___P.ac[1] - Thesis_C___P.cg[1];

      /* Sum: '<S10>/Sum2' incorporates:
       *  Constant: '<S10>/DngPOS'
       *  Constant: '<S11>/cg'
       *  Sum: '<S10>/Sum5'
       */
      Thesis_C___B.Sum2_b[1] = Thesis_C___P.eng[1] - Thesis_C___P.cg[1];

      /* Sum: '<S10>/Sum5' incorporates:
       *  Constant: '<S10>/Aero Center'
       *  Constant: '<S11>/cg'
       */
      Thesis_C___B.Sum5[2] = Thesis_C___P.ac[2] - Thesis_C___P.cg[2];

      /* Sum: '<S10>/Sum2' incorporates:
       *  Constant: '<S10>/DngPOS'
       *  Constant: '<S11>/cg'
       *  Sum: '<S10>/Sum5'
       */
      Thesis_C___B.Sum2_b[2] = Thesis_C___P.eng[2] - Thesis_C___P.cg[2];
    }

    /* Sum: '<S10>/Sum4' incorporates:
     *  Constant: '<S34>/Check prob not zero'
     *  Fcn: '<S34>/i axis'
     *  Fcn: '<S34>/k axis'
     *  Fcn: '<S35>/i axis'
     *  Fcn: '<S35>/k axis'
     */
    rtb_switch2 = ((Thesis_C___B.Sum5[1] * rtb_Product1[2] - rtb_Product1[1] *
                    Thesis_C___B.Sum5[2]) + rtb_Roll) +
      (Thesis_C___P.Checkprobnotzero_Value * Thesis_C___B.Sum2_b[1] -
       Thesis_C___P.Checkprobnotzero_Value * Thesis_C___B.Sum2_b[2]);
    rtb_bank = ((Thesis_C___B.Sum5[0] * rtb_Product1[1] - rtb_Product1[0] *
                 Thesis_C___B.Sum5[1]) + rtb_Sum_b) +
      (Thesis_C___P.Checkprobnotzero_Value * Thesis_C___B.Sum2_b[0] -
       rtb_Product1_a * Thesis_C___B.Sum2_b[1]);

    /* Fcn: '<S29>/pdot' incorporates:
     *  Integrator: '<S29>/p integrate'
     *  Integrator: '<S29>/r integrate'
     */
    Thesis_C___B.pdot = ((Thesis_C___B.c1 * Thesis_C___X.rintegrate_CSTATE +
                          Thesis_C___B.c2 * Thesis_C___X.pintegrate_CSTATE) *
                         rtb_qintegrate + Thesis_C___B.c3 * rtb_switch2) +
      Thesis_C___B.c4 * rtb_bank;

    /* Fcn: '<S29>/qdot' incorporates:
     *  Constant: '<S34>/Check prob not zero'
     *  Fcn: '<S34>/J axis'
     *  Fcn: '<S35>/J axis'
     *  Integrator: '<S29>/p integrate'
     *  Integrator: '<S29>/r integrate'
     *  Sum: '<S10>/Sum4'
     */
    Thesis_C___B.qdot = (((rtb_Product1[0] * Thesis_C___B.Sum5[2] -
      Thesis_C___B.Sum5[0] * rtb_Product1[2]) + rtb_cla) + (rtb_Product1_a *
      Thesis_C___B.Sum2_b[2] - Thesis_C___P.Checkprobnotzero_Value *
      Thesis_C___B.Sum2_b[0])) * Thesis_C___B.c7 + (Thesis_C___B.c5 *
      Thesis_C___X.pintegrate_CSTATE * Thesis_C___X.rintegrate_CSTATE -
      (rt_powd_snf(Thesis_C___X.pintegrate_CSTATE, 2.0) - rt_powd_snf
       (Thesis_C___X.rintegrate_CSTATE, 2.0)) * Thesis_C___B.c6);

    /* Fcn: '<S29>/rdot' incorporates:
     *  Integrator: '<S29>/p integrate'
     *  Integrator: '<S29>/r integrate'
     */
    Thesis_C___B.rdot = ((Thesis_C___B.c8 * Thesis_C___X.pintegrate_CSTATE -
                          Thesis_C___B.c2 * Thesis_C___X.rintegrate_CSTATE) *
                         rtb_qintegrate + Thesis_C___B.c4 * rtb_switch2) +
      Thesis_C___B.c9 * rtb_bank;

    /* Sum: '<S199>/Del_Y' */
    rtb_Del_Y = Thesis_C___B.activewaypoint[1] - rtb_Del_Y;

    /* Sum: '<S199>/Del_x' */
    rtb_Del_x = Thesis_C___B.activewaypoint[0] - rtb_Del_x;

    /* RelationalOperator: '<S4>/Less Than' incorporates:
     *  Constant: '<S4>/Min Range'
     *  Math: '<S199>/Math Function'
     *  Math: '<S199>/Math Function1'
     *  Sqrt: '<S199>/Square Root'
     *  Sum: '<S199>/Sum1'
     */
    Thesis_C___B.increment = (std::sqrt(rtb_Del_x * rtb_Del_x + rtb_Del_Y *
      rtb_Del_Y) < Thesis_C___P.MinRange_Value);
    if (tmp) {
      /* S-Function (sdspcount2): '<S4>/Counter' */
      if (MWDSP_EPH_R_B(Thesis_C___B.increment,
                        &Thesis_C___DW.Counter_ClkEphState) != 0U) {
        if (Thesis_C___DW.Counter_Count < 255) {
          Thesis_C___DW.Counter_Count = static_cast<uint8_T>
            (Thesis_C___DW.Counter_Count + 1);
        } else {
          Thesis_C___DW.Counter_Count = 0U;
        }
      }

      /* S-Function (sdspcount2): '<S4>/Counter' */
      rtb_counter = Thesis_C___DW.Counter_Count;

      /* Stop: '<S4>/Stop Simulation' incorporates:
       *  S-Function (sdspcount2): '<S4>/Counter'
       */
      if (Thesis_C___DW.Counter_Count == Thesis_C___P.Counter_HitValue) {
        rtmSetStopRequested((&Thesis_C___M), 1);
      }

      /* End of Stop: '<S4>/Stop Simulation' */

      /* Gain: '<S242>/Integral Gain' */
      Thesis_C___B.IntegralGain_m = Thesis_C___P.PIDController_I_n * 0.0;
    }

    /* Gain: '<S294>/Integral Gain' */
    Thesis_C___B.IntegralGain = Thesis_C___P.PIDController1_I * rtb_rintegrate;
  }

  if (rtmIsMajorTimeStep((&Thesis_C___M))) {
    real_T (*lastU)[2];

    /* Update for Derivative: '<S9>/Derivative' */
    if (Thesis_C___DW.TimeStampA == (rtInf)) {
      Thesis_C___DW.TimeStampA = (&Thesis_C___M)->Timing.t[0];
      lastU = &Thesis_C___DW.LastUAtTimeA;
    } else if (Thesis_C___DW.TimeStampB == (rtInf)) {
      Thesis_C___DW.TimeStampB = (&Thesis_C___M)->Timing.t[0];
      lastU = &Thesis_C___DW.LastUAtTimeB;
    } else if (Thesis_C___DW.TimeStampA < Thesis_C___DW.TimeStampB) {
      Thesis_C___DW.TimeStampA = (&Thesis_C___M)->Timing.t[0];
      lastU = &Thesis_C___DW.LastUAtTimeA;
    } else {
      Thesis_C___DW.TimeStampB = (&Thesis_C___M)->Timing.t[0];
      lastU = &Thesis_C___DW.LastUAtTimeB;
    }

    (*lastU)[0] = Thesis_C___B.GetAoA;
    (*lastU)[1] = Thesis_C___B.GetBeta;

    /* End of Update for Derivative: '<S9>/Derivative' */
    if (rtmIsMajorTimeStep((&Thesis_C___M))) {
      /* Update for Memory: '<S4>/Memory' */
      Thesis_C___DW.Memory_PreviousInput = rtb_counter;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&Thesis_C___M))) {
    rt_ertODEUpdateContinuousStates(&(&Thesis_C___M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&Thesis_C___M)->Timing.clockTick0)) {
      ++(&Thesis_C___M)->Timing.clockTickH0;
    }

    (&Thesis_C___M)->Timing.t[0] = rtsiGetSolverStopTime(&(&Thesis_C___M)
      ->solverInfo);

    {
      /* Update absolute timer for sample time: [0.01s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.01, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&Thesis_C___M)->Timing.clockTick1++;
      if (!(&Thesis_C___M)->Timing.clockTick1) {
        (&Thesis_C___M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Thesis_C__::Thesis_C___derivatives()
{
  XDot_Thesis_C___T *_rtXdot;
  _rtXdot = ((XDot_Thesis_C___T *) (&Thesis_C___M)->derivs);

  /* Derivatives for Integrator: '<S24>/North' incorporates:
   *  Integrator: '<S24>/Alt'
   *  Integrator: '<S24>/East'
   *  Integrator: '<S25>/u integrate'
   *  Integrator: '<S25>/v integrate'
   *  Integrator: '<S25>/w integrate'
   *  Integrator: '<S28>/bank'
   *  Integrator: '<S28>/heading'
   *  Integrator: '<S28>/pitch'
   *  Integrator: '<S29>/q integrate'
   */
  if (!Thesis_C___B.RelationalOperator) {
    _rtXdot->North_CSTATE = Thesis_C___B.NorthDot;
    _rtXdot->East_CSTATE = Thesis_C___B.EastDot;
    _rtXdot->Alt_CSTATE = Thesis_C___B.AlttitudeDot;
    _rtXdot->bank_CSTATE = Thesis_C___B.rollrate;
    _rtXdot->pitch_CSTATE = Thesis_C___B.pitchrate;
    _rtXdot->heading_CSTATE = Thesis_C___B.Yawrate;
    _rtXdot->uintegrate_CSTATE = Thesis_C___B.Sum1;
    _rtXdot->vintegrate_CSTATE = Thesis_C___B.Sum2;
    _rtXdot->wintegrate_CSTATE = Thesis_C___B.Sum3;
    _rtXdot->qintegrate_CSTATE = Thesis_C___B.qdot;
  } else {
    /* level reset is active */
    _rtXdot->North_CSTATE = 0.0;

    /* level reset is active */
    _rtXdot->East_CSTATE = 0.0;

    /* level reset is active */
    _rtXdot->Alt_CSTATE = 0.0;

    /* level reset is active */
    _rtXdot->bank_CSTATE = 0.0;

    /* level reset is active */
    _rtXdot->pitch_CSTATE = 0.0;

    /* level reset is active */
    _rtXdot->heading_CSTATE = 0.0;

    /* level reset is active */
    _rtXdot->uintegrate_CSTATE = 0.0;

    /* level reset is active */
    _rtXdot->vintegrate_CSTATE = 0.0;

    /* level reset is active */
    _rtXdot->wintegrate_CSTATE = 0.0;

    /* level reset is active */
    _rtXdot->qintegrate_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S24>/North' */

  /* Derivatives for If: '<S2>/If' */
  ((XDot_Thesis_C___T *) (&Thesis_C___M)->derivs)->Integrator_CSTATE_k = 0.0;
  ((XDot_Thesis_C___T *) (&Thesis_C___M)->derivs)->Integrator_CSTATE_n = 0.0;
  ((XDot_Thesis_C___T *) (&Thesis_C___M)->derivs)->Integrator_CSTATE_h = 0.0;
  switch (Thesis_C___DW.If_ActiveSubsystem) {
   case 0:
    /* Derivatives for IfAction SubSystem: '<S2>/Climb' incorporates:
     *  ActionPort: '<S36>/Action Port'
     */
    /* Derivatives for Integrator: '<S74>/Integrator' */
    _rtXdot->Integrator_CSTATE_k = Thesis_C___B.IntegralGain_mn;

    /* End of Derivatives for SubSystem: '<S2>/Climb' */
    break;

   case 1:
    /* Derivatives for IfAction SubSystem: '<S2>/Decend' incorporates:
     *  ActionPort: '<S37>/Action Port'
     */
    /* Derivatives for Integrator: '<S127>/Integrator' */
    _rtXdot->Integrator_CSTATE_n = Thesis_C___B.IntegralGain_e;

    /* End of Derivatives for SubSystem: '<S2>/Decend' */
    break;

   case 2:
    /* Derivatives for IfAction SubSystem: '<S2>/Level' incorporates:
     *  ActionPort: '<S38>/Action Port'
     */
    /* Derivatives for Integrator: '<S180>/Integrator' */
    _rtXdot->Integrator_CSTATE_h = Thesis_C___B.IntegralGain_l;

    /* End of Derivatives for SubSystem: '<S2>/Level' */
    break;
  }

  /* End of Derivatives for If: '<S2>/If' */

  /* Derivatives for Integrator: '<S29>/p integrate' incorporates:
   *  Integrator: '<S29>/r integrate'
   */
  if (!Thesis_C___B.RelationalOperator) {
    _rtXdot->pintegrate_CSTATE = Thesis_C___B.pdot;
    _rtXdot->rintegrate_CSTATE = Thesis_C___B.rdot;
  } else {
    /* level reset is active */
    _rtXdot->pintegrate_CSTATE = 0.0;

    /* level reset is active */
    _rtXdot->rintegrate_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S29>/p integrate' */

  /* Derivatives for Integrator: '<S297>/Integrator' */
  _rtXdot->Integrator_CSTATE = Thesis_C___B.IntegralGain;

  /* Derivatives for Integrator: '<S245>/Integrator' */
  _rtXdot->Integrator_CSTATE_a = Thesis_C___B.IntegralGain_m;
}

/* Model initialize function */
void Thesis_C__::initialize()
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&Thesis_C___M)->solverInfo, &(&Thesis_C___M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&Thesis_C___M)->solverInfo, &rtmGetTPtr((&Thesis_C___M)));
    rtsiSetStepSizePtr(&(&Thesis_C___M)->solverInfo, &(&Thesis_C___M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&Thesis_C___M)->solverInfo, &(&Thesis_C___M)->derivs);
    rtsiSetContStatesPtr(&(&Thesis_C___M)->solverInfo, (real_T **)
                         &(&Thesis_C___M)->contStates);
    rtsiSetNumContStatesPtr(&(&Thesis_C___M)->solverInfo, &(&Thesis_C___M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&Thesis_C___M)->solverInfo,
      &(&Thesis_C___M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&Thesis_C___M)->solverInfo,
      &(&Thesis_C___M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&Thesis_C___M)->solverInfo,
      &(&Thesis_C___M)->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&(&Thesis_C___M)->solverInfo, (boolean_T**)
      &(&Thesis_C___M)->contStateDisabled);
    rtsiSetErrorStatusPtr(&(&Thesis_C___M)->solverInfo, (&rtmGetErrorStatus
      ((&Thesis_C___M))));
    rtsiSetRTModelPtr(&(&Thesis_C___M)->solverInfo, (&Thesis_C___M));
  }

  rtsiSetSimTimeStep(&(&Thesis_C___M)->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&(&Thesis_C___M)->solverInfo, false);
  rtsiSetIsContModeFrozen(&(&Thesis_C___M)->solverInfo, false);
  (&Thesis_C___M)->intgData.y = (&Thesis_C___M)->odeY;
  (&Thesis_C___M)->intgData.f[0] = (&Thesis_C___M)->odeF[0];
  (&Thesis_C___M)->intgData.f[1] = (&Thesis_C___M)->odeF[1];
  (&Thesis_C___M)->intgData.f[2] = (&Thesis_C___M)->odeF[2];
  (&Thesis_C___M)->intgData.f[3] = (&Thesis_C___M)->odeF[3];
  (&Thesis_C___M)->contStates = ((X_Thesis_C___T *) &Thesis_C___X);
  (&Thesis_C___M)->contStateDisabled = ((XDis_Thesis_C___T *) &Thesis_C___XDis);
  (&Thesis_C___M)->Timing.tStart = (0.0);
  rtsiSetSolverData(&(&Thesis_C___M)->solverInfo, static_cast<void *>
                    (&(&Thesis_C___M)->intgData));
  rtsiSetSolverName(&(&Thesis_C___M)->solverInfo,"ode4");
  rtmSetTPtr((&Thesis_C___M), &(&Thesis_C___M)->Timing.tArray[0]);
  (&Thesis_C___M)->Timing.stepSize0 = 0.01;

  /* Start for If: '<S2>/If' */
  (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_k), 1,
                     1*sizeof(boolean_T));
  (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_n), 1,
                     1*sizeof(boolean_T));
  (void) std::memset(&(Thesis_C___XDis.Integrator_CSTATE_h), 1,
                     1*sizeof(boolean_T));
  Thesis_C___DW.If_ActiveSubsystem = -1;
  Thesis_C___PrevZCX.North_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Thesis_C___PrevZCX.East_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Thesis_C___PrevZCX.Alt_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Thesis_C___PrevZCX.bank_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Thesis_C___PrevZCX.pitch_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Thesis_C___PrevZCX.heading_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Thesis_C___PrevZCX.uintegrate_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Thesis_C___PrevZCX.vintegrate_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Thesis_C___PrevZCX.wintegrate_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Thesis_C___PrevZCX.qintegrate_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Thesis_C___PrevZCX.pintegrate_Reset_ZCE = UNINITIALIZED_ZCSIG;
  Thesis_C___PrevZCX.rintegrate_Reset_ZCE = UNINITIALIZED_ZCSIG;

  /* InitializeConditions for Integrator: '<S24>/North' */
  Thesis_C___X.North_CSTATE = Thesis_C___P.North_IC;

  /* InitializeConditions for Integrator: '<S24>/East' */
  Thesis_C___X.East_CSTATE = Thesis_C___P.East_IC;

  /* InitializeConditions for Integrator: '<S24>/Alt' */
  Thesis_C___X.Alt_CSTATE = Thesis_C___P.Alt_IC;

  /* InitializeConditions for Integrator: '<S28>/bank' */
  Thesis_C___X.bank_CSTATE = Thesis_C___P.initbank;

  /* InitializeConditions for Integrator: '<S28>/pitch' */
  Thesis_C___X.pitch_CSTATE = Thesis_C___P.pitch_IC;

  /* InitializeConditions for Integrator: '<S28>/heading' */
  Thesis_C___X.heading_CSTATE = Thesis_C___P.inithead;

  /* InitializeConditions for Integrator: '<S25>/u integrate' */
  Thesis_C___X.uintegrate_CSTATE = Thesis_C___P.uintegrate_IC;

  /* InitializeConditions for Integrator: '<S25>/v integrate' */
  Thesis_C___X.vintegrate_CSTATE = Thesis_C___P.initv;

  /* InitializeConditions for Integrator: '<S25>/w integrate' */
  Thesis_C___X.wintegrate_CSTATE = Thesis_C___P.initw;

  /* InitializeConditions for Derivative: '<S9>/Derivative' */
  Thesis_C___DW.TimeStampA = (rtInf);
  Thesis_C___DW.TimeStampB = (rtInf);

  /* InitializeConditions for Integrator: '<S29>/q integrate' */
  Thesis_C___X.qintegrate_CSTATE = Thesis_C___P.initq;

  /* InitializeConditions for Memory: '<S4>/Memory' */
  Thesis_C___DW.Memory_PreviousInput = Thesis_C___P.Memory_InitialCondition;

  /* InitializeConditions for Integrator: '<S29>/p integrate' */
  Thesis_C___X.pintegrate_CSTATE = Thesis_C___P.initp;

  /* InitializeConditions for Integrator: '<S29>/r integrate' */
  Thesis_C___X.rintegrate_CSTATE = Thesis_C___P.initr;

  /* InitializeConditions for Integrator: '<S297>/Integrator' */
  Thesis_C___X.Integrator_CSTATE = Thesis_C___P.PIDController1_InitialCondition;

  /* InitializeConditions for S-Function (sdspcount2): '<S4>/Counter' */
  Thesis_C___DW.Counter_ClkEphState = 5U;
  Thesis_C___DW.Counter_Count = Thesis_C___P.Counter_InitialCount;

  /* InitializeConditions for Integrator: '<S245>/Integrator' */
  Thesis_C___X.Integrator_CSTATE_a =
    Thesis_C___P.PIDController_InitialConditi_kv;

  /* SystemInitialize for IfAction SubSystem: '<S2>/Climb' */
  /* InitializeConditions for Integrator: '<S74>/Integrator' */
  Thesis_C___X.Integrator_CSTATE_k =
    Thesis_C___P.PIDController_InitialConditionF;

  /* End of SystemInitialize for SubSystem: '<S2>/Climb' */

  /* SystemInitialize for IfAction SubSystem: '<S2>/Decend' */
  /* InitializeConditions for Integrator: '<S127>/Integrator' */
  Thesis_C___X.Integrator_CSTATE_n =
    Thesis_C___P.PIDController_InitialConditio_e;

  /* End of SystemInitialize for SubSystem: '<S2>/Decend' */

  /* SystemInitialize for IfAction SubSystem: '<S2>/Level' */
  /* InitializeConditions for Integrator: '<S180>/Integrator' */
  Thesis_C___X.Integrator_CSTATE_h =
    Thesis_C___P.PIDController_InitialConditio_k;

  /* End of SystemInitialize for SubSystem: '<S2>/Level' */
}

/* Model terminate function */
void Thesis_C__::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
Thesis_C__::Thesis_C__() :
  Thesis_C___U(),
  Thesis_C___Y(),
  Thesis_C___B(),
  Thesis_C___DW(),
  Thesis_C___X(),
  Thesis_C___XDis(),
  Thesis_C___PrevZCX(),
  Thesis_C___M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
/* Currently there is no destructor body generated.*/
Thesis_C__::~Thesis_C__() = default;

/* Real-Time Model get method */
RT_MODEL_Thesis_C___T * Thesis_C__::getRTM()
{
  return (&Thesis_C___M);
}