all: lsystem

lsystem: lsystem.cpp
	g++ lsystem.cpp -Wall -O3 -lGL -lGLU -lglut -o lsystem

clean:
	rm -f lsystem

.PHONY: all clean