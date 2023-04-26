
project1: user_interface.o database.o
	gcc -o project1 user_interface.o database.o

user_interface.o: database.c user_interface.c
	gcc -ansi -pedantic-errors -Wall -c user_interface.c
database.o: database.h
	gcc -ansi -pedantic-errors -Wall -c database.c

