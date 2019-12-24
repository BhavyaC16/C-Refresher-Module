CC:=gcc
LIB_PATH:=-pthread

default:
	make preprocess compile assemble link
all:
	$(CC) -Wall -save-temps $(LIB_PATH) $(PWD)/hello.c -o $(PWD)/hello
preprocess:
	$(CC) -Wall -E $(LIB_PATH) $(PWD)/hello.c -o $(PWD)/hello.i
compile:
	$(CC) -S $(LIB_PATH) $(PWD)/hello.i -o $(PWD)/hello.s
assemble:
	$(CC) -m64 -masm=intel -c $(LIB_PATH) $(PWD)/hello.s -o $(PWD)/hello.o
link:
	$(CC) -o $(PWD)/hello $(PWD)/hello.o
clean:
	rm hello hello.i hello.s hello.o