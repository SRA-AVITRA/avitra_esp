#ifndef ROSSERIAL_H
#define ROSSERIAL_H

#ifdef __cplusplus
extern "C" {
#endif

void rosserial_setup();

void rosserial_publish(float* op);

#ifdef __cplusplus
}
#endif

#endif /* ROSSERIAL_H */
