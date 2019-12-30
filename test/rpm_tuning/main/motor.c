#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "motor.h"
#include "pin_defs.h"
#include <math.h>

void init_motor(motor_t* motor){
    init_mcpwm(&(motor->pwm_A));
    init_mcpwm(&(motor->pwm_B));
}

float map(float input, float input_min, float input_max, float output_min, float output_max){
    float output = 0.0;
    output = output_min + ((output_max - output_min) / (input_max - input_min)) * (input - input_min);
   
    if(output < output_min)
        output = output_min;
   else if(output > output_max)
        output = output_max;

    return output;
}

// void calculate_duty_cycle(motor_t* motor){
//     motor->err = motor->desr_rpm - motor->encoder.curr_rpm;
//     if(motor->desr_rpm > 0)
//     	//motor->opt = 47.17155348582-4.75 
//         motor->opt = 29.72411863061209 +  9.31753403*pow(10,-1)*pow(motor-> desr_rpm,1) - 1.05174732*pow(10,-2)*pow(motor-> desr_rpm,2) + 4.09964372*pow(10,-5)*pow(motor-> desr_rpm,3);
//     else if(motor->desr_rpm < 0)
//         //motor->opt = -47.17155348582+4.75
//         motor->opt = -29.8253378318297 + 8.77361922*pow(10,-1)*pow(motor-> desr_rpm,1) + 9.42125283*pow(10,-3)*pow(motor-> desr_rpm,2) + 3.40221433*pow(10,-5)*pow(motor-> desr_rpm,3);
//     else
//         motor->opt = 0;

//     // motor->time = esp_timer_get_time();    //update time
//     // // motor->duty_cycle = motor->opt + (motor->Kp)*motor->err + (motor->Ki)*(motor->cum_err)*(motor->time - motor->prev_time)/1000000;
//     // motor->duty_cycle = motor->opt + (motor->Kp)*(motor->err) + (motor->Kd)*(motor->err)/(motor->time - motor->prev_time)*1000000;
//     // // motor->duty_cycle = motor->opt;

//     // motor->prev_time = motor->time;
//     // motor->prev_err = motor->err;

//     write_duty_cycle(motor);
// }

void calculate_duty_cycle(motor_t* motor){
    motor->err = motor->desr_rpm - motor->encoder.curr_rpm;
    if(motor->name == 'MOTOR_L')
    {
    	motor->opt = (motor->desr_rpm/abs(motor->desr_rpm))*(29.72411863061209 +  9.31753403*pow(10,-1)*pow(motor-> desr_rpm,1) - 1.05174732*pow(10,-2)*pow(motor-> desr_rpm,2) + 4.09964372*pow(10,-5)*pow(motor-> desr_rpm,3));
    }
    else if(motor-> == 'MOTOR_R')
    {
    	motor->opt = (motor->desr_rpm/abs(motor->desr_rpm))*(29.8253378318297 + 8.77361922*pow(10,-1)*pow(motor-> desr_rpm,1) - 9.42125283*pow(10,-3)*pow(motor-> desr_rpm,2) + 3.40221433*pow(10,-5)*pow(motor-> desr_rpm,3));
    }
    motor->duty_cycle = motor->opt + (motor->Kp)*(motor->err) - (motor->Kd)*(motor->err)/(motor->time - motor->prev_time)*1000000;
    motor->prev_time = motor->time;
    motor->prev_err = motor->err;
    write_duty_cycle(motor);
}

void write_duty_cycle(motor_t* motor){
    if(motor->duty_cycle > 0){
        motor->encoder.dir = true;
        if(motor->duty_cycle > 100)
            motor->duty_cycle = 100;
       
        mcpwm_set_duty(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, 0);
        mcpwm_set_duty_type(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, MCPWM_DUTY_MODE_0);

        mcpwm_set_duty(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, abs(motor->duty_cycle));
        mcpwm_set_duty_type(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, MCPWM_DUTY_MODE_0);
    }
    else if(motor->duty_cycle < 0){
        motor->encoder.dir = false;
        if(motor->duty_cycle < -100)
            motor->duty_cycle = -100;
        mcpwm_set_duty(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, abs(motor->duty_cycle));
        mcpwm_set_duty_type(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, MCPWM_DUTY_MODE_0);

        mcpwm_set_duty(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, 0);
        mcpwm_set_duty_type(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, MCPWM_DUTY_MODE_0);
    }
    else if(motor->duty_cycle == -1){
        mcpwm_set_duty(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, 0);
        mcpwm_set_duty_type(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, MCPWM_DUTY_MODE_0);
        mcpwm_set_duty(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, 0);
        mcpwm_set_duty_type(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, MCPWM_DUTY_MODE_0);
    }
    else{
        mcpwm_set_duty(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, 100);
        mcpwm_set_duty_type(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, MCPWM_DUTY_MODE_0);
        mcpwm_set_duty(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, 100);
        mcpwm_set_duty_type(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, MCPWM_DUTY_MODE_0);
    }
}