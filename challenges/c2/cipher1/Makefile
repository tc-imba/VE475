all: main.cpp byte.cpp aes.c
	gcc -c aes.c
	g++ -std=c++11 -o c2 main.cpp byte.cpp aes.o

clean:
	rm -f c2 *.o
