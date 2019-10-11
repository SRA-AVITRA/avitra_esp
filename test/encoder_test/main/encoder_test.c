#include "freertos/FreeRTOS.h"
#include "esp_timer.h"
#include "freertos/task.h"
#include "encoder_test.h"
#include "pin_defs.h"

void IRAM_ATTR enc_isr_handler(encoder_t* encoder)
{
    if(gpio_get_level(encoder->enc_dir)== 0){
        encoder->ticks_count++;
    }
    else{
        encoder->ticks_count--;
    }
}

void init_encoder(encoder_t* encoder){
    printf("init_encoder()\n");
    init_gpio(encoder->enc_dir, GPIO_MODE_INPUT);
    init_interrupt(encoder->enc_intr);
	gpio_isr_handler_add(encoder->enc_intr, enc_isr_handler, (void*) encoder);
    setup_ticks_calculator(encoder);
    printf("init_encoder() END\n");
}

void calculate_ticks(encoder_t* encoder){
    encoder->total_ticks +=  encoder->ticks_count;
    encoder->ticks_count = 0;
    vTaskDelay(1 / portTICK_RATE_MS);
}

void setup_ticks_calculator(encoder_t* encoder){
    printf("setup_rpm_calculator()\n");
    const esp_timer_create_args_t periodic_timer_args = {
            .callback = calculate_ticks,
            .arg = encoder,
            .name = encoder->name
    };

    esp_timer_create(&periodic_timer_args, &(encoder->periodic_timer));
    esp_timer_start_periodic(encoder->periodic_timer, 44444);
    printf("setup_ticks_calculator() ENDS\n");
}