#include "lib_game.h"
#include "lib_cds.h"
#include "lib_led.h"
#include "lib_buzzer.h"
#include "lib_seg.h"
#include "Lib_motor.h"
#include <stdlib.h>
#include <time.h>

void game_init(void* arg){
    st_game_data* data = (st_game_data*)arg;

    led_init();
    buzzer_init();
    seg_init();
    cds_init();
    motor_init();

    srand(time(NULL));
    data->gameRunning = 1;
    data->momentum = rand() % 500 + 500; 
    data->number = 0;
}

void game_play(void* arg){
    st_game_data* data = (st_game_data*)arg;

    if( *(data->kill_thread) == 1)   return;
    // 1. 회전 에너지가 다 떨어지면 종료
    if (data->momentum <= 0) {
        data->gameRunning = 0;
        motor_speed(0);
        buzzer_beep(); // 멈출 때 삑!
        return 0;
    }

    // 2. CDS 읽기 (브레이크 강도 결정)
    int cds_val = cds_read(); // 어두우면 255 근처, 밝으면 0 근처

    // 3. 마찰력(Decay) 계산
    // 자연 마찰(기본 2) + CDS 브레이크(가릴수록 마찰 증가)
    // 255(최대)일 때 약 10 정도의 마찰을 더 줌
    float friction = 2.0 + (cds_val / 25.0); 
    data->momentum -= friction;

    // 4. 숫자가 넘어가는 속도(Delay) 결정 (핵심!)
    // 에너지가 많으면 딜레이가 짧고(빠름), 에너지가 없으면 딜레이가 김(느림)
    // 최소 20ms에서 에너지가 0에 가까워질수록 길어짐
    int dynamic_delay = 20 + (1000 - data->momentum) / 5;
    if (dynamic_delay > 500) dynamic_delay = 500; // 최대 0.5초까지

    // 5. 모터 속도 제어 (회전 에너지와 비례하도록)
    int m_speed = (data->momentum / 4); // 1000일 때 최대 250
    if (m_speed > 255) m_speed = 255;
    motor_speed(m_speed);

    // 6. 세그먼트 출력 및 업데이트
    data->number = (data->number + 1) % 10;
    seg_display(data->number);

    // 가변 딜레이 적용
    delay(dynamic_delay);
}
