all: main.c
	gcc -Wall -O2 -std=c99 -std=gnu99 -std=gnu11 -c gpio/serial.c -o serial.o
	gcc -Wall -O2 -std=c99 -std=gnu99 -std=gnu11 -c main.c -o main.o
	g++ -o gpioSerial serial.o main.o -s   
	rm serial.o main.o

