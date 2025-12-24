CC = gcc
CFLAGS = -fPIC -lwiringPi
LDFLAGS = -shared

TARGET = libbuzzerControl.so libcdsControl.so libledControl.so libsegControl.so


all: $(TARGET)

libbuzzerControl.so : lib_buzzerControl.o lib_buzzer.o
	$(CC) $(LDFLAGS) -o $@ $^

libcdsControl.so : lib_cdsControl.o lib_cds.o
	$(CC) $(LDFLAGS) -o $@ $^

libledControl.so : lib_ledControl.o lib_led.o
	$(CC) $(LDFLAGS) -o $@ $^

libsegControl.so : lib_segControl.o lib_seg.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)

.PHONY: all clean
