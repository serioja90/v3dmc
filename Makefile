all:
	cd ./lib; make
	gcc -Wall -o main.o main.c -lfigures -L lib/ -I include/