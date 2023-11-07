# this is makefile for MeMS

all: clean example run

example: example.c mems.h
	gcc -o example example.c 
clean:
	rm -rf example
run:
	./example
