#include "MPU.h"

float yaw = 0;

void initialise(){
    i2c_master_init();  //Initialise the I2C interface
    start_mpu();        //Intialise the MPU 
    // mag_calibration();	//Calibrate magnetometer
}

void mpu_task(void *arg){
    while(1){
      get_yaw(&yaw);
      printf("YAW = %f\n", yaw);
    }
}

void app_main(){
	initialise();
	xTaskCreate(mpu_task,"mpu_task", 4096, NULL, 22, NULL);
}
