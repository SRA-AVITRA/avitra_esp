#ifndef _MOTOR_H
#define _MOTOR_H

#include "init_sra.h"
#include "encoder.h"

typedef struct{
    int   id;
    char name[10];
    float Kp;
    float Kd;
    float Ki;

    float duty_cycle;
    float prev_duty_cycle;
    float desr_rpm;
    float err;
    float prev_err;
    float cum_err;
    float pTerm;
    float dTerm;
    float iTerm;
    float iTerm_limit;
    float alpha;
    
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