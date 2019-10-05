#include "stdio.h"
#include "rosserial_test.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

int pwm_l = 0;
int pwm_r = 0;
long long unsigned int ticks_l = 99165134652;
long long unsigned int ticks_r = 10145643546;

int app_main(){
    rosserial_setup();
    while(1){
    	rosserial_subscribe(&pwm_l, &pwm_r);
        rosserial_publish(&ticks_l, &ticks_r);
        vTaskDelay(10);		//100ms
    }
}
