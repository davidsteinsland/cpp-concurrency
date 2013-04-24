
all:
	g++ -g -Wall -ansi *.cpp -mthreads -o concurrent.exe

linux:
	g++ -g -Wall -ansi *.cpp -pthread -o concurrent