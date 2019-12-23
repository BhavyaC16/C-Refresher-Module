default:
	make preprocess compile assemble link
all:
	gcc -Wall -save-temps hello.c -o hello
preprocess:
	gcc -Wall -E hello.c -o hello.i
compile:
	gcc -S hello.i -o hello.s
assemble:
	as hello.s -o hello.o
link:
	gcc -o hello hello.o
clean:
	rm hello hello.i hello.s hello.o