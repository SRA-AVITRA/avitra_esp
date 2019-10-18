#include "MPU.h"

float mag_angle = 0;

void mpu_task(void *arg){
    //Create buffers to store raw readings
    uint8_t mag_rd[BUFF_SIZE];
    int16_t mag_raw_value[BUFF_SIZE/2];

    i2c_master_init();  //Initialise the I2C interface
    start_mpu();        //Intialise the MPU 
    
    while(1){
      getmag(mag_rd, mag_raw_value, &mag_angle);
      printf("YAW = %f\n", mag_angle);
      vTaskDelay(1 / portTICK_RATE_MS);
    }
}

void app_main(){
  xTaskCreate(mpu_task,"mpu_task",4096,NULL,1,NULL);
}
