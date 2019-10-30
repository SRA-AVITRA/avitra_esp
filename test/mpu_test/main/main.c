#include "MPU.h"

float roll = 0, pitch = 0, yaw = 0;

void initialise(){
    i2c_master_init();  //Initialise the I2C interface
    start_mpu();        //Intialise the MPU 
    // mpu_calibration();	//Calibrate magnetometer
}

void mpu_task(void *arg){
  while(1){
    get_rpy(&roll, &pitch, &yaw);
    // printf("Roll : %f\t Pitch : %f\t Yaw : %f\n", roll, pitch, yaw);  
  }
}

void app_main(){
	initialise();
	xTaskCreate(mpu_task,"mpu_task", 4096, NULL, 22, NULL);
}
