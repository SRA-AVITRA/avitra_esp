#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "init_sra.h"
#include "pin_defs.h"
#include "motor.h"
#include "rosserial.h"

motor_t motor_F = (motor_t) {.name = "MOTOR_F", .id = 0, .desr_rpm = 0, .Kp = 0.0,  .Kd = 0.0, .duty_cycle = 0,  \
                        .encoder = {.name = "MOTOR_F", .id = 0, .curr_rpm = 0, .ticks_count = 0, .enc_intr0 = ENCODER_F_A, .enc_intr1 = ENCODER_F_B},  \
                        .pwm_A = {.pwm_unit = MCPWM_UNIT_0, .pwm_timer = MCPWM_TIMER_0, .pwm_operator = MCPWM_OPR_A, .pwm_io_signals = MCPWM0A, .pwm_pin = MOTOR_F_PWM_A}, \
                        .pwm_B = {.pwm_unit = MCPWM_UNIT_0, .pwm_timer = MCPWM_TIMER_0, .pwm_operator = MCPWM_OPR_B, .pwm_io_signals = MCPWM0B, .pwm_pin = MOTOR_F_PWM_B}  \
                    };

motor_t motor_L = (motor_t) {.name = "MOTOR_L", .id = 1, .desr_rpm = 0, .Kp = 0.0,  .Kd = 0.0, .duty_cycle = 0,  \
                        .encoder = {.name = "MOTOR_L", .id = 1, .curr_rpm = 0, .ticks_count = 0, .enc_intr0 = ENCODER_L_A, .enc_intr1 = ENCODER_L_B},  \
                        .pwm_A = {.pwm_unit = MCPWM_UNIT_0, .pwm_timer = MCPWM_TIMER_1, .pwm_operator = MCPWM_OPR_A, .pwm_io_signals = MCPWM1A, .pwm_pin = MOTOR_L_PWM_A}, \
                        .pwm_B = {.pwm_unit = MCPWM_UNIT_0, .pwm_timer = MCPWM_TIMER_1, .pwm_operator = MCPWM_OPR_B, .pwm_io_signals = MCPWM1B, .pwm_pin = MOTOR_L_PWM_B}  \
                    };

motor_t motor_R = (motor_t) {.name = "MOTOR_R", .id = 2, .desr_rpm = 60, .Kp = 0.0,  .Kd = 0.0, .duty_cycle = 0, .alpha = 0.3, .iTerm_limit = 30, \
                        .encoder = {.name = "MOTOR_R", .id = 2, .curr_rpm = 0, .ticks_count = 0, .enc_intr1 = ENCODER_R_A, .enc_intr0 = ENCODER_R_B},  \
                        .pwm_A = {.pwm_unit = MCPWM_UNIT_1, .pwm_timer = MCPWM_TIMER_0, .pwm_operator = MCPWM_OPR_A, .pwm_io_signals = MCPWM0A, .pwm_pin = MOTOR_R_PWM_A}, \
                        .pwm_B = {.pwm_unit = MCPWM_UNIT_1, .pwm_timer = MCPWM_TIMER_0, .pwm_operator = MCPWM_OPR_B, .pwm_io_signals = MCPWM0B, .pwm_pin = MOTOR_R_PWM_B}  \
                    };

motor_t motor_B = (motor_t) {.name = "MOTOR_B", .id = 3, .desr_rpm = 0, .Kp = 0.0,  .Kd = 0.0, .duty_cycle = 0,  \
                        .encoder = {.name = "MOTOR_B", .id = 3, .curr_rpm = 0, .ticks_count = 0, .enc_intr0 = ENCODER_B_A, .enc_intr1 = ENCODER_B_B},  \
                        .pwm_A = {.pwm_unit = MCPWM_UNIT_1, .pwm_timer = MCPWM_TIMER_1, .pwm_operator = MCPWM_OPR_A, .pwm_io_signals = MCPWM1A, .pwm_pin = MOTOR_B_PWM_A}, \
                        .pwm_B = {.pwm_unit = MCPWM_UNIT_1, .pwm_timer = MCPWM_TIMER_1, .pwm_operator = MCPWM_OPR_B, .pwm_io_signals = MCPWM1B, .pwm_pin = MOTOR_B_PWM_B}  \
                    };

void initialize(){
    init_motor(&motor_R);
    init_encoder(&motor_R.encoder);
    motor_R.prev_err = motor_R.desr_rpm;
}

void drive(){
    while(1){
        calculate_duty_cycle(&motor_R);     // write_duty_cycle already called in this function
        vTaskDelay(10/portTICK_RATE_MS);
    }
}

void get_data(){   
    while(1){
        rosserial_publish(&motor_R);
        rosserial_subscribe(&motor_L, &motor_R);
        vTaskDelay(10/portTICK_RATE_MS);
    }
}

void app_main(){
    rosserial_setup();
    xTaskCreatePinnedToCore(get_data, "rosserial_subscribe", 8192, NULL, 22, NULL, 0);
    vTaskDelay(10000/portTICK_RATE_MS);
    initialize();
    xTaskCreatePinnedToCore(drive, "drive", 8192, NULL, 23, NULL, 1);
}