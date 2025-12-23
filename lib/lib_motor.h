#ifndef MOTOR_H
#define MOTOR_H

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define MOTER_PIN 26

void motor_init();

void motor_speed(int speed);


#endif