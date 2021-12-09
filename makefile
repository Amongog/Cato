all:
	gcc -o Cato main.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
	./Cato
compile:
	gcc -o Cato main.c -Wall `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
