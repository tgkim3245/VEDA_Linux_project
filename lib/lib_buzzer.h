#ifndef BUZZER_H
#define BUZZER_H

#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>

#define BUZ_PIN    6

typedef struct{
    int sd;
    int musicRunning;
    int* kill_thread;
} st_buzzer_data;

void buzzer_init();

void buzzer_beep();

void buzzer_musicPlay();


#endif