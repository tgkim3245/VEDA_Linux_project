#include "lib_buzzer.h"

void buzzer_init(){
    // wiringPiSetup(); 
    softToneCreate(BUZ_PIN);   /* 톤 출력을 위한 GPIO 설정*/
}

void buzzer_beep(){
    softToneWrite(BUZ_PIN, 523);
    delay(150);
    softToneWrite(BUZ_PIN, 0);
}

void buzzer_musicPlay(){
    // 테트리스 original bgm
    softToneWrite(BUZ_PIN, 659); delay(400); // 미
    softToneWrite(BUZ_PIN, 494); delay(200); // 시
    softToneWrite(BUZ_PIN, 523); delay(200); // 도
    softToneWrite(BUZ_PIN, 587); delay(400); // 레
    softToneWrite(BUZ_PIN, 523); delay(200); // 도
    softToneWrite(BUZ_PIN, 494); delay(200); // 시
    
    softToneWrite(BUZ_PIN, 440); delay(400); // 라
    softToneWrite(BUZ_PIN, 440); delay(200); // 라
    softToneWrite(BUZ_PIN, 523); delay(200); // 도
    softToneWrite(BUZ_PIN, 659); delay(400); // 미
    softToneWrite(BUZ_PIN, 587); delay(200); // 레
    softToneWrite(BUZ_PIN, 523); delay(200); // 도
    
    softToneWrite(BUZ_PIN, 494); delay(600); // 시
    softToneWrite(BUZ_PIN, 523); delay(200); // 도
    softToneWrite(BUZ_PIN, 587); delay(400); // 레
    softToneWrite(BUZ_PIN, 659); delay(400); // 미
    
    softToneWrite(BUZ_PIN, 523); delay(400); // 도
    softToneWrite(BUZ_PIN, 440); delay(400); // 라
    softToneWrite(BUZ_PIN, 440); delay(400); // 라
    
    softToneWrite(BUZ_PIN, 0);   // 정지
}
/*
int main( )
{
    wiringPiSetup( );
    buzzer_init();
    buzzer_beep();
    // buzzer_musicPlay();
    return 0;
}
*/