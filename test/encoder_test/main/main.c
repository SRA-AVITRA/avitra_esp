#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "init_sra.h"
#include "pin_defs.h"
#include "encoder_test.h"

encoder_t encoder_F = {.name = "ENCODER_F", .id = 0, .curr_rpm = 0, .ticks_count = 0, .enc_intr = ENCODER_F_A, .enc_dir = ENCODER_F_B};
encoder_t encoder_L = {.name = "ENCODER_L", .id = 1, .curr_rpm = 0, .ticks_count = 0, .enc_intr = ENCODER_L_A, .enc_dir = ENCODER_L_B};
encoder_t encoder_R = {.name = "ENCODER_R", .id = 2, .curr_rpm = 0, .ticks_count = 0, .enc_intr = ENCODER_R_A, .enc_dir = ENCODER_R_B};
encoder_t encoder_B = {.name = "ENCODER_B", .id = 3, .curr_rpm = 0, .ticks_count = 0, .enc_intr = ENCODER_B_A, .enc_dir = ENCODER_B_B};

void app_main(){
	init_encoder(&encoder_F);
	init_encoder(&encoder_L);
	init_encoder(&encoder_R);
	init_encoder(&encoder_B);

    while(true){
    	printf("Ticks_L = %ld\t Ticks_R = %ld\t",encoder_L.ticks_count,encoder_R.ticks_count);
    	printf("Ticks_F = %ld\t Ticks_B = %ld\n",encoder_F.ticks_count,encoder_B.ticks_count);
        vTaskDelay(1 / portTICK_RATE_MS);
    }
}