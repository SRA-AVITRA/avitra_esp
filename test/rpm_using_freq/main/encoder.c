#include "freertos/FreeRTOS.h"
#include "esp_timer.h"
#include "freertos/task.h"
#include "encoder.h"
#include "pin_defs.h"

#define RPM_FACTOR 1000000*60*5/135

int64_t time = 0;
int64_t pre_time = 0;
int rpm = 0;
int ticks_count_in_ISR =0;

void IRAM_ATTR enc_isr_handler(encoder_t* encoder)
{
    ticks_count_in_ISR++;
    if(gpio_get_level(encoder->enc_dir)== 0){
        encoder->ticks_count++;
    }
    else{
        encoder->ticks_count--;
    }
    if(ticks_count_in_ISR > 4)
    {
        pre_time = time;
        time = esp_timer_get_time();    //update time
        rpm = RPM_FACTOR / (int64_t)((time - pre_time));
        ticks_count_in_ISR = 0;
    }
}

void init_encoder(encoder_t* encoder){
    printf("init_encoder()\n");
    init_gpio(encoder->enc_dir, GPIO_MODE_INPUT);
    init_interrupt(encoder->enc_intr);
	gpio_isr_handler_add(encoder->enc_intr, (void*)enc_isr_handler, (void*) encoder);
    esp_timer_init();   //start timer
    printf("init_encoder() END\n");
}

void calculate_rpm(){
    while(true){
        printf("rpm = %d\t delta = %lld\n",rpm, (time-pre_time));
    }
}
