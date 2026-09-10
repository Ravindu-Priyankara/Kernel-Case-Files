all: socket_caller bind setkey authsize

socket_caller: socket_caller.c
	gcc -fsanitize=address -g socket_caller.c -o socket_caller

bind: bind_caller.c 
	gcc -fsanitize=address -g bind_caller.c -o bind_caller

setkey: setkey.c 
	gcc -fsanitize=address,undefined -fno-omit-frame-pointer -g setkey.c -o setkey

authsize: authsize.c
	gcc -fsanitize=address,undefined -fno-omit-frame-pointer -g authsize.c -o authsize

clean:
	rm -f socket_caller bind_caller setkey authsize