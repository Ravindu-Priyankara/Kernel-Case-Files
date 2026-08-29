all: socket_caller

socket_caller: socket_caller.c
	gcc -fsanitize=address -g socket_caller.c -o socket_caller

clean:
	rm -f socket_caller