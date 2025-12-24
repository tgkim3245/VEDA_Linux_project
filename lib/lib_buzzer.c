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

// 멜로디 (주파수 Hz)
int melody[] = {
    659, 494, 523, 587, 523, 494, // 파트 1
    440, 440, 523, 659, 587, 523, // 파트 2
    494, 523, 587, 659,           // 파트 3
    523, 440, 440,                 // 파트 4
    0
};
// 리듬 (지연 시간 ms)
int rhythm[] = {
    400, 200, 200, 400, 200, 200, // 파트 1
    400, 200, 200, 400, 200, 200, // 파트 2
    600, 200, 400, 400,           // 파트 3
    400, 400, 400,                 // 파트 4
    10
};
void buzzer_musicPlay(int* musicRunning, int* kill_thread){
    int total_notes = sizeof(melody) / sizeof(int);

    // 0번 음부터 마지막 음까지 루프
    for (int i = 0; i < total_notes; i++) {
        
        // [중요] 음을 내기 직전에 '꺼짐' 상태인지 확인
        if (*musicRunning == 0 || *kill_thread) break;

        softToneWrite(BUZ_PIN, melody[i]);

        // [중요] delay 도중에도 '꺼짐'을 감지하기 위해 10ms 단위로 쪼개서 대기
        int waited = 0;
        while (waited < rhythm[i]) {
            if (*musicRunning == 0) {
                softToneWrite(BUZ_PIN, 0); // 즉시 소리 끔
                return; // 함수 종료 (인덱스 i 초기화 효과)
            }
            delay(10);
            waited += 10;
        }
        
        // 음 사이의 아주 짧은 간격
        softToneWrite(BUZ_PIN, 0);
        delay(10);
    }

    // 노래가 끝까지 연주되었거나 중간에 break로 빠져나왔을 때
    softToneWrite(BUZ_PIN, 0);
    *musicRunning = 0; // 상태를 '정지'로 변경
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