#include "stdio.h"
#include "rosserial_test.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

float pwm_l = 0;
float pwm_r = 0;
long int ticks_l = 0;
long int ticks_r = 0;

int app_main(){
    rosserial_setup();
    while(1){
    	ticks_l+=1;
    	ticks_r-=1;
    	rosserial_subscribe(&pwm_l, &pwm_r);
        rosserial_publish(&ticks_l, &ticks_r);
        vTaskDelay(100 / portTICK_RATE_MS);		//100ms
    }
}
