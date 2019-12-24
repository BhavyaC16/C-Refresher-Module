### Compilation and Command Line Options
- `-save-temps`: Instructs the compiler to not to delete intermediate files, generating `hello.i`, `hello.s`, `hello.o` and `hello`:<br>
```gcc -save-temps hello.c -o hello``` <br>
Execute the command: `make all` to compile using `-save-temps` flag
- `-E`: Stops the compilation after the preprocessing. The output is in the form of pre-processed code and is sent to standard output. In `hello.c`, the library `stdio.h` has to be included in preprocessing, and `hello.i` is genarated upon excuting the following command:<br>
```gcc -E hello.c -o hello.i ```<br>
Execute the command `make preprocess` to pause the compilation after preprocessing, using the `-E` flag. 
- `-S`: Stops after compilation, without assembling. The output is in the form of an assembly code file for every input file that requires to be compiled. Here, `hello.i` is compiled to generate `hello.s` upon executing the following command:<br>
```gcc -S hello.i -o hello.s ```<br>
Execute the command `make compile` to generate the assembly code using the `-S` flag after having preprocessed.
- `-c`: Compiles or assembles the source code files without linking them. The output is in the form of object files. Here, `hello.s` (assembly code) can be converted to `hello.o` (object file) using the following command:<br>
```gcc -c hello.s -o hello.o```<br>
Execute the command `make link` to generate `hello.o` using the `-c` flag after having compiled.
- `-o`: Places the executable/preprocessed/compiled/assembled file as the specified file name.
- `-Wall`: Enables all the compiler warnings.

### Compilation Process and Output Files

### Resources
 - [CS-Fundamentals: Compile and Execute C Program](https://cs-fundamentals.com/c-programming/how-to-compile-c-program-using-gcc.php)
 - [Medium Blog: C Program Compilation Process](https://medium.com/@earthtojhuang/gcc-main-c-9f6ee2e6894b)
 - [NTU: GCC and Make (Compiling, Linking and Building
C/C++ Applications)](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html)
 - [The Geek Stuff: Journey of a C Program to Linux Executable in 4 Stages](https://www.thegeekstuff.com/2011/10/c-program-to-an-executable/)
 - [LAMP – Programming Methods Laboratory (EPFL): How the compiler works](http://lampwww.epfl.ch/~fsalvi/docs/gcc/www.network-theory.co.uk/docs/gccintro/gccintro_68.html)
- [Infosec: Hello World: C, Assembly, Object File and Executable](https://resources.infosecinstitute.com/hello-world-c-assembly-object-file-and-executable/#gref)
