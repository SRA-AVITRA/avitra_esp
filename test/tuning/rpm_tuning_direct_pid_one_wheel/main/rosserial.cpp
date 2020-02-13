#include "ros.h"
#include "rosserial.h"
#include "auto_nav/tuning_msg.h"
#include "auto_nav/velocity_msg.h"
#include "auto_nav/pid_response.h"

ros::NodeHandle nh;

auto_nav::tuning_msg tuna;
auto_nav::pid_response pr;
auto_nav::velocity_msg desr_rpm;
ros::Publisher espPub("pid_response", &pr);

void tuning_callback(const auto_nav::tuning_msg& msg){
  tuna.Kp = msg.Kp;
  tuna.Kd = msg.Kd;
  tuna.Ki = msg.Ki;
}

ros::Subscriber<auto_nav::tuning_msg> espSub_tuning("tuning", &tuning_callback);

void desr_rpm_callback(const auto_nav::velocity_msg& msg){
  desr_rpm.motor_L = msg.motor_L;
}

ros::Subscriber<auto_nav::velocity_msg> espSub_desr_rpm("desr_rpm", &desr_rpm_callback);

void rosserial_setup()
{
  nh.initNode();
  nh.advertise(espPub);
  nh.subscribe(espSub_tuning);
  nh.subscribe(espSub_desr_rpm);
  tuna.Kp = 0;
  tuna.Kd = 0;
  tuna.Ki = 0;
  tuna.alpha = 0;
  tuna.iTerm_limit = 0;
}

void rosserial_publish(motor_t* motor_L)
{
  pr.curr_rpm = motor_L->encoder.curr_rpm;
  pr.duty_cycle = motor_L->duty_cycle;
  pr.desr_rpm = motor_L->desr_rpm;
  pr.err = motor_L->err;
  pr.pTerm = motor_L->pTerm;
  pr.dTerm = motor_L->dTerm;
  pr.iTerm = motor_L->iTerm;
  espPub.publish(&pr);
}

void rosserial_subscribe(motor_t* motor_L){
  motor_L->desr_rpm = desr_rpm.motor_L;
  motor_L->Kp = tuna.Kp;
  motor_L->Kd = tuna.Kd;
  motor_L->Ki = tuna.Ki;
  nh.spinOnce();
}

void rosserial_spinonce(){
  nh.spinOnce();
}
