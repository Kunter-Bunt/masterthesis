CC = xtensa-lx106-elf-gcc
CFLAGS = -I. -mlongcalls
LDLIBS = -nostdlib -Wl,--start-group -lmain -lnet80211 -lwpa -llwip -lpp -lphy -lc -Wl,--end-group -lgcc
LDFLAGS = -Teagle.app.v6.ld

probeReq-0x00000.bin: probeReq
	esptool.py elf2image $^

probeReq: probeReq.o

probeReq.o: probeReq.c

flash: probeReq-0x00000.bin
	esptool.py write_flash 0 probeReq-0x00000.bin 0x10000 probeReq-0x10000.bin

clean:
	rm -f probeReq probeReq.o probeReq-0x00000.bin probeReq-0x10000.bin
