/* rtw_solver.h - Fixed Macro Definitions */
#ifndef RTW_SOLVER_H
#define RTW_SOLVER_H

#include "tmwtypes.h"

typedef enum {
    MAJOR_TIME_STEP = 0,
    MINOR_TIME_STEP = 1
} SimTimeStep;

/* Solver Information Structure */
typedef struct _RTWSolverInfo {
    void *pModelData;
    time_T **tPtr;
    time_T *stepSizePtr;
    real_T **dXPtr;
    real_T **contStatesPtr;
    int_T *numContStatesPtr;
    int_T *numPeriodicContStatesPtr;
    int_T **periodicContStateIndicesPtr;
    real_T **periodicContStateRangesPtr;
    boolean_T **contStateDisabledPtr;
    const char_T **errorStatusPtr;
    void *rtModelPtr;
    SimTimeStep *simTimeStepPtr;
    void *solverData;
    const char_T *solverName;
    time_T solverStopTime;
    boolean_T isMinorTimeStepWithModeChange;
    boolean_T isContModeFrozen;
    
    /* REMOVED: real_T *dX; (This was the cause of the bug) */
} RTWSolverInfo;

/* Macros for accessing Solver Info */
#define rtsiSetTPtr(S, p) ((S)->tPtr = (p))
#define rtsiGetT(S) (*((S)->tPtr)[0])
#define rtsiSetT(S, v) (*((S)->tPtr)[0] = (v))

#define rtsiSetStepSizePtr(S, p) ((S)->stepSizePtr = (p))
#define rtsiGetStepSize(S) (*((S)->stepSizePtr))

#define rtsiSetdXPtr(S, p) ((S)->dXPtr = (p))

/* FIX: Dereference dXPtr to update the model's actual pointer */
#define rtsiSetdX(S, v) (*((S)->dXPtr) = (v)) 
#define rtsiGetdX(S) (*((S)->dXPtr))

#define rtsiSetContStatesPtr(S, p) ((S)->contStatesPtr = (p))
#define rtsiGetContStates(S) (*((S)->contStatesPtr))

#define rtsiSetNumContStatesPtr(S, p) ((S)->numContStatesPtr = (p))
#define rtsiSetNumPeriodicContStatesPtr(S, p) ((S)->numPeriodicContStatesPtr = (p))
#define rtsiSetPeriodicContStateIndicesPtr(S, p) ((S)->periodicContStateIndicesPtr = (p))
#define rtsiSetPeriodicContStateRangesPtr(S, p) ((S)->periodicContStateRangesPtr = (p))
#define rtsiSetContStateDisabledPtr(S, p) ((S)->contStateDisabledPtr = (p))
#define rtsiSetErrorStatusPtr(S, p) ((S)->errorStatusPtr = (p))
#define rtsiSetRTModelPtr(S, p) ((S)->rtModelPtr = (p))

#define rtsiSetSimTimeStepPtr(S, p) ((S)->simTimeStepPtr = (p))
#define rtsiSetSimTimeStep(S, v) (*((S)->simTimeStepPtr) = (v))
#define rtsiGetSimTimeStep(S) (*((S)->simTimeStepPtr))
#define rtsiIsModeUpdateTimeStep(S) (*((S)->simTimeStepPtr) == MAJOR_TIME_STEP)

#define rtsiSetSolverData(S, p) ((S)->solverData = (p))
#define rtsiGetSolverData(S) ((S)->solverData)

#define rtsiSetSolverName(S, p) ((S)->solverName = (p))

#define rtsiSetSolverStopTime(S, v) ((S)->solverStopTime = (v))
#define rtsiGetSolverStopTime(S) ((S)->solverStopTime)

#define rtsiSetIsMinorTimeStepWithModeChange(S, v) ((S)->isMinorTimeStepWithModeChange = (v))
#define rtsiSetIsContModeFrozen(S, v) ((S)->isContModeFrozen = (v))

#define rtsiSetBlockStateForSolverChangedAtMajorStep(S, val) /* No-op */

#endif /* RTW_SOLVER_H */