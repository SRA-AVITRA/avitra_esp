#ifndef _MOTOR_H
#define _MOTOR_H

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
    float Ki; 
    float duty_cycle;
    float opt;
    int64_t time;
    int64_t prev_time;
    mcpwm_t pwm_A;
    mcpwm_t pwm_B;
    encoder_t encoder;
}motor_t;

void init_motor(motor_t *motor);

float map(float input, float input_min, float input_max, float output_min, float output_max);

void calculate_duty_cycle(motor_t* motor);

void write_duty_cycle(motor_t *motor);

#endif