all: expl

exp: exploit.c 
	gcc -fsanitize=address -g exploit.c -o exploit

clean:
	rm -f exploit