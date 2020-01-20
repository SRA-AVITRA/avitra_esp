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

#include <math.h>

float cum_err_factor = 0;
float temp = 0;

void init_motor(motor_t *motor)
{
    init_mcpwm(&(motor->pwm_A));
    init_mcpwm(&(motor->pwm_B));
}

float map(float variable, float fron_min, float from_max, float to_min, float to_max)
{
    return ((variable - fron_min) * (to_max - to_min) / (from_max - fron_min) + to_min);
}

//Normal PI
void calculate_duty_cycle(motor_t *motor)
{
    // motor->Kp = 2;
    // motor->Kd = 0;
    // motor->Ki = 0.5;
    if (motor->Kp == 0 && motor->Kd == 0 && motor->Ki == 0)
    {
        motor->err = 0;
        motor->cum_err = 0;
        motor->duty_cycle = 0;
    }
    else
    {
        motor->err = (motor->desr_rpm - motor->encoder.curr_rpm) / 10;
        motor->pTerm = motor->Kp * motor->err;
        motor->dTerm = motor->Kd * ((motor->err - motor->prev_err) * 100);
        motor->cum_err += motor->err/5;
        motor->iTerm = motor->Ki * motor->cum_err;
        // if (motor->iTerm > motor->iTerm_limit)
        // {
        //     motor->iTerm = motor->iTerm_limit;
        // }
        // else if (motor->iTerm < -motor->iTerm_limit)
        // {
        //     motor->iTerm = -motor->iTerm_limit;
        // }
        motor->duty_cycle = motor->pTerm + motor->dTerm + motor->iTerm;
        motor->actual_duty_cycle = motor->duty_cycle;
        motor->encoder.prev_rpm = motor->encoder.curr_rpm;
        motor->prev_err = motor->err;
        motor->prev_duty_cycle = motor->duty_cycle;
    }
    // ESP_LOGI("calculate_duty_cycle", "temp = %f\t motor->err = %f\t motor->curr_rpm = %f\t cum_err_factor = %f", temp, motor->err, motor->encoder.curr_rpm, cum_err_factor);
    write_duty_cycle(motor);
}

//PI with mapped cum_err_factor
// void calculate_duty_cycle(motor_t *motor)
// {
//     // motor->Kp = 2;
//     // motor->Kd = 0;
//     // motor->Ki = 0.5;
//     if (motor->Kp == 0 && motor->Kd == 0 && motor->Ki == 0)
//     {
//         motor->err = 0;
//         motor->cum_err = 0;
//         motor->duty_cycle = 0;
//     }
//     else
//     {
//         motor->err = (motor->desr_rpm - motor->encoder.curr_rpm) / 10;
//         motor->pTerm = motor->Kp * motor->err;
//         motor->dTerm = motor->Kd * ((motor->err - motor->prev_err) * 100);
//         if (motor->err < 0.1 && motor->err > -0.1)
//         {
//             if (motor->err < 0)
//             {
//                 temp = -motor->err;
//             }
//             else
//             {
//                 temp = motor->err;
//             }
//             cum_err_factor = map(temp, 0, motor->desr_rpm / 10, 0, 1);          //linear map
//             cum_err_factor = (float)(exp(temp / 0.5));                          //(float)(exp(5));     //exponential map
//         }
//         else
//         {
//             cum_err_factor = 1;
//         }
//         motor->cum_err += motor->err * cum_err_factor / 5;
//         motor->iTerm = motor->Ki * motor->cum_err;
//         motor->duty_cycle = motor->pTerm + motor->dTerm + motor->iTerm;
//         motor->actual_duty_cycle = motor->duty_cycle;
//         motor->encoder.prev_rpm = motor->encoder.curr_rpm;
//         motor->prev_err = motor->err;
//         motor->prev_duty_cycle = motor->duty_cycle;
//         // ESP_LOGI("calculate_duty_cycle", "temp = %f\t motor->err = %f\t motor->cum_err = %f\t cum_err_factor = %f", temp, motor->err, motor->cum_err, cum_err_factor);
//     }
//     write_duty_cycle(motor);
// }

//PI with filter
// void calculate_duty_cycle(motor_t *motor)
// {
//     // motor->Kp = 2;
//     // motor->Kd = 0;
//     // motor->Ki = 0.5;
//     if (motor->Kp == 0 && motor->Kd == 0 && motor->Ki == 0)
//     {
//         motor->err = 0;
//         motor->cum_err = 0;
//         motor->duty_cycle = 0;
//     }
//     else
//     {
//         motor->err = (motor->desr_rpm - motor->encoder.curr_rpm) / 10;
//         motor->pTerm = motor->Kp * motor->err;
//         motor->dTerm = motor->Kd * ((motor->err - motor->prev_err) * 100);
//         motor->cum_err += motor->err * cum_err_factor/5;
//         motor->cum_err += motor->err/5;
//         motor->iTerm = motor->Ki * motor->cum_err;
//         motor->duty_cycle = motor->pTerm + motor->dTerm + motor->iTerm;

//         // Low pass filter
//         // motor->duty_cycle = motor->duty_cycle * (1 - 0.5) + motor->prev_duty_cycle * (0.5);

//         // Exponential filter
//         // motor->duty_cycle = motor->duty_cycle + 0.5*(motor->prev_duty_cycle - motor->duty_cycle);

//         motor->actual_duty_cycle = motor->duty_cycle;
//         motor->encoder.prev_rpm = motor->encoder.curr_rpm;
//         motor->prev_err = motor->err;
//         motor->prev_duty_cycle = motor->duty_cycle;
//     }
//     // ESP_LOGI("calculate_duty_cycle", "temp = %f\t motor->err = %f\t motor->curr_rpm = %f\t cum_err_factor = %f", temp, motor->err, motor->encoder.curr_rpm, cum_err_factor);
//     write_duty_cycle(motor);
// }

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