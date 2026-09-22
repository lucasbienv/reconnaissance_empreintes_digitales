CFLAGS= -g -Wall -Wextra -fsanitize=address

main: *.c
	gcc ${CFLAGS} -o main *.c

clean:
	rm -f *.o *.exe
