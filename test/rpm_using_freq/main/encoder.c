#include "freertos/FreeRTOS.h"
#include "esp_timer.h"
#include "driver/timer.h"
#include "freertos/task.h"
#include "encoder.h"
#include "pin_defs.h"

#define RPM_FACTOR 40000000*60/135
#define ESP_RPM_FACTOR 1000000*60/135

uint64_t time = 0;
uint64_t pre_time = 0;
int64_t esp_time = 0;
int64_t pre_esp_time = 0;
int count = 0;
int esp_count = 0;

float rpm = 0;
float esp_rpm = 0;
float rpm_sum = 0;
float esp_rpm_sum = 0;

void IRAM_ATTR enc_isr_handler(encoder_t* encoder)
{
    if(gpio_get_level(encoder->enc_dir)== 0){
        encoder->ticks_count++;
    }
    else{
        encoder->ticks_count--;
    }
    pre_time = time;
    pre_esp_time = esp_time;
    timer_get_counter_value(0, 0, &time);
    esp_time = esp_timer_get_time();
    // count++;
    esp_count++;
}

void init_encoder(encoder_t* encoder){
    printf("init_encoder()\n");
    init_gpio(encoder->enc_dir, GPIO_MODE_INPUT);
    init_interrupt(encoder->enc_intr);
	gpio_isr_handler_add(encoder->enc_intr, enc_isr_handler, (void*) encoder);
    timer_start(0, 0);  //timer.h
    esp_timer_init();   //esp_timer.h
    printf("init_encoder() END\n");
}

void calculate_rpm(){
    while(true){
        if(time != pre_time)
            if(count < 8)
                rpm_sum += ((float)RPM_FACTOR / (time - pre_time));
            else{
                rpm = rpm_sum / 8;
                rpm_sum = 0;
                count = 0;
            }
        else
            rpm = 0;
        if(esp_time != pre_esp_time)
            if(esp_count < 8)
                esp_rpm_sum += ((float)ESP_RPM_FACTOR / (esp_time - pre_esp_time));
            else{
                esp_rpm = esp_rpm_sum / 8;
                esp_rpm_sum = 0;
                esp_count = 0;
            }
        else
            esp_rpm = 0;
        count++;
        printf("rpm = %f\t esp_rpm = %f count = %d\t esp_count = %d\n", rpm, esp_rpm, count, esp_count);
        // vTaskDelay(1 / portTICK_RATE_MS);    
    }
}
