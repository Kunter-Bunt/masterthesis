#!/bin/bash

cd blinky/
make
cd ..
esptool.py elf2image blinky/blinky
esptool.py -p /dev/ttyUSB0 write_flash 0x00000 blinky/blinky-0x00000.bin 0x10000 blinky/blinky-0x10000.bin
