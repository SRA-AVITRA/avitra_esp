#ifndef ROSSERIAL_H
#define ROSSERIAL_H
#include "motor.h"

#ifdef __cplusplus
extern "C" {
#endif

void rosserial_setup();

void rosserial_publish(encoder_t* encoder_L, encoder_t* encoder_R);

void rosserial_subscribe(motor_t* motor_L, motor_t* motor_R);

void rosserial_spinonce();

#ifdef __cplusplus
}
#endif

#endif /* ROSSERIAL_H */
