#ifndef ROSSERIAL_H
#define ROSSERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

void rosserial_setup();

void rosserial_publish(long long unsigned int* ticks_L, long long unsigned int* ticks_R);

void rosserial_subscribe(float* duty_L, float* duty_R);

void rosserial_spinonce();

#ifdef __cplusplus
}
#endif

#endif /* ROSSERIAL_H */
