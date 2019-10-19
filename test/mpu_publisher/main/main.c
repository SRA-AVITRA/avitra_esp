#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "init_sra.h"
#include "pin_defs.h"
#include "motor.h"
#include "rosserial.h"
#include "MPU.h"

uint8_t mag_rd[BUFF_SIZE];
int16_t mag_raw_value[BUFF_SIZE/2];
float mag_angle;

void initialize(){
    i2c_master_init();  //Initialise the I2C interface
    start_mpu();        //Intialise the MPU 
    rosserial_setup();
}

void push_data(){   
    while(1){
        getmag(mag_rd, mag_raw_value, &mag_angle);
        rosserial_publish(&mag_angle);
    }
}

void app_main(){
    initialize();
    xTaskCreatePinnedToCore(push_data, "rosserial_publisher", 8192, NULL, 22, NULL, 0);
}