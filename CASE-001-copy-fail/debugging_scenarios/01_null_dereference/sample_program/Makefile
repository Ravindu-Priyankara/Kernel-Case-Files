all: sample

sample: sample.c
	gcc -fsanitize=address,undefined -fno-omit-frame-pointer -g sample.c -o sample 

clean:
	rm -f sample