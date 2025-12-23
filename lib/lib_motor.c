#include "lib_motor.h"

// 1 이미터, 2 콜렉터, 3 베이스(220옴)
void motor_init(){
    // wiringPiSetup(); 
    pinMode(MOTER_PIN, OUTPUT);
    softPwmCreate(MOTER_PIN, 0, 255);
    motor_speed(255);
}

void motor_speed(int speed){
    if(speed<0) speed = 0;
    else if (speed>255) speed = 255;
    softPwmWrite(MOTER_PIN, 255-speed);
}
/*
int main(){
    wiringPiSetup( ); 
    motor_init();
    for(int i = 0; i<255; i++){
        motor_speed(i);
        delay(20);
    }
    for(int i=255; i>=0; i--){
        motor_speed(i);
        delay(20);
    }
    motor_speed(0);
}
*/