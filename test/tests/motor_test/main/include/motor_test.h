#ifndef _MOTOR_H
#define _MOTOR_H

#include "init_sra.h"


typedef struct{
    char  name[10];
    int   id;    
    float duty_cycle;
    mcpwm_t pwm_A;
    mcpwm_t pwm_B;
}motor_t;

void init_motor(motor_t *motor);

void write_duty_cycle(motor_t *motor);

#endif