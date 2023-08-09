
DEVICE = atmega328p
FILE = main
PROGRAMMER = arduino
PORT = /dev/ttyUSB0
BAUD = 19200
LFUSE = 0xFF

default: compile size upload clean

compile:
	avr-gcc -Wall -mmcu=$(DEVICE) -Os $(FILE).c -o $(FILE).elf
	avr-objcopy -j .text -j .data -O ihex $(FILE).elf $(FILE).hex

size: 
	avr-size --format=avr --mcu=$(DEVICE) $(FILE).elf

upload:
	avrdude -v -C /etc/avrdude.conf -c $(PROGRAMMER) -P $(PORT) -p $(DEVICE) -b $(BAUD) -U flash:w:$(FILE).hex:i

clean:
	rm $(FILE).hex
	rm $(FILE).elf
