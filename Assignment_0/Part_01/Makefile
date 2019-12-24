CC:=gcc

default:
	make preprocess compile assemble link
all:
	$(CC) -Wall -save-temps $(PWD)/hello.c -o $(PWD)/hello
preprocess:
	$(CC) -Wall -E $(PWD)/hello.c -o $(PWD)/hello.i
compile:
	$(CC) -Wall -S $(PWD)/hello.i -o $(PWD)/hello.s
assemble:
	$(CC) -Wall -c $(PWD)/hello.s -o $(PWD)/hello.o
link:
	$(CC) -Wall -o $(PWD)/hello $(PWD)/hello.o
clean:
	rm hello hello.i hello.s hello.o