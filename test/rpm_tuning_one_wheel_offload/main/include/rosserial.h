#ifndef ROSSERIAL_H
#define ROSSERIAL_H
#include "motor.h"

#ifdef __cplusplus
extern "C" {
#endif

void rosserial_setup();

void rosserial_subscribe(motor_t* motor);

void rosserial_spinonce();

#ifdef __cplusplus
}
#endif

#endif /* ROSSERIAL_H */
