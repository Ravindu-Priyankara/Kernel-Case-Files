all: socket_caller bind

socket_caller: socket_caller.c
	gcc -fsanitize=address -g socket_caller.c -o socket_caller

bind: bind_caller.c 
	gcc -fsanitize=address -g bind_caller.c -o bind_caller

clean:
	rm -f socket_caller bind_caller