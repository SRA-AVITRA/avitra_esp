#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "rosserial.h"
#include "MPU.h"

float yaw = 0;

void initialize(){
    rosserial_setup();	//Initialize rosserial for esp32
    i2c_master_init();  //Initialise the I2C interface
    start_mpu();        //Intialise the MPU 
}

void push_data(){   
    while(1){
        get_yaw(&yaw);
        // printf("yaw = %f\n", yaw);
        rosserial_publish(&yaw);
    }
}

void app_main(){
    initialize();
    xTaskCreatePinnedToCore(push_data, "rosserial_publisher", 8192, NULL, 22, NULL, 0);
}