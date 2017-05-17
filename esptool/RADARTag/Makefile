CC = xtensa-lx106-elf-gcc
CFLAGS = -I. -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -lc -Wl,--end-group -lgcc
LDFLAGS = -Teagle.app.v6.ld

RADARTag-0x00000.bin: RADARTag
	esptool.py elf2image $^

RADARTag: RADARTag.o

RADARTag.o: RADARTag.c

flash: RADARTag-0x00000.bin
	esptool.py --baud 921600 write_flash 0 RADARTag-0x00000.bin 0x10000 RADARTag-0x10000.bin

clean:
	rm -f RADARTag RADARTag.o RADARTag-0x00000.bin RADARTag-0x10000.bin
