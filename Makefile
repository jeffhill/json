json: json.c json.h Makefile
	gcc -Wall -Werror -O2 -o json json.c test.c
