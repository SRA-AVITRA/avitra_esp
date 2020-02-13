#ifndef ROSSERIAL_H
#define ROSSERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

void rosserial_setup();

void rosserial_publish(volatile int32_t* ticks_L, volatile int32_t* ticks_R, float* yaw);

void rosserial_subscribe_teleop(float* duty_F, float* duty_B, float* duty_L, float* duty_R);

void rosserial_subscribe_rpm(float* rpm_L, float* rpm_R);

void rosserial_subscribe_command(int* command);

#ifdef __cplusplus
}
#endif

#endif /* ROSSERIAL_H */
