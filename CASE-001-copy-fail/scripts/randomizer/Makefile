all: randomizer

randomizer: key_randomizer.c
	gcc -fsanitize=address -g key_randomizer.c -o key_randomizer

clean:
	rm -f key_randomizer