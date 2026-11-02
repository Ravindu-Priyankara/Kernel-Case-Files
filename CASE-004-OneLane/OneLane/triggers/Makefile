all: trigger

trigger: trigger.c
	gcc -fsanitize=address,undefined -fno-omit-frame-pointer -g trigger.c -o trigger -lbpf

clean:
	rm -f trigger