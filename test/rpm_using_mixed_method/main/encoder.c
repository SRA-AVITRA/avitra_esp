#include "freertos/FreeRTOS.h"
#include "esp_timer.h"
#include "freertos/task.h"
#include "encoder.h"
#include "pin_defs.h"

#define RPM_FACTOR 1000000*60/135

int64_t time_gap_lower_limit = 0;
int64_t time_gap_upper_limit = 0;
int64_t current_time_gap = 0;
int64_t pre_time_gap = 0;
int64_t eq_time = 0;
int const_period_count = 0;
int rpm = 0;

void IRAM_ATTR enc_isr_handler(encoder_t* encoder)
{
    if(gpio_get_level(encoder->enc_dir)== 0){
        encoder->ticks_count++;
    }
    else{
        encoder->ticks_count--;
    }
    time_gap_lower_limit = esp_timer_get_time();
}

void init_encoder(encoder_t* encoder){
    printf("init_encoder()\n");
    init_gpio(encoder->enc_dir, GPIO_MODE_INPUT);
    init_interrupt(encoder->enc_intr);
	gpio_isr_handler_add(encoder->enc_intr, (void*)enc_isr_handler, (void*) encoder);
    esp_timer_init();
    setup_rpm_calculator(encoder);
    printf("init_encoder() END\n");
}

void calculate_rpm(encoder_t* encoder)
{
    const_period_count++;
    if(encoder->ticks_count > 0)
    {
        time_gap_upper_limit = esp_timer_get_time();
        pre_time_gap = current_time_gap;
        current_time_gap = time_gap_upper_limit - time_gap_lower_limit;
        eq_time = 44444*const_period_count + pre_time_gap - current_time_gap;
        rpm = (encoder->ticks_count * RPM_FACTOR)/eq_time;
        
        printf("encoder->ticks_count = %ld\t eq_time = %lld\t rpm = %d\t pre_time_gap = %lld\t current_time_gap = %lld\t const_period_count = %d\n",encoder->ticks_count, eq_time, rpm, pre_time_gap, current_time_gap, const_period_count);
        
        encoder->ticks_count = 0;
        const_period_count = 0;
    }
    vTaskDelay(1 / portTICK_RATE_MS);
}

void setup_rpm_calculator(encoder_t* encoder){
    printf("setup_rpm_calculator()\n");
    const esp_timer_create_args_t periodic_timer_args = {
            .callback = calculate_rpm,
            .arg = encoder,
            .name = encoder->name
    };

    esp_timer_create(&periodic_timer_args, &(encoder->periodic_timer));
    esp_timer_start_periodic(encoder->periodic_timer, 44444);
    printf("setup_rpm_calculator() ENDS\n");
}