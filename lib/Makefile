CC = gcc
CFLAGS = -fPIC -MMD -MP  # -MMD: .d 파일 생성, -MP: 헤더 삭제 시 오류 방지
LDFLAGS = -shared -Wl,--no-as-needed -lwiringPi

# 각 라이브러리별 오브젝트 구성 정의
BUZZER_OBJS = lib_buzzerControl.o lib_buzzer.o
CDS_OBJS    = lib_cdsControl.o lib_cds.o lib_led.o
LED_OBJS    = lib_ledControl.o lib_led.o
SEG_OBJS    = lib_segControl.o lib_seg.o

# 전체 오브젝트 및 의존성 파일 목록
ALL_OBJS = $(BUZZER_OBJS) $(CDS_OBJS) $(LED_OBJS) $(SEG_OBJS)
DEPS = $(ALL_OBJS:.o=.d)

TARGETS = libbuzzerControl.so libcdsControl.so libledControl.so libsegControl.so

all: $(TARGETS)

libbuzzerControl.so : $(BUZZER_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

libcdsControl.so : $(CDS_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

libledControl.so : $(LED_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

libsegControl.so : $(SEG_OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

# 패턴 규칙: .c를 .o로 컴파일
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.d $(TARGETS)

# 생성된 .d 파일을 포함시켜 헤더 의존성 적용
-include $(DEPS)

.PHONY: all clean