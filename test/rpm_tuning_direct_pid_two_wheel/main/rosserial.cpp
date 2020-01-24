#include "ros.h"
#include "rosserial.h"
#include "auto_nav/base_params_msg.h"
#include "auto_nav/velocity_msg.h"
#include "auto_nav/tuning_msg.h"

ros::NodeHandle nh;

auto_nav::base_params_msg base_params;
auto_nav::velocity_msg desr_rpm;
auto_nav::tuning_msg tuning;
ros::Publisher espPub("base_params", &base_params);

void desr_rpm_callback(const auto_nav::velocity_msg &msg)
{
	desr_rpm.motor_L = msg.motor_L;
	desr_rpm.motor_R = msg.motor_R;
}

ros::Subscriber<auto_nav::velocity_msg> espSub_desr_rpm("desr_rpm", &desr_rpm_callback);

void tuning_callback(const auto_nav::tuning_msg &msg)
{
	tuning.Kp = msg.Kp;
	tuning.Kd = msg.Kd;
	tuning.Ki = msg.Ki;
	tuning.alpha = msg.alpha;
	tuning.iTerm_limit = msg.iTerm_limit;
}

ros::Subscriber<auto_nav::tuning_msg> espSub_tuning("tuning", &tuning_callback);

void rosserial_setup()
{
	nh.initNode();
	nh.advertise(espPub);
	nh.subscribe(espSub_desr_rpm);
	nh.subscribe(espSub_tuning);
	desr_rpm.motor_L = 0;
	desr_rpm.motor_R = 0;
	tuning.Kp = 0;
	tuning.Kd = 0;
	tuning.Ki = 0;
	tuning.alpha = 0;
	tuning.iTerm_limit = 0;
}

void rosserial_publish(float *duty_cycle_L, float *duty_cycle_R, float *desr_rpm_L, float *desr_rpm_R, float *curr_rpm_L, float *curr_rpm_R)
{
	base_params.duty_cycle_L = *duty_cycle_L;
	base_params.duty_cycle_R = *duty_cycle_R;
	base_params.desr_rpm_L = *desr_rpm_L;
	base_params.desr_rpm_R = *desr_rpm_R;
	base_params.curr_rpm_L = *curr_rpm_L;
	base_params.curr_rpm_R = *curr_rpm_R;
	espPub.publish(&base_params);
}

void rosserial_subscribe(motor_t *motor_L, motor_t *motor_R)
{
	motor_L->desr_rpm = desr_rpm.motor_L;
	motor_L->Kp = tuning.Kp;
	motor_L->Kd = tuning.Kd;
	motor_L->Ki = tuning.Ki;
	motor_L->alpha = tuning.alpha;
	motor_L->iTerm_limit = tuning.iTerm_limit;
	motor_R->desr_rpm = desr_rpm.motor_R;
	motor_R->Kp = tuning.Kp;
	motor_R->Kd = tuning.Kd;
	motor_R->Ki = tuning.Ki;
	motor_R->alpha = tuning.alpha;
	motor_R->iTerm_limit = tuning.iTerm_limit;
	nh.spinOnce();
}
