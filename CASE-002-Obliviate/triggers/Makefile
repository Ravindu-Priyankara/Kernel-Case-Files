all: get_hash decrypt_hash

get_hash: get_hash.c
	gcc -fsanitize=address -g get_hash.c -o get_hash

decrypt_hash: decrypt_hash.c
	gcc -fsanitize=address -g decrypt_hash.c -o decrypt_hash

clean:
	rm -f get_hash decrypt_hash