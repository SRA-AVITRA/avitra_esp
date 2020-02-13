#ifndef ROSSERIAL_H
#define ROSSERIAL_H
#include "motor.h"

#ifdef __cplusplus
extern "C" {
#endif

void rosserial_setup();

void rosserial_publish(float *duty_cycle_L, float *duty_cycle_R, float *desr_rpm_L, float *desr_rpm_R, float *curr_rpm_L, float *curr_rpm_R);

void rosserial_subscribe(motor_t *motor_L, motor_t *motor_R);

#ifdef __cplusplus
}
#endif

#endif /* ROSSERIAL_H */
