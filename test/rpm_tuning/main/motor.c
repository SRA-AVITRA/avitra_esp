#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motor.h"
#include "pin_defs.h"

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

void calculate_duty_cycle(motor_t* motor){
    motor->err = motor->desr_rpm - motor->encoder.curr_rpm;
    motor->cum_err += motor->err;
    
    if(motor->err * motor->prev_err < 0)  //check if err * prev_error < 0
        motor->cum_err = 0;

    if(motor->cum_err > 10)    //random have to find later
        motor->cum_err = 10;
    else if(motor->cum_err < -10)    //random have to find later
        motor->cum_err = -10;

    motor->del_duty_cycle = (motor->Kp)*motor->err + (motor->Kd)*(motor->err-motor->prev_err) + (motor->Ki)*(motor->cum_err);
    motor->duty_cycle = motor->del_duty_cycle;
    motor->prev_err = motor->err;
    
    write_duty_cycle(motor);
}

void write_duty_cycle(motor_t* motor){
    if(motor->duty_cycle > 0){
        motor->encoder.dir=true;
        if(motor->duty_cycle > 100)
            motor->duty_cycle = 100;
        
        mcpwm_set_duty(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, 0);
        mcpwm_set_duty_type(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, MCPWM_DUTY_MODE_0);

        mcpwm_set_duty(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, abs(motor->duty_cycle));
        mcpwm_set_duty_type(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, MCPWM_DUTY_MODE_0);
    }
    else if(motor->duty_cycle < 0){
        motor->encoder.dir=false;
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