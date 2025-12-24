#ifndef LED_H
#define LED_H


#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

#define LED_RED_IDX 0
#define LED_GREEN_IDX 1
#define LED_YELLOW_IDX 2

#define LED_RED_PIN 27
#define LED_GREEN_PIN 28
#define LED_YELLOW_PIN 29

typedef struct{
    int sd;
    int brightness;
    int* kill_thread;
} st_led_data;

void led_init();

void led_pwm(char color, int duty);

void led_write(char color, int state);

#endif