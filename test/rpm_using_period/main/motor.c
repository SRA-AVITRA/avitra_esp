#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "motor.h"
#include "pin_defs.h"

void init_motor(motor_t* motor){
    init_mcpwm(&(motor->pwm_A));
    init_mcpwm(&(motor->pwm_B));
    init_encoder(&(motor->encoder));
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
    else{
        mcpwm_set_duty(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, 100);
        mcpwm_set_duty_type(motor->pwm_A.pwm_unit, motor->pwm_A.pwm_timer, motor->pwm_A.pwm_operator, MCPWM_DUTY_MODE_0);
        mcpwm_set_duty(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, 100);
        mcpwm_set_duty_type(motor->pwm_B.pwm_unit, motor->pwm_B.pwm_timer, motor->pwm_B.pwm_operator, MCPWM_DUTY_MODE_0);
    }


}