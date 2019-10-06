#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "init_sra.h"
#include "pin_defs.h"
#include "encoder_test.h"

encoder_commander_t encoder_F = {.name = "ENCODER_F", .id = 0, .enc_intr = ENCODER_F_A, .enc_dir = ENCODER_F_B, .ticks_count = 0, .total_ticks = 0, .curr_rpm = 0};
encoder_commander_t encoder_L = {.name = "ENCODER_L", .id = 1, .enc_intr = ENCODER_L_A, .enc_dir = ENCODER_L_B, .ticks_count = 0, .total_ticks = 0, .curr_rpm = 0};
encoder_commander_t encoder_R = {.name = "ENCODER_R", .id = 2, .enc_intr = ENCODER_R_A, .enc_dir = ENCODER_R_B, .ticks_count = 0, .total_ticks = 0, .curr_rpm = 0};
encoder_commander_t encoder_B = {.name = "ENCODER_B", .id = 3, .enc_intr = ENCODER_B_A, .enc_dir = ENCODER_B_B, .ticks_count = 0, .total_ticks = 0, .curr_rpm = 0};

void app_main(){
    init_encoder(&encoder_F);
    init_encoder(&encoder_L);
    init_encoder(&encoder_R);
    init_encoder(&encoder_B);
    while(true){
    	printf("Ticks_L = %ld\t Ticks_R = %ld\n",encoder_L.total_ticks,encoder_R.total_ticks);
        vTaskDelay(1 / portTICK_RATE_MS);
    }
}