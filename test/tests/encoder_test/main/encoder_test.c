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
  gpio_isr_handler_add(encoder->enc_intr, (void*)enc_isr_handler, (void*) encoder);
  printf("init_encoder() END\n ");
}
