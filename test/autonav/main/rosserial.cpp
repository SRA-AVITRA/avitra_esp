#include "ros.h"
#include "auto_nav/ticks_msg.h"
#include "auto_nav/velocity_msg.h"
#include "geometry_msgs/Twist.h"
#include "rosserial.h"

#define bot_radius 0.475/2
#define wheel_radius 0.154/2
#define pi 3.14159265358

ros::NodeHandle nh;

auto_nav::ticks_msg ticks;
auto_nav::velocity_msg velocity;
geometry_msgs::Twist twist;
ros::Publisher espPub("ticks", &ticks);

void callback_teleop(const auto_nav::velocity_msg& msg){
  velocity.motor_F = msg.motor_F;
  velocity.motor_B = msg.motor_B;
  velocity.motor_L = msg.motor_L;
  velocity.motor_R = msg.motor_R;
  velocity.command = msg.command;
}

ros::Subscriber<auto_nav::velocity_msg> espSub_teleop("teleop", &callback_teleop);

void callback_twist(const geometry_msgs::Twist& msg){
  twist.angular.z = msg.angular.z;
  twist.linear.x = msg.linear.x;
}

ros::Subscriber<geometry_msgs::Twist> espSub_rpm("cmd_vel", &callback_twist);

void rosserial_setup(){  // Initialize ROS
  nh.initNode();
  nh.advertise(espPub);
  nh.subscribe(espSub_teleop);
  nh.subscribe(espSub_rpm);
  velocity.motor_F = 0;
  velocity.motor_B = 0;
  velocity.motor_L = 0;
  velocity.motor_R = 0;
  velocity.command = 0;
  twist.angular.z = 0;
  twist.linear.x = 0;
}

void rosserial_publish(volatile long int* ticks_L, volatile long int* ticks_R){
  ticks.motor_L = *ticks_L;
  ticks.motor_R = *ticks_R;
  ticks.motor_R *= -1;    //since the right motor moves forward in negative rpm, negative ticks are published
  espPub.publish(&ticks);  // publish the msg
}

void rosserial_subscribe_teleop(float* duty_F, float* duty_B, float* duty_L, float* duty_R){
  *duty_F = velocity.motor_F;
  *duty_B = velocity.motor_B;
  *duty_L = velocity.motor_L;
  *duty_R = velocity.motor_R;
  nh.spinOnce();
}

void rosserial_subscribe_command(int* command){
  *command = velocity.command;
  nh.spinOnce();
}

void rosserial_subscribe_rpm(float* rpm_L, float* rpm_R){
  float vel_L = twist.linear.x - bot_radius * twist.angular.z;
  float vel_R = twist.linear.x + bot_radius * twist.angular.z;
  
  *rpm_L = vel_L * 60 / (2 * pi * wheel_radius);
  *rpm_R = vel_R * 60 / (2 * pi * wheel_radius);
  *rpm_R *= -1;   //since the right motor moves forward with negative rpm
  nh.spinOnce();
}

void rosserial_spinonce(){
  nh.spinOnce();
}
