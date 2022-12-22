CC=avr-gcc
CFLAGS=-mmcu=atmega2560 -Os -Wall -Wextra

SOURCES=led.c uart.c
TARGETS=$(SOURCES:.c=.hex)

OBJCOPY=avr-objcopy
OBJCOPY_FLAGS=-j .text -j .data -O ihex -R .eeprom

all: $(TARGETS)

%.hex: %.c
	$(CC) $(CFLAGS) -o $(<:.c=.elf) $<
	$(OBJCOPY) $(OBJCOPY_FLAGS) $(<:.c=.elf) $@

.PHONT: clean
clean:
	rm -rf *.hex *.elf
