#ifndef ROSSERIAL_H
#define ROSSERIAL_H

#ifdef __cplusplus
extern "C"
{
#endif

    void rosserial_setup();

    void rosserial_publish_base_params(volatile long int *ticks_L, volatile long int *ticks_R, float *desr_rpm_L, float *desr_rpm_R, float *curr_rpm_L, float *curr_rpm_R);

    // void rosserial_subscribe_teleop(float *duty_F, float *duty_B, float *duty_L, float *duty_R);

    void rosserial_subscribe_teleop(float *desr_rpm_F, float *desr_rpm_B, float *desr_rpm_L, float *desr_rpm_R);

    void rosserial_subscribe_rpm(float *rpm_L, float *rpm_R);

    void rosserial_subscribe_command(int *command);

#ifdef __cplusplus
}
#endif

#endif /* ROSSERIAL_H */
