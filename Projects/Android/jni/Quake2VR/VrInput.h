
#if !defined(vrinput_h)
#define vrinput_h

#include "VrCommon.h"

//New control scheme definitions to be defined L1VR_SurfaceView.c enumeration
enum control_scheme;

ovrInputStateTrackedRemote leftTrackedRemoteState_old;
ovrInputStateTrackedRemote leftTrackedRemoteState_new;
ovrTracking leftRemoteTracking_new;

ovrInputStateTrackedRemote rightTrackedRemoteState_old;
ovrInputStateTrackedRemote rightTrackedRemoteState_new;
ovrTracking rightRemoteTracking_new;

float remote_movementSideways;
float remote_movementForward;
float remote_movementUp;
float positional_movementSideways;
float positional_movementForward;
float snapTurn;

void sendButtonAction(const char* action, long buttonDown);
void sendButtonActionSimple(const char* action);

void acquireTrackedRemotesData(const ovrMobile *Ovr, double displayTime);

void HandleInput_Right( ovrMobile * Ovr, double displayTime );
void HandleInput_Left( ovrMobile * Ovr, double displayTime );


#endif //vrinput_h