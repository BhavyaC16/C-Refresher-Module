CC:=gcc

default:
	make all
all:
	nasm -f elf64 add.s -o add.o
	$(CC) $(PWD)/prog-add.c add.o -o $(PWD)/prog-add
clean:
	rm $(PWD)/prog-add $(PWD)/add.o