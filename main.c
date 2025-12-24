#include <dlfcn.h>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    wiringPiSetup();
    void *handle;
    void (*init_lib)(void); // 함수 포인터 정의
    char *error;

    handle = dlopen("./lib/libsegControl.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }

    dlerror(); 
    init_lib = (void (*)(void))dlsym(handle, "seg_init");

    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        dlclose(handle);
        exit(EXIT_FAILURE);
    }

    init_lib();

    dlclose(handle);

    // seg_init();
    // led_init();

    // seg_off();
    // led_write(0, 0);
    // led_write(1, 0);
    // led_write(2, 0);
}