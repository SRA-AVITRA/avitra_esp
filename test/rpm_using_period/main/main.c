#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "init_sra.h"
#include "pin_defs.h"
#include "motor.h"

motor_t motor_L = (motor_t) {.name = "MOTOR_L", .id = 1, .desr_rpm = 200, .Kp = 0.003,  .Kd = 0.75, .duty_cycle = 0,  \
                        .encoder = {.name = "MOTOR_L", .id = 1, .curr_rpm = 0, .ticks_count = 0, .enc_intr0 = ENCODER_L_A, .enc_intr1 = ENCODER_L_B},  \
                        .pwm_A = {.pwm_unit = MCPWM_UNIT_0, .pwm_timer = MCPWM_TIMER_1, .pwm_operator = MCPWM_OPR_A, .pwm_io_signals = MCPWM1A, .pwm_pin = MOTOR_L_PWM_A}, \
                        .pwm_B = {.pwm_unit = MCPWM_UNIT_0, .pwm_timer = MCPWM_TIMER_1, .pwm_operator = MCPWM_OPR_B, .pwm_io_signals = MCPWM1B, .pwm_pin = MOTOR_L_PWM_B}  \
                    };

motor_t motor_R = (motor_t) {.name = "MOTOR_R", .id = 2, .desr_rpm = 200, .Kp = 0.003,  .Kd = 0.75, .duty_cycle = 0, \
                        .encoder = {.name = "MOTOR_R", .id = 2, .curr_rpm = 0, .ticks_count = 0, .enc_intr1 = ENCODER_R_A, .enc_intr0 = ENCODER_R_B},  \
                        .pwm_A = {.pwm_unit = MCPWM_UNIT_1, .pwm_timer = MCPWM_TIMER_0, .pwm_operator = MCPWM_OPR_A, .pwm_io_signals = MCPWM0A, .pwm_pin = MOTOR_R_PWM_A}, \
                        .pwm_B = {.pwm_unit = MCPWM_UNIT_1, .pwm_timer = MCPWM_TIMER_0, .pwm_operator = MCPWM_OPR_B, .pwm_io_signals = MCPWM0B, .pwm_pin = MOTOR_R_PWM_B}  \
                    };

void initialize()
{
    init_motor(&motor_L);
    init_motor(&motor_R);
    gpio_set_direction(MOTOR_L_PWM_A, GPIO_MODE_OUTPUT); 
    gpio_set_direction(MOTOR_L_PWM_B, GPIO_MODE_OUTPUT); 
    gpio_set_direction(MOTOR_R_PWM_A, GPIO_MODE_OUTPUT);        
    gpio_set_direction(MOTOR_R_PWM_B, GPIO_MODE_OUTPUT);   
    gpio_set_level(MOTOR_L_PWM_A, 0);
    gpio_set_level(MOTOR_L_PWM_B, 1);  
    gpio_set_level(MOTOR_R_PWM_A, 1);
    gpio_set_level(MOTOR_R_PWM_B, 0);   

}

void app_main()
{
    initialize();
    while(true){
    	//printf("Ticks_L= %ld\t Ticks_R %ld\n",motor_L.encoder.total_ticks,motor_R.encoder.total_ticks);
        printf("Ticks_L = %ld\t RPM_L = %f\t Ticks_R = %ld\t RPM_R = %f\n",motor_L.encoder.total_ticks,motor_L.encoder.curr_rpm,motor_R.encoder.total_ticks,motor_R.encoder.curr_rpm);
        vTaskDelay(1 / portTICK_RATE_MS);
    }
}