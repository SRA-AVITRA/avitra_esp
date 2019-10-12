

/////////All the motors turn in cockwise direction. To change the dirrection swap the .pwm_pin parameter of the respective motor/////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "pin_defs.h"
#include "motor_test.h"


#define MAXPWM 65.0
#define MINPWM 35.0
#define ENCODING_FACTOR (MAXPWM)/40.0

motor_t motor_F = (motor_t) {.name = "MOTOR_F", .id = 0, .duty_cycle = 0,  \
                        .pwm_A = {.pwm_unit = MCPWM_UNIT_0, .pwm_timer = MCPWM_TIMER_0, .pwm_operator = MCPWM_OPR_A, .pwm_io_signals = MCPWM0A, .pwm_pin = MOTOR_F_PWM_A}, \
                        .pwm_B = {.pwm_unit = MCPWM_UNIT_0, .pwm_timer = MCPWM_TIMER_0, .pwm_operator = MCPWM_OPR_B, .pwm_io_signals = MCPWM0B, .pwm_pin = MOTOR_F_PWM_B}  \
                    };

motor_t motor_L = (motor_t) {.name = "MOTOR_L", .id = 1, .duty_cycle = 0,  \
                        .pwm_A = {.pwm_unit = MCPWM_UNIT_0, .pwm_timer = MCPWM_TIMER_1, .pwm_operator = MCPWM_OPR_A, .pwm_io_signals = MCPWM1A, .pwm_pin = MOTOR_L_PWM_A}, \
                        .pwm_B = {.pwm_unit = MCPWM_UNIT_0, .pwm_timer = MCPWM_TIMER_1, .pwm_operator = MCPWM_OPR_B, .pwm_io_signals = MCPWM1B, .pwm_pin = MOTOR_L_PWM_B}  \
                    };

motor_t motor_R = (motor_t) {.name = "MOTOR_R", .id = 2, .duty_cycle = 0, \
                        .pwm_A = {.pwm_unit = MCPWM_UNIT_1, .pwm_timer = MCPWM_TIMER_0, .pwm_operator = MCPWM_OPR_A, .pwm_io_signals = MCPWM0A, .pwm_pin = MOTOR_R_PWM_A}, \
                        .pwm_B = {.pwm_unit = MCPWM_UNIT_1, .pwm_timer = MCPWM_TIMER_0, .pwm_operator = MCPWM_OPR_B, .pwm_io_signals = MCPWM0B, .pwm_pin = MOTOR_R_PWM_B}  \
                    };

motor_t motor_B = (motor_t) {.name = "MOTOR_B", .id = 3,.duty_cycle = 0,  \
                        .pwm_A = {.pwm_unit = MCPWM_UNIT_1, .pwm_timer = MCPWM_TIMER_1, .pwm_operator = MCPWM_OPR_A, .pwm_io_signals = MCPWM1A, .pwm_pin = MOTOR_B_PWM_B}, \
                        .pwm_B = {.pwm_unit = MCPWM_UNIT_1, .pwm_timer = MCPWM_TIMER_1, .pwm_operator = MCPWM_OPR_B, .pwm_io_signals = MCPWM1B, .pwm_pin = MOTOR_B_PWM_A}  \
                    };

void bot_motion(){
    float pwm = 10;
    bool flag = true;
    while(true){
        if(pwm < 30 && flag){
            pwm++;
            if(pwm == 30)
                flag = false;
        }
        else if(pwm > 10 && ~flag)
            pwm--;
        else
            pwm = 0;

        motor_F.duty_cycle = ENCODING_FACTOR * pwm;
        motor_L.duty_cycle = ENCODING_FACTOR * pwm;
        motor_R.duty_cycle = ENCODING_FACTOR * pwm;
        motor_B.duty_cycle = ENCODING_FACTOR * pwm;
        write_duty_cycle(&motor_F);
        write_duty_cycle(&motor_L);
        write_duty_cycle(&motor_R);
        write_duty_cycle(&motor_B);
        vTaskDelay(500 / portTICK_RATE_MS);
    
    }
}

void app_main(){
    init_motor(&motor_F);
    init_motor(&motor_L);
    init_motor(&motor_B);
    init_motor(&motor_R);
    xTaskCreate(bot_motion, "motor_test", 8192, NULL, 23, NULL);
    while(true){
        vTaskDelay(1 / portTICK_RATE_MS);        
    }
}