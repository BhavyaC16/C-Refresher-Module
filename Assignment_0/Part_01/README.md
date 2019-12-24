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
---

### Compilation Process and Output Files
#### Pre-processing
The source code `hello.c` is pre-processed and the file `hello.i` is generated.
- The line included headerfiles are expanded and included in the source code.
- The macros defined using ```#define``` in the source code are replaced (substitution) in the pre-processed output.
- Conditional Compilation takes place using the ```#ifdef``` directives for C source codes, for running the source code on different platforms or different versions of libraries and hardware.

The output file:
```c
...
extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);

extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));

...

# 2 "/home/bhavya16/Desktop/C_Refresher_Module/Assignment_0/Part_01/hello.c" 2

# 3 "/home/bhavya16/Desktop/C_Refresher_Module/Assignment_0/Part_01/hello.c"
int main()
{
 int a = 10;
 int b = 20;
 printf("a = %d \nb = %d\n", a, b);
 return(0);
}

```

 - In the file `hello.i`, the line ```#include<stdio.h>``` cannot be found as the headerfile stdio.h has been expanded and included in the source code. 
 - The comments in the file `hello.c` cannot be found here.
 - The keyword `extern` before the function header for `printf()` indicates that it's definition is located elsewhere and needs to be linked before the execution of the source code.
 - The source code present in `hello.c` can be found towards the end in `hello.i`
 
#### Compilation
The file `hello.i` is compiled to generate the assembly code file `hello.s` as follows: 
 ```as
    .file	"hello.c"
	.text
	.section	.rodata
.LC0:
	.string	"a = %d \nb = %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$10, -8(%rbp)
	movl	$20, -4(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
 ```
 Here, the instructions are in assembly language and can be assembled by an assembler into machine level code.
 - The directive `.file` includes the name of the source code file, `hello.c`
 - The `.rodata` specifies read-only variables, which is the string:
 ```c
 "a = %d \nb = %d\n"
 ```
 This string can now be accessed via the `LC0` variable. The scope and function in which the variable can be accessed (`main`) is also specified.
 - Next, the main function is defined under the `main:` label. Here, `rbp`, `rsp`, `edx`, `eax`, `esi`, etc. represent registers. These instructions shall be executed sequentially. There are instructions to initialize stacks and registers with required variables and values.
 - ```call printf@PLT``` is the print statement.
 - The `.size` instruction stored the size of the main function in `.-main`. The `.ident` instruction shall save information about the compiler used to generate the assembly code. These shell be written to the object file.
 
#### Assembly
 

### Resources
 - [CS-Fundamentals: Compile and Execute C Program](https://cs-fundamentals.com/c-programming/how-to-compile-c-program-using-gcc.php)
 - [Medium Blog: C Program Compilation Process](https://medium.com/@earthtojhuang/gcc-main-c-9f6ee2e6894b)
 - [NTU: GCC and Make (Compiling, Linking and Building
C/C++ Applications)](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html)
 - [The Geek Stuff: Journey of a C Program to Linux Executable in 4 Stages](https://www.thegeekstuff.com/2011/10/c-program-to-an-executable/)
 - [LAMP – Programming Methods Laboratory (EPFL): How the compiler works](http://lampwww.epfl.ch/~fsalvi/docs/gcc/www.network-theory.co.uk/docs/gccintro/gccintro_68.html)
- [Infosec: Hello World: C, Assembly, Object File and Executable](https://resources.infosecinstitute.com/hello-world-c-assembly-object-file-and-executable/#gref)
