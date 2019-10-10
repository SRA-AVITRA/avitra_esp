#include "freertos/FreeRTOS.h"
#include "esp_timer.h"
#include "freertos/task.h"
#include "encoder.h"
#include "pin_defs.h"

#define RPM_FACTOR 111111.111111111     //(1000000*60)/(135*4)
#define time_window 88888

int64_t time_gap_lower_limit = 0;
int64_t time_gap_upper_limit = 0;
int64_t current_time_gap = 0;
int64_t pre_time_gap = 0;
int64_t eq_time = 0;
int const_period_count = 0;
int rpm = 0;

void IRAM_ATTR enc_isr_handler0(encoder_t* encoder)
{
    time_gap_lower_limit = esp_timer_get_time();   
    if(encoder->dir){
        encoder->ticks_count++;
    }
    else
    {
        encoder->ticks_count--;
    }
 }

void IRAM_ATTR enc_isr_handler1(encoder_t* encoder)
{
    time_gap_lower_limit = esp_timer_get_time();
    if(encoder->dir){
           encoder->ticks_count++;
       }
       else
       {
           encoder->ticks_count--;
       }
}

void setup_rpm_calculator(encoder_t* encoder){
    printf("setup_rpm_calculator()\n");
    const esp_timer_create_args_t periodic_timer_args = {
            .callback = calculate_rpm,
            .arg = encoder,
            .name = encoder->name
    };

    esp_timer_create(&periodic_timer_args, &(encoder->periodic_timer));
    esp_timer_start_periodic(encoder->periodic_timer, time_window);
    printf("setup_rpm_calculator() ENDS\n");
}

void init_encoder(encoder_t* encoder){
    printf("init_encoder()\n");
    //init_gpio(encoder->enc_dir0, GPIO_MODE_INPUT);
    init_interrupt(encoder->enc_intr0);
    init_interrupt(encoder->enc_intr1);
	gpio_isr_handler_add(encoder->enc_intr0, enc_isr_handler0, (void*) encoder);
    gpio_isr_handler_add(encoder->enc_intr1, enc_isr_handler1, (void*) encoder);
    setup_rpm_calculator(encoder);
    printf("init_encoder() END\n");
}

void calculate_rpm(encoder_t* encoder)
{
    time_gap_upper_limit = esp_timer_get_time();
    const_period_count++;
    if(encoder->ticks_count > 0)
    {
        pre_time_gap = current_time_gap;
        current_time_gap = time_gap_upper_limit - time_gap_lower_limit;
        eq_time = time_window*const_period_count + pre_time_gap - current_time_gap;
        rpm = (encoder->ticks_count * RPM_FACTOR)/eq_time;
        printf("encoder->ticks_count = %ld\t rpm = %d\n", encoder->ticks_count, rpm);     
        encoder->ticks_count = 0;
        const_period_count = 0;
    }
    else
    {
        rpm = 0;
    }
    vTaskDelay(10 / portTICK_RATE_MS);
}