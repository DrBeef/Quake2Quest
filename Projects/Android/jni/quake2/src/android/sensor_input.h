#include <string.h>
#include <jni.h>
#include <android/sensor.h>
#include <android/looper.h>
#include <android/log.h>
#include <time.h>
#define LOOPER_ID 1
#define SAMP_PER_SEC 100

ASensorEventQueue* sensorEventQueue;

int accCounter = 0;
int64_t lastAccTime = 0;

int gyroCounter = 0;
int64_t lastGyroTime = 0;

int magCounter = 0;
int64_t lastMagTime = 0;

float sensor_float_array[64]; // if you don't know how many there are, use the heap

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "native-activity", __VA_ARGS__))



/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/HelloJni/HelloJni.java
 */

static int get_sensor_events(int fd, int events, void* data);

struct tm* start;
struct tm* finish;

 int events, ident;
 ASensorManager* sensorManager;
 const ASensor* accSensor;
 const ASensor* gyroSensor;
 const ASensor* magSensor;
 void* sensor_data;
 ALooper* looper;


void
init_sensor() {

     LOGI("sensorValue() - ALooper_forThread()");

     looper = ALooper_forThread();
     sensor_data= malloc(1000);
    if(looper == NULL)
    {
        looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    }

    sensorManager = ASensorManager_getInstance();

    accSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
    gyroSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_GYROSCOPE);
    magSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_MAGNETIC_FIELD);



    sensorEventQueue = ASensorManager_createEventQueue(sensorManager, looper, 3, get_sensor_events, sensor_data);

    ASensorEventQueue_enableSensor(sensorEventQueue, accSensor);
    ASensorEventQueue_enableSensor(sensorEventQueue, gyroSensor);
    ASensorEventQueue_enableSensor(sensorEventQueue, magSensor);

    //Sampling rate: 100Hz
    int a = ASensor_getMinDelay(accSensor);
    int b = ASensor_getMinDelay(gyroSensor);
    int c = ASensor_getMinDelay(magSensor);
    LOGI("min-delay: %d, %d, %d",a,b,c);
    ASensorEventQueue_setEventRate(sensorEventQueue, accSensor, 100000);
    ASensorEventQueue_setEventRate(sensorEventQueue, gyroSensor, 100000);
    ASensorEventQueue_setEventRate(sensorEventQueue, magSensor, 100000);

    LOGI("sensorValue() - START");
}



static int get_sensor_events(int fd, int events, void* data) {
	ASensorEvent sensor_input_event;
//ASensorEvent event;
  //ASensorEventQueue* sensorEventQueue;
	 LOGI("received callback");

  while (ASensorEventQueue_getEvents(sensorEventQueue, &sensor_input_event, 1) > 0) {
      LOGI("In get_sensor_events");

	  if(sensor_input_event.type == ASENSOR_TYPE_ACCELEROMETER) {
                LOGI("accl(x,y,z,t): %f %f %f %lld", sensor_input_event.acceleration.x, sensor_input_event.acceleration.y, sensor_input_event.acceleration.z, sensor_input_event.timestamp);
                if(accCounter == 0 || accCounter == 1000)
                    {
                     LOGI("Acc-Time: %lld (%f)", sensor_input_event.timestamp,((double)(sensor_input_event.timestamp-lastAccTime))/1000000000.0);
                     lastAccTime = sensor_input_event.timestamp;
                     accCounter = 0;
                    }

                accCounter++;
        }
        else if(sensor_input_event.type == ASENSOR_TYPE_GYROSCOPE) {
                //LOGI("accl(x,y,z,t): %f %f %f %lld", event.acceleration.x, event.acceleration.y, event.acceleration.z, event.timestamp);
                if(gyroCounter == 0 || gyroCounter == 1000)
                    {

                     LOGI("Gyro-Time: %lld (%f)", sensor_input_event.timestamp,((double)(sensor_input_event.timestamp-lastGyroTime))/1000000000.0);
                     lastGyroTime = sensor_input_event.timestamp;
                     gyroCounter = 0;
                    }

                gyroCounter++;
        }
        else if(sensor_input_event.type == ASENSOR_TYPE_MAGNETIC_FIELD) {
                //LOGI("accl(x,y,z,t): %f %f %f %lld", event.acceleration.x, event.acceleration.y, event.acceleration.z, event.timestamp);
                if(magCounter == 0 || magCounter == 1000)
                    {
                     LOGI("Mag-Time: %lld (%f)", sensor_input_event.timestamp,((double)(sensor_input_event.timestamp-lastMagTime))/1000000000.0);
                     lastMagTime = sensor_input_event.timestamp;
                     magCounter = 0;
                    }

                magCounter++;
        }

  }
  //should return 1 to continue receiving callbacks, or 0 to unregister
  return 1;
}



float sensor_input_getyaw(){
return sensor_float_array[0];
}

float sensor_input_getpitch(){
return sensor_float_array[2];
}
float sensor_input_getroll(){
return sensor_float_array[1];
}
