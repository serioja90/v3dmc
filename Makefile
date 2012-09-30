all:
	cd ./lib; make
	export LD_LIBRARY_PATH="./lib"
	gcc -Wall -o main.o main.c -lfigures -L lib/ -I include/