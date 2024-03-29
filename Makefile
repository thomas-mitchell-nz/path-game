# File:   Makefile
# Author: M. P. Hayes, UCECE
# Date:   12 Sep 2010
# Descr:  Makefile for game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/navswitch.h ../../fonts/font3x5_1.h ../../utils/font.h ../../utils/pacer.h ../../utils/tinygl.h fsm.h kernel.h menustate.h playstate.h pathstate.h gameoverstate.h levelupstate.h
	$(CC) -c $(CFLAGS) $< -o $@

fsm.o: fsm.c fsm.h menustate.h pathstate.h playstate.h kernel.h types.h
	$(CC) -c $(CFLAGS) $< -o $@

kernel.o: kernel.c ../../drivers/avr/system.h ../../utils/pacer.h kernel.h
	$(CC) -c $(CFLAGS) $< -o $@

playstate.o: menustate.c ../../drivers/avr/system.h ../../drivers/navswitch.h ../../utils/tinygl.h menustate.h types.h fsm.h

pathstate.o: menustate.c ../../drivers/avr/system.h ../../drivers/navswitch.h ../../utils/tinygl.h pathstate.h types.h fsm.h

menustate.o: menustate.c ../../drivers/avr/system.h ../../drivers/navswitch.h ../../utils/tinygl.h playstate.h types.h fsm.h

gameoverstate.o: gameoverstate.c ../../drivers/avr/system.h ../../drivers/navswitch.h ../../utils/tinygl.h gameoverstate.h types.h fsm.h

levelupstate.o: levelupstate.c ../../drivers/avr/system.h ../../drivers/navswitch.h ../../utils/tinygl.h levelupstate.h types.h fsm.h

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@


# Link: create ELF output file from object files.
game.out: game.o pio.o system.o timer.o display.o ledmat.o navswitch.o font.o pacer.o tinygl.o kernel.o menustate.o fsm.o playstate.o pathstate.o gameoverstate.o levelupstate.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean:
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start
