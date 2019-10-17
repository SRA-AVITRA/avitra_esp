#ifndef _MOTOR_H
#define _MOTOR_H

#define KD_STEP 0.05
#define KP_STEP 0.002

#include "init_sra.h"
#include "encoder.h"

typedef struct{
    char  name[10];
    int   id;    
    int   desr_rpm;
    int16_t err;
    int16_t prev_err;
    int16_t cum_err;
    float Kp;
    float Kd;
    bool tune_mode;
    float Ki; 
    float duty_cycle;
    float del_duty_cycle;
    mcpwm_t pwm_A;
    mcpwm_t pwm_B;
    encoder_t encoder;
}motor_t;

void init_motor(motor_t *motor);

void write_duty_cycle(motor_t *motor);

#endif