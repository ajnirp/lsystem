all: lsystem

lsystem: main.cpp util.h systems.h
	g++ util.h systems.h main.cpp -Wall -O3 -lGL -lGLU -lglut -o lsystem

clean:
	rm -f lsystem

.PHONY: all clean