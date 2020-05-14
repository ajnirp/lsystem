all: lsystem

lsystem: lsystem.cpp draw.h util.h types.h
	g++ draw.h util.h types.h lsystem.cpp -Wall -O3 -lGL -lGLU -lglut -o lsystem

clean:
	rm -f lsystem

.PHONY: all clean