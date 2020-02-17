#include "ros.h"
#include "auto_nav/motor_msg.h"
#include "auto_nav/base_params_msg.h"
#include "rosserial.h"

ros::NodeHandle nh;

auto_nav::motor_msg rpm_from_teleop;
auto_nav::motor_msg rpm_from_autonav;
auto_nav::base_params_msg base_params;
ros::Publisher espPub_base_params("base_params", &base_params);

void callback_teleop(const auto_nav::motor_msg &msg)
{
	rpm_from_teleop.motor_L = msg.motor_L;
	rpm_from_teleop.motor_R = msg.motor_R;
	rpm_from_teleop.command = msg.command;
}
ros::Subscriber<auto_nav::motor_msg> espSub_teleop("teleop", &callback_teleop);

void callback_autonav(const auto_nav::motor_msg &msg)
{
	rpm_from_autonav.motor_L = msg.motor_L;
	rpm_from_autonav.motor_R = msg.motor_R;
}
ros::Subscriber<auto_nav::motor_msg> espSub_autonav("rpm", &callback_autonav);

void rosserial_setup()
{ // Initialize ROS
	nh.initNode();
	nh.advertise(espPub_base_params);
	nh.subscribe(espSub_teleop);
	nh.subscribe(espSub_autonav);
	rpm_from_teleop.motor_L = 0;
	rpm_from_teleop.motor_R = 0;
	rpm_from_teleop.command = 0;
	rpm_from_autonav.motor_L = 0;
	rpm_from_autonav.motor_R = 0;
}

void rosserial_publish_base_params(volatile long int *ticks_L, volatile long int *ticks_R, float *desr_rpm_L, float *desr_rpm_R, float *curr_rpm_L, float *curr_rpm_R)
{
	base_params.ticks_L = *ticks_L;
	base_params.ticks_R = *ticks_R * (-1);
	base_params.desr_rpm_L = *desr_rpm_L;
	base_params.desr_rpm_R = *desr_rpm_R;
	base_params.curr_rpm_L = *curr_rpm_L;
	base_params.curr_rpm_R = *curr_rpm_R;
	espPub_base_params.publish(&base_params);
	nh.spinOnce();
}

void rosserial_subscribe_teleop(float *desr_rpm_L, float *desr_rpm_R)
{
	*desr_rpm_L = rpm_from_teleop.motor_L;
	*desr_rpm_R = rpm_from_teleop.motor_R;
	nh.spinOnce();
}

void rosserial_subscribe_command(int *command)
{
	*command = rpm_from_teleop.command;
	nh.spinOnce();
}

void rosserial_subscribe_rpm(float *rpm_L, float *rpm_R)
{
	*rpm_L = rpm_from_autonav.motor_L;
	*rpm_R = rpm_from_autonav.motor_R;
	*rpm_R *= -1; //since the right motor moves forward with negative rpm
	nh.spinOnce();
}
