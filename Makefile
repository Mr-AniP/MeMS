# this is makefile for MeMS

all: clean example 

example: example.c mems.h memsyscall.h memsyscall.c freelist.c freelist.h mainimpl.c mainimpl.h
	gcc -o example example.c 

clean:
	rm -rf example