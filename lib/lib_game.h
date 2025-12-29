#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#define CDS_CH 0

typedef struct{
    int sd;
    int gameRunning;
    int* kill_thread;
    int speed;
    int number;
} st_game_data;

void game_init();

void game_play();


#endif