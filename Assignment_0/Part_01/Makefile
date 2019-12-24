CC:=gcc
LIB_PATH:=-pthread

default:
	make preprocess compile assemble link
all:
	$(CC) -Wall -save-temps $(LIB_PATH) $(PWD)/hello.c -o $(PWD)/hello
preprocess:
	$(CC) -Wall -E $(LIB_PATH) $(PWD)/hello.c -o $(PWD)/hello.i
compile:
	$(CC) -Wall -S $(LIB_PATH) $(PWD)/hello.i -o $(PWD)/hello.s
assemble:
	$(CC) -Wall -c $(LIB_PATH) $(PWD)/hello.s -o $(PWD)/hello.o
link:
	$(CC) -Wall -o $(PWD)/hello $(PWD)/hello.o
clean:
	rm hello hello.i hello.s hello.o