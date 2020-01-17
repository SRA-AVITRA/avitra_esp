#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "motor.h"
#include "pin_defs.h"
#include <math.h>
#include "esp_timer.h"

#include "esp_system.h"
#include "esp_err.h"
#include "esp_log.h"

void init_motor(motor_t *motor)
{
    init_mcpwm(&(motor->pwm_A));
    init_mcpwm(&(motor->pwm_B));
}

void calculate_duty_cycle(motor_t *motor)
{
    if(motor->desr_rpm == 0)
    {
        motor->err = 0;
        motor->cum_err = 0;
        motor->duty_cycle = 0;
    }
    else
    {
        motor->err = (motor->desr_rpm - motor->encoder.curr_rpm) / 10;
        motor->pTerm = motor->Kp * motor->err;
        motor->dTerm = motor->Kd * ((motor->err - motor->prev_err)*100);
        motor->cum_err += motor->err/5;
        motor->iTerm = motor->Ki * motor->cum_err;
        if (motor->iTerm > motor->iTerm_limit)
        {
            motor->iTerm = motor->iTerm_limit;
        }
        if (motor->iTerm < -motor->iTerm_limit)
        {
            motor->iTerm = -motor->iTerm_limit;
        }
        motor->duty_cycle = motor->pTerm + motor->dTerm + motor->iTerm;
        motor->duty_cycle = motor->duty_cycle*(1 - motor->alpha) + motor->prev_duty_cycle*(motor->alpha);
        motor->actual_duty_cycle = motor->duty_cycle;
        motor->encoder.prev_rpm = motor->encoder.curr_rpm;
        motor->prev_err = motor->err;
        motor->prev_duty_cycle = motor->duty_cycle;
    }
    write_duty_cycle(motor);
}

void write_duty_cycle(motor_t *motor)
{
    if (motor->duty_cycle > 0)
    {
        motor->encoder.dir = true;
        if (motor->duty_cycle > 100)
            motor->duty_cycle = 100;

        mcpwm_set_duty(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, 0);
        mcpwm_set_duty_type(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, MCPWM_DUTY_MODE_0);

        mcpwm_set_duty(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, abs(motor->duty_cycle));
        mcpwm_set_duty_type(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, MCPWM_DUTY_MODE_0);
    }
    else if (motor->duty_cycle < 0)
    {
        motor->encoder.dir = false;
        if (motor->duty_cycle < -100)
            motor->duty_cycle = -100;
        mcpwm_set_duty(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, abs(motor->duty_cycle));
        mcpwm_set_duty_type(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, MCPWM_DUTY_MODE_0);

        mcpwm_set_duty(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, 0);
        mcpwm_set_duty_type(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, MCPWM_DUTY_MODE_0);
    }
    else if (motor->duty_cycle == -1)
    {
        mcpwm_set_duty(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, 0);
        mcpwm_set_duty_type(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, MCPWM_DUTY_MODE_0);
        mcpwm_set_duty(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, 0);
        mcpwm_set_duty_type(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, MCPWM_DUTY_MODE_0);
    }
    else
    {
        mcpwm_set_duty(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, 100);
        mcpwm_set_duty_type(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, MCPWM_DUTY_MODE_0);
        mcpwm_set_duty(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, 100);
        mcpwm_set_duty_type(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, MCPWM_DUTY_MODE_0);
    }
}