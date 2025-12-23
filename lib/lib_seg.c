#include "lib_seg.h"

int seg_pins[5] = {SEG_A, SEG_B, SEG_C, SEG_D, SEG_DP};

// 초기화
void seg_init(){
    // wiringPiSetup(); 
    pinMode(SEG_A, OUTPUT);
    pinMode(SEG_B, OUTPUT);
    pinMode(SEG_C, OUTPUT);
    pinMode(SEG_D, OUTPUT);
    pinMode(SEG_DP, OUTPUT);
    seg_off();
}

// 입력으로 숫자 넣으면 출력됨
void seg_display(int n){
    for (int i = 0; i < 4; i++) {
        digitalWrite(seg_pins[i], (n >> i) & 1);
    }
}

// 입력으로 dp 0(끄기)/1(켜기)
void seg_dp(int n){
    if(n) digitalWrite(SEG_DP, 0);
    else digitalWrite(SEG_DP, 1);
}

// 전부다 꺼짐
void seg_off(){
    seg_display(15);
    seg_dp(0);
}
/*
int main(){
    seg_init();
    delay(1000);
    int i = 0;
    while(1){
        seg_display((i++)%10);
        seg_dp(i%2);
        delay(1000);
    }
}
*/