#ifndef _ENCODER_H
#define _ENCODER_H

#include "init_sra.h"

typedef struct{
    char  name[10];
    int   id;
    float   curr_rpm;
    float   esp_curr_rpm;
    volatile long int ticks_count;
    volatile long int total_ticks;
    gpio_num_t enc_intr;
    gpio_num_t enc_dir;
    esp_timer_handle_t periodic_timer;
}encoder_t;

void init_encoder(encoder_t *encoder);    //TODO: add parameter for type of edge

void IRAM_ATTR enc_isr_handler(encoder_t* encoder);

void calculate_rpm();

#endif