CFLAGS=-std=c99 -pedantic -Wall -Wextra -Werror -Wwrite-strings

main: FileEncryption.c
	gcc $(CFLAGS) FileEncryption.c -o main
