CC = xtensa-lx106-elf-gcc
CFLAGS = -I. -DICACHE_FLASH -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -lc -Wl,--end-group -lgcc
LDFLAGS = -Teagle.app.v6.ld

naiveTag-0x00000.bin: naiveTag
	esptool.py elf2image $^

naiveTag: naiveTag.o

naiveTag.o: naiveTag.c

flash: naiveTag-0x00000.bin
	esptool.py --baud 921600 write_flash 0 naiveTag-0x00000.bin 0x10000 naiveTag-0x10000.bin

clean:
	rm -f naiveTag naiveTag.o naiveTag-0x00000.bin naiveTag-0x10000.bin
