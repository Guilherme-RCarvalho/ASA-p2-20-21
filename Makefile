# Makefile


CC   = g++
CFLAGS =  -std=c++11 -O3 -Wall -g
LDFLAGS= -lm

.PHONY: all clean


all: comp

comp: p2.cpp
	$(CC) $(CFLAGS) -o proj $?

comp1: p2_cp-algorithms.cpp
	$(CC) $(CFLAGS) -o copy $?

run: comp
	./proj

runV: comp1
	valgrind -s --track-origins=yes ./copy < input2.in

test: comp
	./proj < input.txt

generate: generate.cpp
	$(CC) $(CFLAGS) -o generate $?

clean:
	@echo Cleaning...
	rm -f proj
