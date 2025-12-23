#ifndef BUZZER_H
#define BUZZER_H

#include <stdio.h>
#include <wiringPi.h>
#include <softTone.h>

#define BUZ_PIN    6   /* GPIO25 */

void buzzer_init();

void buzzer_beep();

void buzzer_musicPlay();


#endif