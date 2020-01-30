#include "freertos/FreeRTOS.h"
#include "esp_timer.h"
#include "freertos/task.h"
#include "encoder.h"
#include "pin_defs.h"

#define RPM_FACTOR 111111.111111111     //(1000000*60)/(135*4)
#define time_window 88888

void IRAM_ATTR enc_isr_handler0(encoder_t* encoder){
    encoder->time_gap_lower_limit = esp_timer_get_time();   
    if(encoder->dir)
      encoder->ticks_count++;
    else
      encoder->ticks_count--;
 }

void IRAM_ATTR enc_isr_handler1(encoder_t* encoder){
    encoder->time_gap_lower_limit = esp_timer_get_time();
    if(encoder->dir)
      encoder->ticks_count++;
    else
      encoder->ticks_count--;
}

void calculate_rpm(encoder_t* encoder){
  encoder->time_gap_upper_limit = esp_timer_get_time();
  encoder->const_period_count++;
  encoder->total_ticks += encoder->ticks_count;
  if(encoder->ticks_count != 0){
    encoder->curr_rpm = (encoder->ticks_count * RPM_FACTOR)/(time_window*encoder->const_period_count + encoder->pre_time_gap - (encoder->time_gap_upper_limit - encoder->time_gap_lower_limit));
    encoder->ticks_count = 0;
    encoder->const_period_count = 0;
  }
  else
    encoder->curr_rpm = 0;
}

void setup_rpm_calculator(encoder_t* encoder){
  const esp_timer_create_args_t periodic_timer_args = {
          .callback = calculate_rpm,
          .arg = encoder,
          .name = encoder->name
  };
  esp_timer_create(&periodic_timer_args, &(encoder->periodic_timer));
  esp_timer_start_periodic(encoder->periodic_timer, time_window);
}

void init_encoder(encoder_t* encoder){
  init_interrupt(encoder->enc_intr0);
  init_interrupt(encoder->enc_intr1);
  gpio_isr_handler_add(encoder->enc_intr0, (void*) enc_isr_handler0, (void*) encoder);
  gpio_isr_handler_add(encoder->enc_intr1, (void*) enc_isr_handler1, (void*) encoder);
  setup_rpm_calculator(encoder);
}