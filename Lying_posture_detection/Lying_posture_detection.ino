int IMU_state = 999;
float pos[5];  // array to hold the percetage of each label

#include <TensorFlowLite.h>
#include <Arduino_LSM9DS1.h>
#include "main_functions.h"
#include "tensorflow/lite/micro/all_ops_resolver.h"
#include "model.h"
#include "output_handler.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

// Globals, used for compatibility with Arduino.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;
TfLiteTensor* output = nullptr;

constexpr int kTensorArenaSize = 10*2048;
uint8_t tensor_arena[kTensorArenaSize];
}  


void setup() {
  // Initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU");
    while (1);
  }
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(posture_IMU_tflite);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // This pulls in all the operation implementations we need.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::AllOpsResolver resolver;

  // Build an interpreter to run the model with.
  static tflite::MicroInterpreter static_interpreter(
      model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  // Obtain pointers to the model's input and output tensors.
  input = interpreter->input(0);
  output = interpreter->output(0);

}

void stateIMU(){
  char x = Serial.read();
  if (x == 'a'){                  // for accelerometer
   
    IMU_state = 0;
  }
  else if (x == 'g'){             // for gyroscope
    IMU_state = 1;
  }
  else if (x == 'm'){             // for magnetometer
    IMU_state = 2;
  }
  else{
    IMU_state = 999;
  }
}

void state(float val, int position){                    // a function to print out the position and the probability percentage
  switch(position){
    case(0):
      Serial.print("Supline");
      val = val*100 ;
      Serial.print(" with a percentage of ");
      Serial.println(val);
      break;
  
    case(1):
      Serial.print("Prone");
      val = val*100;
      Serial.print(" with a percentage of ");
      Serial.println(val);
      break;
  
    case(2):
      Serial.print("Side");
      val = val*100;
      Serial.print(" with a percentage of ");
      Serial.println(val);
      break;
  
      case(3):
      Serial.print("Sitting");
      val = val*100;
      Serial.print(" with a percentage of ");
      Serial.println(val);
      break;
  
      case(4):
      Serial.print("Unknown");
      val = val*100;
      Serial.print(" with a percentage of ");
      Serial.println(val);
      break;
  }
}

void loop() {
  float x, y, z;
  switch(IMU_state){
    case (0):
      if (IMU.accelerationAvailable()){
        IMU.readAcceleration(x, y, z);
        input->data.f[0] = x;
        input->data.f[1] = y;
        input->data.f[2] = z;


        static tflite::MicroErrorReporter micro_error_reporter;
        error_reporter = &micro_error_reporter;
        model = tflite::GetModel(posture_IMU_tflite);
        // Run inference, and report any error
        TfLiteStatus invoke_status = interpreter->Invoke();
        if (invoke_status != kTfLiteOk) {
        TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x: %f\n",
                         static_cast<double>(x));
        return;
        }

        float max_value =0;
        int max_index = 0;
        for(int i=0;i<5;i++){                         //input all the label probability in an array
          pos[i]=output->data.f[i];
          if(pos[i]>max_value){
            max_value = pos[i];
            max_index = i;
          }
        }
        state(max_value,max_index);
        }
        break;
      case (1):
      if (IMU.gyroscopeAvailable()){
        IMU.readGyroscope(x, y, z);
        input->data.f[0] = x;
        input->data.f[1] = y;
        input->data.f[2] = z;

        static tflite::MicroErrorReporter micro_error_reporter;
        error_reporter = &micro_error_reporter;
        model = tflite::GetModel(posture_IMU_tflite);
        // Run inference, and report any error
        TfLiteStatus invoke_status = interpreter->Invoke();
        if (invoke_status != kTfLiteOk) {
        TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x: %f\n",
                         static_cast<double>(x));
        return;
        }
        float max_value =0;
        int max_index = 0;
        for(int i=0;i<5;i++){
          pos[i]=output->data.f[i];
          if(pos[i]>max_value){
            max_value = pos[i];
            max_index = i;
          }

        }
        state(max_value,max_index);   
      }
        break;
      case (2):
      if (IMU.magneticFieldAvailable()){
        IMU.readMagneticField(x, y, z);
        input->data.f[0] = x;
        input->data.f[1] = y;
        input->data.f[2] = z;
        
        static tflite::MicroErrorReporter micro_error_reporter;
        error_reporter = &micro_error_reporter;
        model = tflite::GetModel(posture_IMU_tflite);
        // Run inference, and report any error
        TfLiteStatus invoke_status = interpreter->Invoke();
        if (invoke_status != kTfLiteOk) {
        TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed on x: %f\n",
                         static_cast<double>(x));
        return;
        }
        float max_value =0;
        int max_index = 0;
        for(int i=0;i<5;i++){
          pos[i]=output->data.f[i];
          if(pos[i]>max_value){
            max_value = pos[i];
            max_index = i;
          }
        }
        state(max_value,max_index);
      }
        break;  
      }


  stateIMU();
  delay(1000);

}
