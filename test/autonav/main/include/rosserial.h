#ifndef ROSSERIAL_H
#define ROSSERIAL_H
// #include "motor.h"

#ifdef __cplusplus
extern "C" {
#endif

void rosserial_setup();

void rosserial_publish_ticks(volatile long int* ticks_L,volatile long int* ticks_R);

void rosserial_publish_pid(float desr_rpm_L, float desr_rpm_R);

void rosserial_subscribe_teleop(float* duty_F, float* duty_B, float* duty_L, float* duty_R);

void rosserial_subscribe_rpm(float* rpm_L, float* rpm_R);

void rosserial_subscribe_command(int* command);

void rosserial_spinonce();

#ifdef __cplusplus
}
#endif

#endif /* ROSSERIAL_H */
