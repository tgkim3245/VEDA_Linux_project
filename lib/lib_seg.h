#ifndef SEG_H
#define SEG_H

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#define SEG_A 21
#define SEG_B 22
#define SEG_C 23
#define SEG_D 24
#define SEG_DP 25

// 초기화
void seg_init();

// 입력으로 숫자 넣으면 출력됨
void seg_display(int n);

// 입력으로 dp 0(끄기)/1(켜기)
void seg_dp(int n);

// 전부다 끄기
void seg_off();


#endif