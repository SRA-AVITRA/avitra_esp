#include "BNO.h"

float yaw = 0;

void initialise(){
    i2c_master_init();  //Initialise the I2C interface
    start_bno();        //Intialise the MPU 
    // mag_calibration();	//Calibrate magnetometer

        
  }

void mpu_task(void *arg){
  float x,y,z;
  
    while(1){
      uint8_t a,b;
      float x,y,z;
      int ret=read_byte(I2C_MASTER_NUM,0x28,0x3D,&b,1);
      vTaskDelay(50/portTICK_RATE_MS);
      // ret=read_byte(I2C_MASTER_NUM,0x28,0x1B,&a,1);
      // vTaskDelay(50/portTICK_RATE_MS);
      // printf("%d\t%d\t%f\n",b,a,(a*256+b)/16.0);
      get_euler(&x,&y,&z);
      vTaskDelay(50/portTICK_RATE_MS);
      printf("%d\tx:%f\ty:%f\tz:%f\n",b, x,y,z);
    }
}

void app_main(){
	initialise();
	xTaskCreate(mpu_task,"mpu_task", 4096, NULL, 22, NULL);
  // while(1){
  //     uint8_t a,b;
  //     float x,y,z;
  //     int ret=read_byte(I2C_MASTER_NUM,0x28,0x3D,&b,1);
  //     vTaskDelay(50/portTICK_RATE_MS);
  //     // ret=read_byte(I2C_MASTER_NUM,0x28,0x1B,&a,1);
  //     // vTaskDelay(50/portTICK_RATE_MS);
  //     // printf("%d\t%d\t%f\n",b,a,(a*256+b)/16.0);
  //     get_euler(&x,&y,&z);
  //     vTaskDelay(50/portTICK_RATE_MS);
  //     printf("%d\tx:%f\ty:%f\tz:%f\n",b, x,y,z);
  //   }
}
