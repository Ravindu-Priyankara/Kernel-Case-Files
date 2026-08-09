all:
	nasm -f elf64 reconstructed_payload.asm	-o payload.o
	ld payload.o -o reconstructed_payload 
	strip --strip-all reconstructed_payload

clean:
	rm -f reconstructed_payload reconstructed_payload.o
