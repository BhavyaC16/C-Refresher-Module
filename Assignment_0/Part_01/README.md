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
The assembly code `hello.s` is then converted to an object file `hello.o` in Executable and Linkable Format (ELF). Following is the object code, obtained using the command ```readerelf hello.o```:

 ```elf
 ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          752 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         13
  Section header string table index: 12

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       0000000000000036  0000000000000000  AX       0     0     1
  [ 2] .rela.text        RELA             0000000000000000  00000240
       0000000000000030  0000000000000018   I      10     1     8
  [ 3] .data             PROGBITS         0000000000000000  00000076
       0000000000000000  0000000000000000  WA       0     0     1
  [ 4] .bss              NOBITS           0000000000000000  00000076
       0000000000000000  0000000000000000  WA       0     0     1
  [ 5] .rodata           PROGBITS         0000000000000000  00000076
       0000000000000010  0000000000000000   A       0     0     1
  [ 6] .comment          PROGBITS         0000000000000000  00000086
       000000000000002c  0000000000000001  MS       0     0     1
  [ 7] .note.GNU-stack   PROGBITS         0000000000000000  000000b2
       0000000000000000  0000000000000000           0     0     1
  [ 8] .eh_frame         PROGBITS         0000000000000000  000000b8
       0000000000000038  0000000000000000   A       0     0     8
  [ 9] .rela.eh_frame    RELA             0000000000000000  00000270
       0000000000000018  0000000000000018   I      10     8     8
  [10] .symtab           SYMTAB           0000000000000000  000000f0
       0000000000000120  0000000000000018          11     9     8
  [11] .strtab           STRTAB           0000000000000000  00000210
       000000000000002b  0000000000000000           0     0     1
  [12] .shstrtab         STRTAB           0000000000000000  00000288
       0000000000000061  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  l (large), p (processor specific)

There are no section groups in this file.

There are no program headers in this file.

There is no dynamic section in this file.

Relocation section '.rela.text' at offset 0x240 contains 2 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000021  000500000002 R_X86_64_PC32     0000000000000000 .rodata - 4
00000000002b  000b00000004 R_X86_64_PLT32    0000000000000000 printf - 4

Relocation section '.rela.eh_frame' at offset 0x270 contains 1 entry:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000000020  000200000002 R_X86_64_PC32     0000000000000000 .text + 0

The decoding of unwind sections for machine type Advanced Micro Devices X86-64 is not currently supported.

Symbol table '.symtab' contains 12 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS hello.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    8 
     8: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     9: 0000000000000000    54 FUNC    GLOBAL DEFAULT    1 main
    10: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_
    11: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND printf

 ```
 - The ELF consists of the Program Headers, which provide the kernel and runtime linker information about what to load into memory during runtime for dynamic linking, and the Section Headers, which provide information about compile-time linking to reslove symbols. 
- The ELF File Header contains information about the binary code present in the object file. `ELF64` tells that it is a 64-bit binary code, which is in 2's complement representation and little endian format.
- The object file has 13 section headers: `NULL`, `.text`, `.rela.text`, `.data`, `.bss`, `.rodata`, `.symtab`, and others. 
    - `.txt` contains the executable instructions of the program.
    - `.data` contains initialized data.
    - `.bss` contains uninitialized global data.
    - `.rodata` contains read-only data.
    - `.symtab` is the compile-time static symbol table.
 
#### Linking
The last step involves linking the object file `hello.o` to make an executable. Here all the function call `printf()` will be linked to its definition. The virtual address of the function and all other variables, literals and instructions will be replaced by the actual memory addresses.

The linking process will add information to the executable for setting up of the running environment and passing arguments, as well as returning the value of the program to the kernel, for example, 0 for successful execution.

Following is the executable file `hello`, obtained using the command ```readerelf hello.o```:

```elf
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Shared object file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x540
  Start of program headers:          64 (bytes into file)
  Start of section headers:          6448 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         9
  Size of section headers:           64 (bytes)
  Number of section headers:         29
  Section header string table index: 28

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .interp           PROGBITS         0000000000000238  00000238
       000000000000001c  0000000000000000   A       0     0     1
  [ 2] .note.ABI-tag     NOTE             0000000000000254  00000254
       0000000000000020  0000000000000000   A       0     0     4
  [ 3] .note.gnu.build-i NOTE             0000000000000274  00000274
       0000000000000024  0000000000000000   A       0     0     4
  [ 4] .gnu.hash         GNU_HASH         0000000000000298  00000298
       000000000000001c  0000000000000000   A       5     0     8
  [ 5] .dynsym           DYNSYM           00000000000002b8  000002b8
       00000000000000a8  0000000000000018   A       6     1     8
  [ 6] .dynstr           STRTAB           0000000000000360  00000360
       0000000000000084  0000000000000000   A       0     0     1
  [ 7] .gnu.version      VERSYM           00000000000003e4  000003e4
       000000000000000e  0000000000000002   A       5     0     2
  [ 8] .gnu.version_r    VERNEED          00000000000003f8  000003f8
       0000000000000020  0000000000000000   A       6     1     8
  [ 9] .rela.dyn         RELA             0000000000000418  00000418
       00000000000000c0  0000000000000018   A       5     0     8
  [10] .rela.plt         RELA             00000000000004d8  000004d8
       0000000000000018  0000000000000018  AI       5    22     8
  [11] .init             PROGBITS         00000000000004f0  000004f0
       0000000000000017  0000000000000000  AX       0     0     4
  [12] .plt              PROGBITS         0000000000000510  00000510
       0000000000000020  0000000000000010  AX       0     0     16
  [13] .plt.got          PROGBITS         0000000000000530  00000530
       0000000000000008  0000000000000008  AX       0     0     8
  [14] .text             PROGBITS         0000000000000540  00000540
       00000000000001b2  0000000000000000  AX       0     0     16
  [15] .fini             PROGBITS         00000000000006f4  000006f4
       0000000000000009  0000000000000000  AX       0     0     4
  [16] .rodata           PROGBITS         0000000000000700  00000700
       0000000000000014  0000000000000000   A       0     0     4
  [17] .eh_frame_hdr     PROGBITS         0000000000000714  00000714
       000000000000003c  0000000000000000   A       0     0     4
  [18] .eh_frame         PROGBITS         0000000000000750  00000750
       0000000000000108  0000000000000000   A       0     0     8
  [19] .init_array       INIT_ARRAY       0000000000200db8  00000db8
       0000000000000008  0000000000000008  WA       0     0     8
  [20] .fini_array       FINI_ARRAY       0000000000200dc0  00000dc0
       0000000000000008  0000000000000008  WA       0     0     8
  [21] .dynamic          DYNAMIC          0000000000200dc8  00000dc8
       00000000000001f0  0000000000000010  WA       6     0     8
  [22] .got              PROGBITS         0000000000200fb8  00000fb8
       0000000000000048  0000000000000008  WA       0     0     8
  [23] .data             PROGBITS         0000000000201000  00001000
       0000000000000010  0000000000000000  WA       0     0     8
  [24] .bss              NOBITS           0000000000201010  00001010
       0000000000000008  0000000000000000  WA       0     0     1
  [25] .comment          PROGBITS         0000000000000000  00001010
       000000000000002b  0000000000000001  MS       0     0     1
  [26] .symtab           SYMTAB           0000000000000000  00001040
       00000000000005e8  0000000000000018          27    43     8
  [27] .strtab           STRTAB           0000000000000000  00001628
       0000000000000205  0000000000000000           0     0     1
  [28] .shstrtab         STRTAB           0000000000000000  0000182d
       00000000000000fe  0000000000000000           0     0     1
Key to Flags:
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),
  L (link order), O (extra OS processing required), G (group), T (TLS),
  C (compressed), x (unknown), o (OS specific), E (exclude),
  l (large), p (processor specific)

There are no section groups in this file.

Program Headers:
  Type           Offset             VirtAddr           PhysAddr
                 FileSiz            MemSiz              Flags  Align
  PHDR           0x0000000000000040 0x0000000000000040 0x0000000000000040
                 0x00000000000001f8 0x00000000000001f8  R      0x8
  INTERP         0x0000000000000238 0x0000000000000238 0x0000000000000238
                 0x000000000000001c 0x000000000000001c  R      0x1
      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]
  LOAD           0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000858 0x0000000000000858  R E    0x200000
  LOAD           0x0000000000000db8 0x0000000000200db8 0x0000000000200db8
                 0x0000000000000258 0x0000000000000260  RW     0x200000
  DYNAMIC        0x0000000000000dc8 0x0000000000200dc8 0x0000000000200dc8
                 0x00000000000001f0 0x00000000000001f0  RW     0x8
  NOTE           0x0000000000000254 0x0000000000000254 0x0000000000000254
                 0x0000000000000044 0x0000000000000044  R      0x4
  GNU_EH_FRAME   0x0000000000000714 0x0000000000000714 0x0000000000000714
                 0x000000000000003c 0x000000000000003c  R      0x4
  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000
                 0x0000000000000000 0x0000000000000000  RW     0x10
  GNU_RELRO      0x0000000000000db8 0x0000000000200db8 0x0000000000200db8
                 0x0000000000000248 0x0000000000000248  R      0x1

 Section to Segment mapping:
  Segment Sections...
   00     
   01     .interp 
   02     .interp .note.ABI-tag .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt .plt.got .text .fini .rodata .eh_frame_hdr .eh_frame 
   03     .init_array .fini_array .dynamic .got .data .bss 
   04     .dynamic 
   05     .note.ABI-tag .note.gnu.build-id 
   06     .eh_frame_hdr 
   07     
   08     .init_array .fini_array .dynamic .got 

Dynamic section at offset 0xdc8 contains 27 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
 0x000000000000000c (INIT)               0x4f0
 0x000000000000000d (FINI)               0x6f4
 0x0000000000000019 (INIT_ARRAY)         0x200db8
 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
 0x000000000000001a (FINI_ARRAY)         0x200dc0
 0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)
 0x000000006ffffef5 (GNU_HASH)           0x298
 0x0000000000000005 (STRTAB)             0x360
 0x0000000000000006 (SYMTAB)             0x2b8
 0x000000000000000a (STRSZ)              132 (bytes)
 0x000000000000000b (SYMENT)             24 (bytes)
 0x0000000000000015 (DEBUG)              0x0
 0x0000000000000003 (PLTGOT)             0x200fb8
 0x0000000000000002 (PLTRELSZ)           24 (bytes)
 0x0000000000000014 (PLTREL)             RELA
 0x0000000000000017 (JMPREL)             0x4d8
 0x0000000000000007 (RELA)               0x418
 0x0000000000000008 (RELASZ)             192 (bytes)
 0x0000000000000009 (RELAENT)            24 (bytes)
 0x000000000000001e (FLAGS)              BIND_NOW
 0x000000006ffffffb (FLAGS_1)            Flags: NOW PIE
 0x000000006ffffffe (VERNEED)            0x3f8
 0x000000006fffffff (VERNEEDNUM)         1
 0x000000006ffffff0 (VERSYM)             0x3e4
 0x000000006ffffff9 (RELACOUNT)          3
 0x0000000000000000 (NULL)               0x0

Relocation section '.rela.dyn' at offset 0x418 contains 8 entries:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000200db8  000000000008 R_X86_64_RELATIVE                    640
000000200dc0  000000000008 R_X86_64_RELATIVE                    600
000000201008  000000000008 R_X86_64_RELATIVE                    201008
000000200fd8  000100000006 R_X86_64_GLOB_DAT 0000000000000000 _ITM_deregisterTMClone + 0
000000200fe0  000300000006 R_X86_64_GLOB_DAT 0000000000000000 __libc_start_main@GLIBC_2.2.5 + 0
000000200fe8  000400000006 R_X86_64_GLOB_DAT 0000000000000000 __gmon_start__ + 0
000000200ff0  000500000006 R_X86_64_GLOB_DAT 0000000000000000 _ITM_registerTMCloneTa + 0
000000200ff8  000600000006 R_X86_64_GLOB_DAT 0000000000000000 __cxa_finalize@GLIBC_2.2.5 + 0

Relocation section '.rela.plt' at offset 0x4d8 contains 1 entry:
  Offset          Info           Type           Sym. Value    Sym. Name + Addend
000000200fd0  000200000007 R_X86_64_JUMP_SLO 0000000000000000 printf@GLIBC_2.2.5 + 0

The decoding of unwind sections for machine type Advanced Micro Devices X86-64 is not currently supported.

Symbol table '.dynsym' contains 7 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTab
     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND printf@GLIBC_2.2.5 (2)
     3: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@GLIBC_2.2.5 (2)
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     5: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
     6: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@GLIBC_2.2.5 (2)

Symbol table '.symtab' contains 63 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000238     0 SECTION LOCAL  DEFAULT    1 
     2: 0000000000000254     0 SECTION LOCAL  DEFAULT    2 
     3: 0000000000000274     0 SECTION LOCAL  DEFAULT    3 
     4: 0000000000000298     0 SECTION LOCAL  DEFAULT    4 
     5: 00000000000002b8     0 SECTION LOCAL  DEFAULT    5 
     6: 0000000000000360     0 SECTION LOCAL  DEFAULT    6 
     7: 00000000000003e4     0 SECTION LOCAL  DEFAULT    7 
     8: 00000000000003f8     0 SECTION LOCAL  DEFAULT    8 
     9: 0000000000000418     0 SECTION LOCAL  DEFAULT    9 
    10: 00000000000004d8     0 SECTION LOCAL  DEFAULT   10 
    11: 00000000000004f0     0 SECTION LOCAL  DEFAULT   11 
    12: 0000000000000510     0 SECTION LOCAL  DEFAULT   12 
    13: 0000000000000530     0 SECTION LOCAL  DEFAULT   13 
    14: 0000000000000540     0 SECTION LOCAL  DEFAULT   14 
    15: 00000000000006f4     0 SECTION LOCAL  DEFAULT   15 
    16: 0000000000000700     0 SECTION LOCAL  DEFAULT   16 
    17: 0000000000000714     0 SECTION LOCAL  DEFAULT   17 
    18: 0000000000000750     0 SECTION LOCAL  DEFAULT   18 
    19: 0000000000200db8     0 SECTION LOCAL  DEFAULT   19 
    20: 0000000000200dc0     0 SECTION LOCAL  DEFAULT   20 
    21: 0000000000200dc8     0 SECTION LOCAL  DEFAULT   21 
    22: 0000000000200fb8     0 SECTION LOCAL  DEFAULT   22 
    23: 0000000000201000     0 SECTION LOCAL  DEFAULT   23 
    24: 0000000000201010     0 SECTION LOCAL  DEFAULT   24 
    25: 0000000000000000     0 SECTION LOCAL  DEFAULT   25 
    26: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
    27: 0000000000000570     0 FUNC    LOCAL  DEFAULT   14 deregister_tm_clones
    28: 00000000000005b0     0 FUNC    LOCAL  DEFAULT   14 register_tm_clones
    29: 0000000000000600     0 FUNC    LOCAL  DEFAULT   14 __do_global_dtors_aux
    30: 0000000000201010     1 OBJECT  LOCAL  DEFAULT   24 completed.7697
    31: 0000000000200dc0     0 OBJECT  LOCAL  DEFAULT   20 __do_global_dtors_aux_fin
    32: 0000000000000640     0 FUNC    LOCAL  DEFAULT   14 frame_dummy
    33: 0000000000200db8     0 OBJECT  LOCAL  DEFAULT   19 __frame_dummy_init_array_
    34: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS hello.c
    35: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c
    36: 0000000000000854     0 OBJECT  LOCAL  DEFAULT   18 __FRAME_END__
    37: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS 
    38: 0000000000200dc0     0 NOTYPE  LOCAL  DEFAULT   19 __init_array_end
    39: 0000000000200dc8     0 OBJECT  LOCAL  DEFAULT   21 _DYNAMIC
    40: 0000000000200db8     0 NOTYPE  LOCAL  DEFAULT   19 __init_array_start
    41: 0000000000000714     0 NOTYPE  LOCAL  DEFAULT   17 __GNU_EH_FRAME_HDR
    42: 0000000000200fb8     0 OBJECT  LOCAL  DEFAULT   22 _GLOBAL_OFFSET_TABLE_
    43: 00000000000006f0     2 FUNC    GLOBAL DEFAULT   14 __libc_csu_fini
    44: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTab
    45: 0000000000201000     0 NOTYPE  WEAK   DEFAULT   23 data_start
    46: 0000000000201010     0 NOTYPE  GLOBAL DEFAULT   23 _edata
    47: 00000000000006f4     0 FUNC    GLOBAL DEFAULT   15 _fini
    48: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND printf@@GLIBC_2.2.5
    49: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@@GLIBC_
    50: 0000000000201000     0 NOTYPE  GLOBAL DEFAULT   23 __data_start
    51: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
    52: 0000000000201008     0 OBJECT  GLOBAL HIDDEN    23 __dso_handle
    53: 0000000000000700     4 OBJECT  GLOBAL DEFAULT   16 _IO_stdin_used
    54: 0000000000000680   101 FUNC    GLOBAL DEFAULT   14 __libc_csu_init
    55: 0000000000201018     0 NOTYPE  GLOBAL DEFAULT   24 _end
    56: 0000000000000540    43 FUNC    GLOBAL DEFAULT   14 _start
    57: 0000000000201010     0 NOTYPE  GLOBAL DEFAULT   24 __bss_start
    58: 000000000000064a    54 FUNC    GLOBAL DEFAULT   14 main
    59: 0000000000201010     0 OBJECT  GLOBAL HIDDEN    23 __TMC_END__
    60: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
    61: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@@GLIBC_2.2
    62: 00000000000004f0     0 FUNC    GLOBAL DEFAULT   11 _init

Version symbols section '.gnu.version' contains 7 entries:
 Addr: 00000000000003e4  Offset: 0x0003e4  Link: 5 (.dynsym)
  000:   0 (*local*)       0 (*local*)       2 (GLIBC_2.2.5)   2 (GLIBC_2.2.5)
  004:   0 (*local*)       0 (*local*)       2 (GLIBC_2.2.5)

Version needs section '.gnu.version_r' contains 1 entry:
 Addr: 0x00000000000003f8  Offset: 0x0003f8  Link: 6 (.dynstr)
  000000: Version: 1  File: libc.so.6  Cnt: 1
  0x0010:   Name: GLIBC_2.2.5  Flags: none  Version: 2

Displaying notes found in: .note.ABI-tag
  Owner                 Data size	Description
  GNU                  0x00000010	NT_GNU_ABI_TAG (ABI version tag)
    OS: Linux, ABI: 3.2.0

Displaying notes found in: .note.gnu.build-id
  Owner                 Data size	Description
  GNU                  0x00000014	NT_GNU_BUILD_ID (unique build ID bitstring)
    Build ID: 722f29701546260f484c99829446373892245fec

```

### Resources
 - [CS-Fundamentals: Compile and Execute C Program](https://cs-fundamentals.com/c-programming/how-to-compile-c-program-using-gcc.php)
 - [Medium Blog: C Program Compilation Process](https://medium.com/@earthtojhuang/gcc-main-c-9f6ee2e6894b)
 - [NTU: GCC and Make (Compiling, Linking and Building
C/C++ Applications)](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html)
 - [The Geek Stuff: Journey of a C Program to Linux Executable in 4 Stages](https://www.thegeekstuff.com/2011/10/c-program-to-an-executable/)
 - [LAMP – Programming Methods Laboratory (EPFL): How the compiler works](http://lampwww.epfl.ch/~fsalvi/docs/gcc/www.network-theory.co.uk/docs/gccintro/gccintro_68.html)
- [Infosec: Hello World: C, Assembly, Object File and Executable](https://resources.infosecinstitute.com/hello-world-c-assembly-object-file-and-executable/#gref)
- [ELF](https://stevens.netmeister.org/631/elf.html)
