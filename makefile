FILENAME=main
FILENAME2=atmega328P_LCD
FILENAME3=atmega328P_HC_SR04
PORT=COM7
PROGRAMMER=arduino
BAUD=115200
COMPILE=avr-gcc -Wall -Os -mmcu=$(DEVICE)
DEVICE=atmega328p


default:compile upload clean

compile:
	$(COMPILE) -c $(FILENAME).c -o $(FILENAME).o
	$(COMPILE) -c $(FILENAME2).c -o $(FILENAME2).o
	$(COMPILE) -c $(FILENAME3).c -o $(FILENAME3).o 
	$(COMPILE) -o $(FILENAME).elf $(FILENAME).o $(FILENAME2).o $(FILENAME3).o

	avr-objcopy -j .text -j .data -O ihex $(FILENAME).elf $(FILENAME).hex

upload:
	avrdude -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b$(BAUD) -U flash:w:$(FILENAME).hex:i

clean:
	rm $(FILENAME).o
	rm $(FILENAME2).o
	rm $(FILENAME).elf
	rm $(FILENAME).hex