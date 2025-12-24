#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/select.h>
#include <pthread.h>
#include <dlfcn.h>
#include <wiringPi.h>
#include "lib_led.h"
#include "lib_buzzer.h"
#include "lib_cds.h"
#include "lib_seg.h"

#define BACKLOG 10
#define MAXDATASIZE 1000
char buf[MAXDATASIZE];
int MENU = 0;
typedef void* (* OP_FUNC) (void*);

void chatting(int sd);
void *thread_led(void *arg);
void *thread_buzzer(void *arg);
void *thread_cds(void *arg);
void *thread_seg(void *arg);

int main(void)
{
    wiringPiSetup(); 
    int sockfd, new_fd;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int sin_size;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // 소켓 옵션으로, 소켓이 죽었을때 TIME WAIT 을 거치지 않게함 
    int optval = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(60000);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&(server_addr.sin_zero), '\0', 8);

    if(bind(sockfd, (struct sockaddr *)&server_addr,
            sizeof(struct sockaddr))==-1) {
        perror("bind");
        exit(1);
    }
    if(listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }
    sin_size = sizeof(struct sockaddr_in);
    if((new_fd = accept(sockfd, (struct sockaddr *) &client_addr, &sin_size))== -1)  {
        perror("accept");
    }
    printf("입장함\n");
    chatting(new_fd);
    return 0;
}

void chatting(int sd){
    int kill_thread = 0;
    int running_thread = 0;

    st_led_data     led_data_set;
    st_buzzer_data  buzzer_data_set;
    st_cds_data     cds_data_set;
    st_seg_data     seg_data_set;

    // char buf[MAXDATASIZE];
    int status;
    pthread_t a_thread;
    void *thread_result;

    fd_set rfedet, rfedet_copy;
    FD_ZERO(&rfedet);
    FD_SET(0, &rfedet);
    FD_SET(sd, &rfedet);

    char* menu_list = 
        "\n********** 제어 메뉴 **********\n"
        "1. LED 밝기 제어\n"
        "2. 부저 노래 재생\n"
        "3. CDS 조도 센서 모니터링\n"
        "4. 세븐세그먼트 카운트다운\n"
        "5. 프로그램 종료\n"
        "********************************\n";
    send(sd, menu_list, strlen(menu_list), 0);

    while(1){
        rfedet_copy =  rfedet;
        select(sd + 1, &rfedet_copy, NULL, NULL, NULL); // 이벤트가 발생!
        if(FD_ISSET(0, &rfedet_copy)){
            fgets(buf, sizeof(buf), stdin);
            send(sd, buf, strlen(buf), 0);
        }
        else if(FD_ISSET(sd, &rfedet_copy)){
            int numbytes = recv(sd, buf, MAXDATASIZE - 1, 0);
            buf[numbytes-1] = '\0';

            if(strcmp(buf, "home")==0){
                if(running_thread) {
                    kill_thread = 1;
                    running_thread = 0;
                }
                MENU = 0;
                send(sd, menu_list, strlen(menu_list), 0);
                continue;
            }

            if(MENU == 0){  // 홈
                int menu = atoi(buf);
                if(menu<1 || menu > 5){
                    strcpy(buf,"메뉴를 잘못 입력했습니다... 1~5\n");
                    send(sd, buf, strlen(buf), 0);
                    send(sd, menu_list, strlen(menu_list), 0);
                    continue;
                }
                MENU = menu;

                if(menu == 1){
                    strcpy(buf, "\n기능1. LED 밝기 제어\n\n"
                                " (1) LED 최대 \n"
                                " (2) LED 중간 \n"
                                " (3) LED 최저 \n"
                                " (home) 홈으로 \n\n");
                    send(sd, buf, strlen(buf), 0);
                    led_data_set.sd = sd;
                    led_data_set.brightness = 0;
                    led_data_set.kill_thread = &kill_thread;
                    pthread_create(&a_thread, NULL, thread_led, &led_data_set);
                    pthread_detach(a_thread);
                    running_thread = 1;
                }
                else if(menu == 2){
                    strcpy(buf, "\n기능2. 부저 노래 재생\n\n"
                                " (1) 노래 play \n"
                                " (2) 노래 stop \n"
                                " (home) 홈으로 \n\n");
                    send(sd, buf, strlen(buf), 0);
                    buzzer_data_set.sd = sd;
                    buzzer_data_set.musicRunning = 0;
                    buzzer_data_set.kill_thread = &kill_thread;
                    pthread_create(&a_thread, NULL, thread_buzzer, &buzzer_data_set);
                    pthread_detach(a_thread);
                    running_thread = 1;
                }
                else if(menu == 3){
                    strcpy(buf, "\n기능3. CDS 조도 센서 모니터링\n\n"
                                " 밝기가 어두우면 LED가 ON됩니다.. \n\n"
                                " (home) 홈으로 \n\n");
                    send(sd, buf, strlen(buf), 0);
                    cds_data_set.sd = sd;
                    cds_data_set.kill_thread = &kill_thread;
                    pthread_create(&a_thread, NULL, thread_cds, &cds_data_set);
                    pthread_detach(a_thread);
                    running_thread = 1;
                }
                else if(menu == 4){
                    strcpy(buf,"숫자를 입력하면 카운트 다운 됩니다..\n");
                    strcpy(buf, "\n기능4. 세븐세그먼트 카운트다운\n\n"
                                " 숫자를 입력하면 카운트 다운 됩니다..\n\n"
                                " (home) 홈으로 \n\n");
                    send(sd, buf, strlen(buf), 0);
                    seg_data_set.sd = sd;
                    seg_data_set.start_num = 0;
                    seg_data_set.kill_thread = &kill_thread;
                    pthread_create(&a_thread, NULL, thread_seg, &seg_data_set);
                    pthread_detach(a_thread);
                    running_thread = 1;
                }
            }
            else if(MENU == 1){
                int brightness = atoi(buf);
                if(brightness == 1){
                    led_data_set.brightness = 255;
                    printf("led 밝기 최대(%d)로 변경\n",brightness);
                }
                else if(brightness == 2){
                    led_data_set.brightness = 180;
                    printf("led 밝기 중간(%d)으로 변경\n",brightness);
                }
                else if(brightness == 3){
                    led_data_set.brightness = 120;
                    printf("led 밝기 최저(%d)로 변경\n",brightness);
                }
                else{
                    strcpy(buf,"밝기는 ... 1.LED 최대 / 2. LED 중간 / 3. LED 최저\n");
                    send(led_data_set.sd, buf, strlen(buf), 0);
                }
            }
            else if(MENU == 2){
                int music_onoff = atoi(buf);
                if(music_onoff == 1){
                    buzzer_data_set.musicRunning = 1;
                    printf("노래 on\n");
                }
                else if(music_onoff == 2){
                    buzzer_data_set.musicRunning = 0;
                    printf("노래 off\n");
                }
                else{
                    strcpy(buf,"잘못 입력하였습니다...(1. 노래on / 2. 노래 off)\n");
                    send(buzzer_data_set.sd, buf, strlen(buf), 0);
                }
            }
            else if(MENU == 3){
                
            }
            else if(MENU == 4){
                int start_num = atoi(buf);
                if(1<=start_num && start_num<=9){
                    seg_data_set.start_num = start_num;
                    printf("카운트다운 시작\n");
                }
                else{
                    strcpy(buf,"잘못 입력하였습니다...(시작 숫자는 1~9)\n");
                    send(seg_data_set.sd, buf, strlen(buf), 0);
                }
            }

            // printf("클라이언트>> %s\n", buf);
        }
    }
}


void *thread_led(void *arg)
{
    OP_FUNC ledControl;
    void *handle=dlopen("./lib/libledControl.so", RTLD_LAZY);
    if(handle==NULL) {
        printf("%s\n", dlerror());
        exit(1);
    }
    ledControl = (OP_FUNC)dlsym(handle, "ledControl");
    ledControl(arg);
    dlclose(handle);
    pthread_exit(NULL);
}
void *thread_buzzer(void *arg)
{
    OP_FUNC buzzerControl;
    void *handle=dlopen("./lib/libbuzzerControl.so", RTLD_LAZY);
    if(handle==NULL) {
        printf("%s\n", dlerror());
        exit(1);
    }
    buzzerControl = (OP_FUNC)dlsym(handle, "buzzerControl");
    buzzerControl(arg);
    dlclose(handle);
    pthread_exit(NULL);
}
void *thread_cds(void *arg)
{
    OP_FUNC cdsControl;
    void *handle=dlopen("./lib/libcdsControl.so", RTLD_LAZY);
    if(handle==NULL) {
        printf("%s\n", dlerror());
        exit(1);
    }
    cdsControl = (OP_FUNC)dlsym(handle, "cdsControl");
    cdsControl(arg);
    dlclose(handle);
    pthread_exit(NULL);
}
void *thread_seg(void *arg)
{
    OP_FUNC segControl;
    void *handle=dlopen("./lib/libsegControl.so", RTLD_LAZY);
    if(handle==NULL) {
        printf("%s\n", dlerror());
        exit(1);
    }
    segControl = (OP_FUNC)dlsym(handle, "segControl");
    segControl(arg);
    dlclose(handle);
    pthread_exit(NULL);
}
