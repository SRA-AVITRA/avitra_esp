#ifndef _ENCODER_TEST_H
#define _ENCODER_TEST_H

#include "init_sra.h"

typedef struct{
    char  name[10];
    int   id;
    float   curr_rpm;
    volatile long int ticks_count;
    gpio_num_t enc_intr;
    gpio_num_t enc_dir;
}encoder_t;

void init_encoder(encoder_t *encoder);    //TODO: add parameter for type of edge

void IRAM_ATTR enc_isr_handler(encoder_t* encoder);

#endif