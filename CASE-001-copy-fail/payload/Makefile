all:
	nasm -f elf64 reconstructed_payload.asm	-o payload.o
	ld payload.o -o payload 
	strip --strip-all payload

clean:
	rm -f payload payload.o