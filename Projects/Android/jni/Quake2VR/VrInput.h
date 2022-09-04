
#if !defined(vrinput_h)
#define vrinput_h

#include "VrCommon.h"

//New control scheme definitions to be defined L1VR_SurfaceView.c enumeration
extern enum control_scheme;

extern ovrInputStateTrackedRemote leftTrackedRemoteState_old;
extern ovrInputStateTrackedRemote leftTrackedRemoteState_new;
extern ovrTracking leftRemoteTracking_new;

extern ovrInputStateTrackedRemote rightTrackedRemoteState_old;
extern ovrInputStateTrackedRemote rightTrackedRemoteState_new;
extern ovrTracking rightRemoteTracking_new;

extern ovrDeviceID controllerIDs[2];

extern int hmdType;

extern float remote_movementSideways;
extern float remote_movementForward;
extern float remote_movementUp;
extern float positional_movementSideways;
extern float positional_movementForward;
extern float snapTurn;

void sendButtonAction(const char* action, long buttonDown);
void sendButtonActionSimple(const char* action);

void acquireTrackedRemotesData(const ovrMobile *Ovr, double displayTime);

void HandleInput_Default( ovrInputStateTrackedRemote *pDominantTrackedRemoteNew, ovrInputStateTrackedRemote *pDominantTrackedRemoteOld, ovrTracking* pDominantTracking,
                          ovrInputStateTrackedRemote *pOffTrackedRemoteNew, ovrInputStateTrackedRemote *pOffTrackedRemoteOld, ovrTracking* pOffTracking,
                          int domButton1, int domButton2, int offButton1, int offButton2 );


#endif //vrinput_h