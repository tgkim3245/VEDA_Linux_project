# 1. 컴파일러 및 플래그 설정
CC = gcc
CFLAGS = -Wall -g -I./lib
# -ldl: dlopen 등 동적 라이브러리 함수 사용을 위함
# -lwiringPi: 하드웨어 제어
# -lpthread: 멀티스레드 사용
LDFLAGS = -lwiringPi -lpthread -ldl

# 2. 경로 및 대상 정의
LIB_DIR = lib
SERVER_TARGET = server
CLIENT_TARGET = client

# 3. 기본 빌드 규칙 (전체 빌드)
all: build_libs $(SERVER_TARGET) $(CLIENT_TARGET)

# 4. 하위 디렉토리(lib)의 Makefile 호출
build_libs:
	@echo "--- [1/3] 하위 라이브러리 빌드 시작 ---"
	$(MAKE) -C $(LIB_DIR)
	@echo "--- 하위 라이브러리 빌드 완료 ---"

# 5. 서버 빌드
$(SERVER_TARGET): server.c
	@echo "--- [2/3] 서버 컴파일 시작 ---"
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 6. 클라이언트 빌드
$(CLIENT_TARGET): client.c
	@echo "--- [3/3] 클라이언트 컴파일 시작 ---"
	$(CC) $(CFLAGS) -o $@ $^

# 7. 정리 규칙
clean:
	@echo "--- 전체 정리 시작 ---"
	$(MAKE) -C $(LIB_DIR) clean
	rm -f $(SERVER_TARGET) $(CLIENT_TARGET)
	@echo "--- 전체 정리 완료 ---"

.PHONY: all build_libs clean