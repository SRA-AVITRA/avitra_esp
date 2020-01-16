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
    motor->opt = 41.86257414592657 + 0.15232979*motor->desr_rpm;

    motor->err = (motor->desr_rpm - motor->encoder.curr_rpm) / 10;

    motor->pTerm = motor->Kp * motor->err;

    motor->dTerm = motor->Kd * ((motor->err - motor->prev_err)*100);
    
    if (motor->err < 10 && motor->err > -10)
    {
        motor->cum_err += motor->err;
        motor->iTerm = motor->Ki * motor->cum_err;
        if (motor->iTerm > motor->iTerm_limit)
        {
            motor->iTerm = motor->iTerm_limit;
        }
        if (motor->iTerm < -motor->iTerm_limit)
        {
            motor->iTerm = -motor->iTerm_limit;
        }
    }
    else
    {
        motor->iTerm = 0;
    }

    motor->duty_cycle = motor->opt + motor->pTerm + motor->dTerm + motor->iTerm;

    // motor->duty_cycle = motor->duty_cycle*(1 - motor->alpha) + motor->prev_duty_cycle*(motor->alpha);

    // motor->actual_duty_cycle = motor->duty_cycle;

    // if (motor->duty_cycle > 100)
    // {
    //     motor->duty_cycle = 100;
    // }
    // else if (motor->duty_cycle < 25)
    // {
    //     motor->duty_cycle = 25;
    // }

    // ESP_LOGI("calculate_duty_cycle", "calculated duty_cycle = %f, actual dutycycle = %f", motor->duty_cycle, motor->actual_duty_cycle);
    // ESP_LOGI("PID", "PID TERMS : pre_error = %d, error_term = %d, kp*err = %f, kd*pre-err = %f, ki*int_err = %f, actual_motor->iterm = %f", motor->prev_err, motor->err, motor->Kp * motor->err, motor->dTerm, motor->iTerm, motor->Ki*motor->cum_err);
    // ESP_LOGI("RPM", "RPM VALUES : desr_rpm = %d, prev_rpm = %d, current_rpm = %d \n", motor->desr_rpm, motor->encoder.prev_rpm, motor->encoder.curr_rpm);

    motor->encoder.prev_rpm = motor->encoder.curr_rpm;
    motor->prev_err = motor->err;
    motor->prev_duty_cycle = motor->duty_cycle;
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