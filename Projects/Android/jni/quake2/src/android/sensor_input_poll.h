#include <string.h>
#include <jni.h>
#include <android/sensor.h>
#include <android/looper.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <time.h>



#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "native-activity", __VA_ARGS__))

struct saved_state {
    float angle;
    int32_t x;
    int32_t y;
};

struct engine {
    struct android_app* app;
    ALooper* looper;
    ASensorManager* sensorManager;
    const ASensor* gyroscopeSensor;
    ASensorEventQueue* sensorEventQueue;
    int animating;

    struct saved_state state;
}engine;




static int get_sensor_events(int fd, int events, void* data);





void
init_sensor() {

     LOGI("sensorValue() - ALooper_forThread()");
     engine.looper = ALooper_forThread();
     // Prepare to monitor accelerometer
       engine.sensorManager = ASensorManager_getInstance();
       engine.gyroscopeSensor = ASensorManager_getDefaultSensor(engine.sensorManager,
               ASENSOR_TYPE_ACCELEROMETER);
       engine.sensorEventQueue = ASensorManager_createEventQueue(engine.sensorManager,
               engine.looper, LOOPER_ID_USER, NULL, NULL);


    LOGI("sensorValue() - START");
}



int poll_sensor_events() {
	  int ident;
	        int events;
	        struct android_poll_source* source;
            LOGI("accelerometer: x=%f y=%f z=%f");

	        // If not animating, we will block forever waiting for events.
	        // If animating, we loop until all events are read, then continue
	        // to draw the next frame of animation.
	        if (ident=ALooper_pollAll(engine.animating ? 0 : -1, NULL, &events,(void**)&source)>=0){

	            // Process this event.
	            if (source != NULL) {
	                source->process(state, source);
	            }

	            // If a sensor has data, process it now.
	            if (ident == 3) {
	                if (engine.gyroscopeSensor != NULL) {
	                    ASensorEvent event;
	                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
	                            &event, 1) > 0) {
	                        LOGI("accelerometer: x=%f y=%f z=%f",
	                                event.acceleration.x, event.acceleration.y,
	                                event.acceleration.z);
	                    }
	                }

	            }
}
}


float sensor_input_getyaw(){
//return sensor_float_array[0];
}

float sensor_input_getpitch(){
//return sensor_float_array[2];
}
float sensor_input_getroll(){
//return sensor_float_array[1];
}
