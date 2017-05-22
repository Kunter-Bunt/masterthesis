CC = xtensa-lx106-elf-gcc
CFLAGS = -I. -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -lc -Wl,--end-group -lgcc
LDFLAGS = -Teagle.app.v6.ld

WiFiLLSTag-0x00000.bin: WiFiLLSTag
	esptool.py elf2image $^

WiFiLLSTag: WiFiLLSTag.o

WiFiLLSTag.o: WiFiLLSTag.c

flash: WiFiLLSTag-0x00000.bin
	esptool.py --baud 921600 write_flash 0 WiFiLLSTag-0x00000.bin 0x10000 WiFiLLSTag-0x10000.bin

clean:
	rm -f WiFiLLSTag WiFiLLSTag.o WiFiLLSTag-0x00000.bin WiFiLLSTag-0x10000.bin
