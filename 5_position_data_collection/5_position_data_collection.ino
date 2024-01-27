#include <Arduino_LSM9DS1.h>                                        // IMU Sensor Library

float accel_x, accel_y, accel_z, mag_x, mag_y, mag_z, gyro_x, gyro_y, gyro_z;             //Variables to store IMU readings
int ThetaY=0;                                                        //Variable to store theta (in degrees)
int ThetaZ=0;
#define PI 3.1415926535897932384626433832795                        //Constant PI

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Started");
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");                    //Initialize IMU Sensor
    while (1);
  }
                                
}

void loop() {
  if (IMU.accelerationAvailable() & IMU.gyroscopeAvailable() & IMU.magneticFieldAvailable()) {                                //Checking if sensor is available
    IMU.readAcceleration(accel_x, accel_y, accel_z); 
    IMU.readGyroscope(gyro_x, gyro_y, gyro_z);
    IMU.readMagneticField(mag_x, mag_y, mag_z);                                 //Reading the IMU readings in x,y,z direction
  }
  ThetaY=atan(accel_y/accel_z)*(180/PI);                                         //Calulating the theta with respect to the gravity vector
  ThetaZ=atan(accel_x/accel_z)*(180/PI);
  Serial.print(accel_x);
  Serial.print(",");
  Serial.print(accel_y);
  Serial.print(",");
  Serial.print(accel_z);
  Serial.print(",");
  Serial.print(gyro_x);
  Serial.print(",");
  Serial.print(gyro_y);
  Serial.print(",");
  Serial.print(gyro_z);
  Serial.print(",");
  Serial.print(mag_x);
  Serial.print(",");
  Serial.print(mag_y);
  Serial.print(",");
  Serial.print(mag_z);
  Serial.print(",");
  if((ThetaY<10 && ThetaY>-10) && accel_z>0){                               //Supine Condition
    Serial.println(1);

  }
  else if((ThetaY<10 && ThetaY>-10) && accel_z<0){                          
    Serial.println(2);

  }
  else if((ThetaY<=100 && ThetaY>80) || (ThetaY<-80 && ThetaY>=-100)&&(abs(accel_y)>0.85 && abs(accel_y)<1.1)){  //Side wise Condition
    Serial.println(3);
   // blink();
   // blink();
    //blink();
  }
  else if((ThetaZ>80 && ThetaZ<100)&&(accel_x>0.85&&accel_x<1.1)){
    Serial.println(4);
  }
  else
    Serial.println(5);                               //Other
    //digitalWrite(LED_BUILTIN, LOW);
    //delay(1000);
  delay(200);                                                     //Delay between each reading
}
