#include "ros.h"
#include "rosserial.h"
#include "auto_nav/tuning_msg.h"
#include "auto_nav/velocity_msg.h"

ros::NodeHandle nh;

auto_nav::tuning_msg tuna;
auto_nav::velocity_msg rpm;
ros::Publisher espPub("rpm", &rpm);

void callback(const auto_nav::tuning_msg& msg){
  tuna.Kp=msg.Kp;
  tuna.Kd=msg.Kd;
  tuna.Ki=msg.Ki;
}
ros::Subscriber<auto_nav::tuning_msg> espSub("tuning", &callback);

void rosserial_setup(){  // Initialize ROS
  nh.initNode();
  nh.advertise(espPub);
  nh.subscribe(espSub);
  tuna.Kp = 0;
  tuna.Kd = 0;
  tuna.Ki = 0;
}

void rosserial_publish(encoder_t* encoder_L, encoder_t* encoder_R){
  rpm.motor_L = encoder_L->curr_rpm;
  rpm.motor_R = encoder_R->curr_rpm;
  espPub.publish(&rpm);  // publish the msg
}

void rosserial_subscribe(motor_t* motor){
  motor->Kp = tuna.Kp;
  motor->Kd = tuna.Kd;
  motor->Ki = tuna.Ki;
  nh.spinOnce();
}

void rosserial_spinonce(){
  nh.spinOnce();
}
