#include "BNO.h"

float yaw = 0;

void initialise(){
    i2c_master_init();  //Initialise the I2C interface
    // start_bno();        //Intialise the MPU 
    // mag_calibration();	//Calibrate magnetometer

    int ret=write_byte(I2C_MASTER_NUM,0x28,0x3D,0x00);
    vTaskDelay(30/portTICK_RATE_MS);
    ret=write_byte(I2C_MASTER_NUM,0x28,0x3F,0x20);
    vTaskDelay(30/portTICK_RATE_MS);
    ret=write_byte(I2C_MASTER_NUM,0x28,0x3E,0x00);
    vTaskDelay(10/portTICK_RATE_MS);
    ret=write_byte(I2C_MASTER_NUM,0x28,0x07,0x00);
    vTaskDelay(10/portTICK_RATE_MS);
    ret=write_byte(I2C_MASTER_NUM,0x28,0x3F,0x00);
    vTaskDelay(10/portTICK_RATE_MS);
    ret=ESP_FAIL;
    while(ret != ESP_OK){
      ret=write_byte(I2C_MASTER_NUM,0x28,0x3D,0x0A);
    }
    
  }

void mpu_task(void *arg){
  float x,y,z;
  
    while(1){
      uint8_t a,b;
      int ret=write_byte(I2C_MASTER_NUM,0x28,0x3D,0x0A);
      vTaskDelay(30/portTICK_RATE_MS);
      // ret=read_byte(I2C_MASTER_NUM,0x28,0x3D,&b,1);
      // ret=read_byte(I2C_MASTER_NUM,0x28,0x08,&a,1);
      // printf("%d\t%d\n",b,a );
      get_euler(&x,&y,&z);
      printf("x:%f\ty:%f\tz:%f\n", x,y,z);
    }
}

void app_main(){
	initialise();
	// xTaskCreate(mpu_task,"mpu_task", 4096, NULL, 22, NULL);
  uint8_t a,b;
  float x,y,z;
  while(1){
      int ret=read_byte(I2C_MASTER_NUM,0x28,0x3D,&b,1);
      // vTaskDelay(50/portTICK_RATE_MS);
      ret=read_byte(I2C_MASTER_NUM,0x28,0x1B,&a,1);
      vTaskDelay(50/portTICK_RATE_MS);
      printf("%d\t%d\t%f\n",b,a,(a*256+b)/16.0);
      vTaskDelay(50/portTICK_RATE_MS);
      // get_euler(&x,&y,&z);
      // printf("x:%f\ty:%f\tz:%f\n", x,y,z);
    }
}
