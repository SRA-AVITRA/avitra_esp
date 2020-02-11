#include "ros.h"
#include "auto_nav/velocity_msg.h"
#include "auto_nav/base_params_msg.h"
#include "rosserial.h"

ros::NodeHandle nh;

auto_nav::velocity_msg velocity;
auto_nav::velocity_msg rpm;
auto_nav::base_params_msg base_params;
ros::Publisher espPub_base_params("base_params", &base_params);

void callback_teleop(const auto_nav::velocity_msg &msg)
{
	// velocity.motor_F = msg.motor_F;
	// velocity.motor_B = msg.motor_B;
	// velocity.motor_L = msg.motor_L;
	// velocity.motor_R = msg.motor_R;
	rpm.motor_F = msg.motor_F;
	rpm.motor_B = msg.motor_B;
	rpm.motor_L = msg.motor_L;
	rpm.motor_R = msg.motor_R;
	velocity.command = msg.command;
}
ros::Subscriber<auto_nav::velocity_msg> espSub_teleop("teleop", &callback_teleop);

void callback_rpm(const auto_nav::velocity_msg &msg)
{
	rpm.motor_L = msg.motor_L;
	rpm.motor_R = msg.motor_R;
}
ros::Subscriber<auto_nav::velocity_msg> espSub_rpm("rpm", &callback_rpm);

void rosserial_setup()
{ // Initialize ROS
	nh.initNode();
	nh.advertise(espPub_base_params);
	nh.subscribe(espSub_teleop);
	nh.subscribe(espSub_rpm);
	velocity.motor_F = 0;
	velocity.motor_B = 0;
	velocity.motor_L = 0;
	velocity.motor_R = 0;
	velocity.command = 0;
	rpm.motor_L = 0;
	rpm.motor_R = 0;
}

void rosserial_publish_base_params(volatile long int *ticks_L, volatile long int *ticks_R, float *desr_rpm_L, float *desr_rpm_R, float *curr_rpm_L, float *curr_rpm_R)
{
	base_params.ticks_L = *ticks_L;
	base_params.ticks_R = *ticks_R;
	base_params.desr_rpm_L = *desr_rpm_L;
	base_params.desr_rpm_R = *desr_rpm_R;
	base_params.curr_rpm_L = *curr_rpm_L;
	base_params.curr_rpm_R = *curr_rpm_R;
	espPub_base_params.publish(&base_params);
	nh.spinOnce();
}

void rosserial_subscribe_teleop(float *desr_rpm_F, float *desr_rpm_B, float *desr_rpm_L, float *desr_rpm_R)
{
	// *duty_F = velocity.motor_F;
	// *duty_B = velocity.motor_B;
	// *duty_L = velocity.motor_L;
	// *duty_R = velocity.motor_R;
	*desr_rpm_F = rpm.motor_F;
	*desr_rpm_B = rpm.motor_B;
	*desr_rpm_L = rpm.motor_L;
	*desr_rpm_R = rpm.motor_R;

	nh.spinOnce();
}

void rosserial_subscribe_command(int *command)
{
	*command = velocity.command;
	nh.spinOnce();
}

void rosserial_subscribe_rpm(float *rpm_L, float *rpm_R)
{
	*rpm_L = rpm.motor_L;
	*rpm_R = rpm.motor_R;
	*rpm_R *= -1; //since the right motor moves forward with negative rpm
	nh.spinOnce();
}
