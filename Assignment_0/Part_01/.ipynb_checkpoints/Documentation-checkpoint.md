{
 "cells": [
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "##  Understanding Program Compilation Process\n",
    "C Programming Language Refresher Module for Operating Systems <br>\n",
    "__Assignment 0.1__ <br>\n",
    "__Submitted by__: Bhavya Chopra <br>\n",
    "__Roll Number__: 2018333 <br>\n",
    "__E-mail__: bhavya18333@iiitd.ac.in\n",
    "\n",
    "---\n",
    "### Compilation and Command Line Options\n",
    "- `-save-temps`: Instructs the compiler to not to delete intermediate files, generating `hello.i`, `hello.s`, `hello.o` and `hello`:<br>\n",
    "```gcc -save-temps hello.c -o hello``` <br>\n",
    "Execute the command: `make all` to compile using `-save-temps` flag\n",
    "- `-E`: Stops the compilation after the preprocessing. The output is in the form of pre-processed code and is sent to standard output. In `hello.c`, the library `stdio.h` has to be included in preprocessing, and `hello.i` is genarated upon excuting the following command:<br>\n",
    "```gcc -E hello.c -o hello.i ```<br>\n",
    "Execute the command `make preprocess` to pause the compilation after preprocessing, using the `-E` flag. \n",
    "- `-S`: Stops after compilation, without assembling. The output is in the form of an assembly code file for every input file that requires to be compiled. Here, `hello.i` is compiled to generate `hello.s` upon executing the following command:<br>\n",
    "```gcc -S hello.i -o hello.s ```<br>\n",
    "Execute the command `make compile` to generate the assembly code using the `-S` flag after having preprocessed.\n",
    "- `-c`: Compiles or assembles the source code files without linking them. The output is in the form of object files. Here, `hello.s` (assembly code) can be converted to `hello.o` (object file) using the following command:<br>\n",
    "```gcc -c hello.s -o hello.o```<br>\n",
    "Execute the command `make link` to generate `hello.o` using the `-c` flag after having compiled.\n",
    "- `-o`: Places the executable/preprocessed/compiled/assembled file as the specified file name.\n",
    "- `-Wall`: Enables all the compiler warnings.\n",
    "---\n",
    "\n",
    "### Compilation Process and Output Files\n",
    "#### [STEP 1] Pre-processing\n",
    "The source code `hello.c` is pre-processed and the file `hello.i` is generated.\n",
    "- The line included headerfiles are expanded and included in the source code.\n",
    "- The macros defined using ```#define``` in the source code are replaced (substitution) in the pre-processed output.\n",
    "- Conditional Compilation takes place using the ```#ifdef``` directives for C source codes, for running the source code on different platforms or different versions of libraries and hardware.\n",
    "\n",
    "The output file:\n",
    "```c\n",
    "...\n",
    "extern int fprintf (FILE *__restrict __stream,\n",
    "      const char *__restrict __format, ...);\n",
    "\n",
    "extern int printf (const char *__restrict __format, ...);\n",
    "\n",
    "extern int sprintf (char *__restrict __s,\n",
    "      const char *__restrict __format, ...) __attribute__ ((__nothrow__));\n",
    "\n",
    "...\n",
    "\n",
    "# 2 \"/home/bhavya16/Desktop/C_Refresher_Module/Assignment_0/Part_01/hello.c\" 2\n",
    "\n",
    "# 3 \"/home/bhavya16/Desktop/C_Refresher_Module/Assignment_0/Part_01/hello.c\"\n",
    "int main()\n",
    "{\n",
    " int a = 10;\n",
    " int b = 20;\n",
    " printf(\"a = %d \\nb = %d\\n\", a, b);\n",
    " return(0);\n",
    "}\n",
    "\n",
    "```\n",
    "\n",
    " - In the file `hello.i`, the line ```#include<stdio.h>``` cannot be found as the headerfile stdio.h has been expanded and included in the source code. \n",
    " - The comments in the file `hello.c` cannot be found here.\n",
    " - The keyword `extern` before the function header for `printf()` indicates that it's definition is located elsewhere and needs to be linked before the execution of the source code.\n",
    " - The source code present in `hello.c` can be found towards the end in `hello.i`\n",
    " \n",
    "#### [STEP 2] Compilation\n",
    "The file `hello.i` is compiled to generate the assembly code file `hello.s` as follows: \n",
    " ```as\n",
    "    .file\t\"hello.c\"\n",
    "\t.text\n",
    "\t.section\t.rodata\n",
    ".LC0:\n",
    "\t.string\t\"a = %d \\nb = %d\\n\"\n",
    "\t.text\n",
    "\t.globl\tmain\n",
    "\t.type\tmain, @function\n",
    "main:\n",
    ".LFB0:\n",
    "\t.cfi_startproc\n",
    "\tpushq\t%rbp\n",
    "\t.cfi_def_cfa_offset 16\n",
    "\t.cfi_offset 6, -16\n",
    "\tmovq\t%rsp, %rbp\n",
    "\t.cfi_def_cfa_register 6\n",
    "\tsubq\t$16, %rsp\n",
    "\tmovl\t$10, -8(%rbp)\n",
    "\tmovl\t$20, -4(%rbp)\n",
    "\tmovl\t-4(%rbp), %edx\n",
    "\tmovl\t-8(%rbp), %eax\n",
    "\tmovl\t%eax, %esi\n",
    "\tleaq\t.LC0(%rip), %rdi\n",
    "\tmovl\t$0, %eax\n",
    "\tcall\tprintf@PLT\n",
    "\tmovl\t$0, %eax\n",
    "\tleave\n",
    "\t.cfi_def_cfa 7, 8\n",
    "\tret\n",
    "\t.cfi_endproc\n",
    ".LFE0:\n",
    "\t.size\tmain, .-main\n",
    "\t.ident\t\"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0\"\n",
    "\t.section\t.note.GNU-stack,\"\",@progbits\n",
    " ```\n",
    " Here, the instructions are in assembly language and can be assembled by an assembler into machine level code.\n",
    " - The directive `.file` includes the name of the source code file, `hello.c`\n",
    " - The `.rodata` specifies read-only variables, which is the string:\n",
    " ```c\n",
    " \"a = %d \\nb = %d\\n\"\n",
    " ```\n",
    " This string can now be accessed via the `LC0` variable. The scope and function in which the variable can be accessed (`main`) is also specified.\n",
    " - Next, the main function is defined under the `main:` label. Here, `rbp`, `rsp`, `edx`, `eax`, `esi`, etc. represent registers. These instructions shall be executed sequentially. There are instructions to initialize stacks and registers with required variables and values.\n",
    " - ```call printf@PLT``` is the print statement.\n",
    " - The `.size` instruction stored the size of the main function in `.-main`. The `.ident` instruction shall save information about the compiler used to generate the assembly code. These shell be written to the object file.\n",
    " \n",
    "#### [STEP 3] Assembly\n",
    "The assembly code `hello.s` is then converted to an object file `hello.o` in Executable and Linkable Format (ELF). Following is the object code, obtained using the command ```readerelf hello.o```:\n",
    "\n",
    " ```elf\n",
    " ELF Header:\n",
    "  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 \n",
    "  Class:                             ELF64\n",
    "  Data:                              2's complement, little endian\n",
    "  Version:                           1 (current)\n",
    "  OS/ABI:                            UNIX - System V\n",
    "  ABI Version:                       0\n",
    "  Type:                              REL (Relocatable file)\n",
    "  Machine:                           Advanced Micro Devices X86-64\n",
    "  Version:                           0x1\n",
    "  Entry point address:               0x0\n",
    "  Start of program headers:          0 (bytes into file)\n",
    "  Start of section headers:          752 (bytes into file)\n",
    "  Flags:                             0x0\n",
    "  Size of this header:               64 (bytes)\n",
    "  Size of program headers:           0 (bytes)\n",
    "  Number of program headers:         0\n",
    "  Size of section headers:           64 (bytes)\n",
    "  Number of section headers:         13\n",
    "  Section header string table index: 12\n",
    "\n",
    "Section Headers:\n",
    "  [Nr] Name              Type             Address           Offset\n",
    "       Size              EntSize          Flags  Link  Info  Align\n",
    "  [ 0]                   NULL             0000000000000000  00000000\n",
    "       0000000000000000  0000000000000000           0     0     0\n",
    "  [ 1] .text             PROGBITS         0000000000000000  00000040\n",
    "       0000000000000036  0000000000000000  AX       0     0     1\n",
    "  [ 2] .rela.text        RELA             0000000000000000  00000240\n",
    "       0000000000000030  0000000000000018   I      10     1     8\n",
    "  [ 3] .data             PROGBITS         0000000000000000  00000076\n",
    "       0000000000000000  0000000000000000  WA       0     0     1\n",
    "  [ 4] .bss              NOBITS           0000000000000000  00000076\n",
    "       0000000000000000  0000000000000000  WA       0     0     1\n",
    "  [ 5] .rodata           PROGBITS         0000000000000000  00000076\n",
    "       0000000000000010  0000000000000000   A       0     0     1\n",
    "  [ 6] .comment          PROGBITS         0000000000000000  00000086\n",
    "       000000000000002c  0000000000000001  MS       0     0     1\n",
    "  [ 7] .note.GNU-stack   PROGBITS         0000000000000000  000000b2\n",
    "       0000000000000000  0000000000000000           0     0     1\n",
    "  [ 8] .eh_frame         PROGBITS         0000000000000000  000000b8\n",
    "       0000000000000038  0000000000000000   A       0     0     8\n",
    "  [ 9] .rela.eh_frame    RELA             0000000000000000  00000270\n",
    "       0000000000000018  0000000000000018   I      10     8     8\n",
    "  [10] .symtab           SYMTAB           0000000000000000  000000f0\n",
    "       0000000000000120  0000000000000018          11     9     8\n",
    "  [11] .strtab           STRTAB           0000000000000000  00000210\n",
    "       000000000000002b  0000000000000000           0     0     1\n",
    "  [12] .shstrtab         STRTAB           0000000000000000  00000288\n",
    "       0000000000000061  0000000000000000           0     0     1\n",
    "Key to Flags:\n",
    "  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),\n",
    "  L (link order), O (extra OS processing required), G (group), T (TLS),\n",
    "  C (compressed), x (unknown), o (OS specific), E (exclude),\n",
    "  l (large), p (processor specific)\n",
    "\n",
    "There are no section groups in this file.\n",
    "\n",
    "There are no program headers in this file.\n",
    "\n",
    "There is no dynamic section in this file.\n",
    "\n",
    "Relocation section '.rela.text' at offset 0x240 contains 2 entries:\n",
    "  Offset          Info           Type           Sym. Value    Sym. Name + Addend\n",
    "000000000021  000500000002 R_X86_64_PC32     0000000000000000 .rodata - 4\n",
    "00000000002b  000b00000004 R_X86_64_PLT32    0000000000000000 printf - 4\n",
    "\n",
    "Relocation section '.rela.eh_frame' at offset 0x270 contains 1 entry:\n",
    "  Offset          Info           Type           Sym. Value    Sym. Name + Addend\n",
    "000000000020  000200000002 R_X86_64_PC32     0000000000000000 .text + 0\n",
    "\n",
    "The decoding of unwind sections for machine type Advanced Micro Devices X86-64 is not currently supported.\n",
    "\n",
    "Symbol table '.symtab' contains 12 entries:\n",
    "   Num:    Value          Size Type    Bind   Vis      Ndx Name\n",
    "     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND \n",
    "     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS hello.c\n",
    "     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 \n",
    "     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 \n",
    "     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 \n",
    "     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 \n",
    "     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 \n",
    "     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    8 \n",
    "     8: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 \n",
    "     9: 0000000000000000    54 FUNC    GLOBAL DEFAULT    1 main\n",
    "    10: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_\n",
    "    11: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND printf\n",
    "\n",
    " ```\n",
    " - The ELF consists of the Program Headers, which provide the kernel and runtime linker information about what to load into memory during runtime for dynamic linking, and the Section Headers, which provide information about compile-time linking to reslove symbols. \n",
    "- The ELF File Header contains information about the binary code present in the object file. `ELF64` tells that it is a 64-bit binary code, which is in 2's complement representation and little endian format.\n",
    "- The object file has 13 section headers: `NULL`, `.text`, `.rela.text`, `.data`, `.bss`, `.rodata`, `.symtab`, and others. \n",
    "    - `.txt` contains the executable instructions of the program.\n",
    "    - `.data` contains initialized data.\n",
    "    - `.bss` contains uninitialized global data.\n",
    "    - `.rodata` contains read-only data.\n",
    "    - `.symtab` is the compile-time static symbol table.\n",
    " \n",
    "#### [STEP 4] Linking\n",
    "The last step involves linking the object file `hello.o` to make an executable. Here all the function call `printf()` will be linked to its definition. The virtual address of the function and all other variables, literals and instructions will be replaced by the actual memory addresses.\n",
    "\n",
    "The linking process will add information to the executable for setting up of the running environment and passing arguments, as well as returning the value of the program to the kernel, for example, 0 for successful execution.\n",
    "\n",
    "Following is the executable file `hello`, obtained using the command ```readerelf hello.o```:\n",
    "\n",
    "```elf\n",
    "ELF Header:\n",
    "  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 \n",
    "  Class:                             ELF64\n",
    "  Data:                              2's complement, little endian\n",
    "  Version:                           1 (current)\n",
    "  OS/ABI:                            UNIX - System V\n",
    "  ABI Version:                       0\n",
    "  Type:                              DYN (Shared object file)\n",
    "  Machine:                           Advanced Micro Devices X86-64\n",
    "  Version:                           0x1\n",
    "  Entry point address:               0x540\n",
    "  Start of program headers:          64 (bytes into file)\n",
    "  Start of section headers:          6448 (bytes into file)\n",
    "  Flags:                             0x0\n",
    "  Size of this header:               64 (bytes)\n",
    "  Size of program headers:           56 (bytes)\n",
    "  Number of program headers:         9\n",
    "  Size of section headers:           64 (bytes)\n",
    "  Number of section headers:         29\n",
    "  Section header string table index: 28\n",
    "\n",
    "Section Headers:\n",
    "  [Nr] Name              Type             Address           Offset\n",
    "       Size              EntSize          Flags  Link  Info  Align\n",
    "  [ 0]                   NULL             0000000000000000  00000000\n",
    "       0000000000000000  0000000000000000           0     0     0\n",
    "  [ 1] .interp           PROGBITS         0000000000000238  00000238\n",
    "       000000000000001c  0000000000000000   A       0     0     1\n",
    "  [ 2] .note.ABI-tag     NOTE             0000000000000254  00000254\n",
    "       0000000000000020  0000000000000000   A       0     0     4\n",
    "  [ 3] .note.gnu.build-i NOTE             0000000000000274  00000274\n",
    "       0000000000000024  0000000000000000   A       0     0     4\n",
    "  [ 4] .gnu.hash         GNU_HASH         0000000000000298  00000298\n",
    "       000000000000001c  0000000000000000   A       5     0     8\n",
    "  [ 5] .dynsym           DYNSYM           00000000000002b8  000002b8\n",
    "       00000000000000a8  0000000000000018   A       6     1     8\n",
    "  [ 6] .dynstr           STRTAB           0000000000000360  00000360\n",
    "       0000000000000084  0000000000000000   A       0     0     1\n",
    "  [ 7] .gnu.version      VERSYM           00000000000003e4  000003e4\n",
    "       000000000000000e  0000000000000002   A       5     0     2\n",
    "  [ 8] .gnu.version_r    VERNEED          00000000000003f8  000003f8\n",
    "       0000000000000020  0000000000000000   A       6     1     8\n",
    "  [ 9] .rela.dyn         RELA             0000000000000418  00000418\n",
    "       00000000000000c0  0000000000000018   A       5     0     8\n",
    "  [10] .rela.plt         RELA             00000000000004d8  000004d8\n",
    "       0000000000000018  0000000000000018  AI       5    22     8\n",
    "  [11] .init             PROGBITS         00000000000004f0  000004f0\n",
    "       0000000000000017  0000000000000000  AX       0     0     4\n",
    "  [12] .plt              PROGBITS         0000000000000510  00000510\n",
    "       0000000000000020  0000000000000010  AX       0     0     16\n",
    "  [13] .plt.got          PROGBITS         0000000000000530  00000530\n",
    "       0000000000000008  0000000000000008  AX       0     0     8\n",
    "  [14] .text             PROGBITS         0000000000000540  00000540\n",
    "       00000000000001b2  0000000000000000  AX       0     0     16\n",
    "  [15] .fini             PROGBITS         00000000000006f4  000006f4\n",
    "       0000000000000009  0000000000000000  AX       0     0     4\n",
    "  [16] .rodata           PROGBITS         0000000000000700  00000700\n",
    "       0000000000000014  0000000000000000   A       0     0     4\n",
    "  [17] .eh_frame_hdr     PROGBITS         0000000000000714  00000714\n",
    "       000000000000003c  0000000000000000   A       0     0     4\n",
    "  [18] .eh_frame         PROGBITS         0000000000000750  00000750\n",
    "       0000000000000108  0000000000000000   A       0     0     8\n",
    "  [19] .init_array       INIT_ARRAY       0000000000200db8  00000db8\n",
    "       0000000000000008  0000000000000008  WA       0     0     8\n",
    "  [20] .fini_array       FINI_ARRAY       0000000000200dc0  00000dc0\n",
    "       0000000000000008  0000000000000008  WA       0     0     8\n",
    "  [21] .dynamic          DYNAMIC          0000000000200dc8  00000dc8\n",
    "       00000000000001f0  0000000000000010  WA       6     0     8\n",
    "  [22] .got              PROGBITS         0000000000200fb8  00000fb8\n",
    "       0000000000000048  0000000000000008  WA       0     0     8\n",
    "  [23] .data             PROGBITS         0000000000201000  00001000\n",
    "       0000000000000010  0000000000000000  WA       0     0     8\n",
    "  [24] .bss              NOBITS           0000000000201010  00001010\n",
    "       0000000000000008  0000000000000000  WA       0     0     1\n",
    "  [25] .comment          PROGBITS         0000000000000000  00001010\n",
    "       000000000000002b  0000000000000001  MS       0     0     1\n",
    "  [26] .symtab           SYMTAB           0000000000000000  00001040\n",
    "       00000000000005e8  0000000000000018          27    43     8\n",
    "  [27] .strtab           STRTAB           0000000000000000  00001628\n",
    "       0000000000000205  0000000000000000           0     0     1\n",
    "  [28] .shstrtab         STRTAB           0000000000000000  0000182d\n",
    "       00000000000000fe  0000000000000000           0     0     1\n",
    "Key to Flags:\n",
    "  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),\n",
    "  L (link order), O (extra OS processing required), G (group), T (TLS),\n",
    "  C (compressed), x (unknown), o (OS specific), E (exclude),\n",
    "  l (large), p (processor specific)\n",
    "\n",
    "There are no section groups in this file.\n",
    "\n",
    "Program Headers:\n",
    "  Type           Offset             VirtAddr           PhysAddr\n",
    "                 FileSiz            MemSiz              Flags  Align\n",
    "  PHDR           0x0000000000000040 0x0000000000000040 0x0000000000000040\n",
    "                 0x00000000000001f8 0x00000000000001f8  R      0x8\n",
    "  INTERP         0x0000000000000238 0x0000000000000238 0x0000000000000238\n",
    "                 0x000000000000001c 0x000000000000001c  R      0x1\n",
    "      [Requesting program interpreter: /lib64/ld-linux-x86-64.so.2]\n",
    "  LOAD           0x0000000000000000 0x0000000000000000 0x0000000000000000\n",
    "                 0x0000000000000858 0x0000000000000858  R E    0x200000\n",
    "  LOAD           0x0000000000000db8 0x0000000000200db8 0x0000000000200db8\n",
    "                 0x0000000000000258 0x0000000000000260  RW     0x200000\n",
    "  DYNAMIC        0x0000000000000dc8 0x0000000000200dc8 0x0000000000200dc8\n",
    "                 0x00000000000001f0 0x00000000000001f0  RW     0x8\n",
    "  NOTE           0x0000000000000254 0x0000000000000254 0x0000000000000254\n",
    "                 0x0000000000000044 0x0000000000000044  R      0x4\n",
    "  GNU_EH_FRAME   0x0000000000000714 0x0000000000000714 0x0000000000000714\n",
    "                 0x000000000000003c 0x000000000000003c  R      0x4\n",
    "  GNU_STACK      0x0000000000000000 0x0000000000000000 0x0000000000000000\n",
    "                 0x0000000000000000 0x0000000000000000  RW     0x10\n",
    "  GNU_RELRO      0x0000000000000db8 0x0000000000200db8 0x0000000000200db8\n",
    "                 0x0000000000000248 0x0000000000000248  R      0x1\n",
    "\n",
    " Section to Segment mapping:\n",
    "  Segment Sections...\n",
    "   00     \n",
    "   01     .interp \n",
    "   02     .interp .note.ABI-tag .note.gnu.build-id .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt .plt.got .text .fini .rodata .eh_frame_hdr .eh_frame \n",
    "   03     .init_array .fini_array .dynamic .got .data .bss \n",
    "   04     .dynamic \n",
    "   05     .note.ABI-tag .note.gnu.build-id \n",
    "   06     .eh_frame_hdr \n",
    "   07     \n",
    "   08     .init_array .fini_array .dynamic .got \n",
    "\n",
    "Dynamic section at offset 0xdc8 contains 27 entries:\n",
    "  Tag        Type                         Name/Value\n",
    " 0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]\n",
    " 0x000000000000000c (INIT)               0x4f0\n",
    " 0x000000000000000d (FINI)               0x6f4\n",
    " 0x0000000000000019 (INIT_ARRAY)         0x200db8\n",
    " 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)\n",
    " 0x000000000000001a (FINI_ARRAY)         0x200dc0\n",
    " 0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)\n",
    " 0x000000006ffffef5 (GNU_HASH)           0x298\n",
    " 0x0000000000000005 (STRTAB)             0x360\n",
    " 0x0000000000000006 (SYMTAB)             0x2b8\n",
    " 0x000000000000000a (STRSZ)              132 (bytes)\n",
    " 0x000000000000000b (SYMENT)             24 (bytes)\n",
    " 0x0000000000000015 (DEBUG)              0x0\n",
    " 0x0000000000000003 (PLTGOT)             0x200fb8\n",
    " 0x0000000000000002 (PLTRELSZ)           24 (bytes)\n",
    " 0x0000000000000014 (PLTREL)             RELA\n",
    " 0x0000000000000017 (JMPREL)             0x4d8\n",
    " 0x0000000000000007 (RELA)               0x418\n",
    " 0x0000000000000008 (RELASZ)             192 (bytes)\n",
    " 0x0000000000000009 (RELAENT)            24 (bytes)\n",
    " 0x000000000000001e (FLAGS)              BIND_NOW\n",
    " 0x000000006ffffffb (FLAGS_1)            Flags: NOW PIE\n",
    " 0x000000006ffffffe (VERNEED)            0x3f8\n",
    " 0x000000006fffffff (VERNEEDNUM)         1\n",
    " 0x000000006ffffff0 (VERSYM)             0x3e4\n",
    " 0x000000006ffffff9 (RELACOUNT)          3\n",
    " 0x0000000000000000 (NULL)               0x0\n",
    "\n",
    "Relocation section '.rela.dyn' at offset 0x418 contains 8 entries:\n",
    "  Offset          Info           Type           Sym. Value    Sym. Name + Addend\n",
    "000000200db8  000000000008 R_X86_64_RELATIVE                    640\n",
    "000000200dc0  000000000008 R_X86_64_RELATIVE                    600\n",
    "000000201008  000000000008 R_X86_64_RELATIVE                    201008\n",
    "000000200fd8  000100000006 R_X86_64_GLOB_DAT 0000000000000000 _ITM_deregisterTMClone + 0\n",
    "000000200fe0  000300000006 R_X86_64_GLOB_DAT 0000000000000000 __libc_start_main@GLIBC_2.2.5 + 0\n",
    "000000200fe8  000400000006 R_X86_64_GLOB_DAT 0000000000000000 __gmon_start__ + 0\n",
    "000000200ff0  000500000006 R_X86_64_GLOB_DAT 0000000000000000 _ITM_registerTMCloneTa + 0\n",
    "000000200ff8  000600000006 R_X86_64_GLOB_DAT 0000000000000000 __cxa_finalize@GLIBC_2.2.5 + 0\n",
    "\n",
    "Relocation section '.rela.plt' at offset 0x4d8 contains 1 entry:\n",
    "  Offset          Info           Type           Sym. Value    Sym. Name + Addend\n",
    "000000200fd0  000200000007 R_X86_64_JUMP_SLO 0000000000000000 printf@GLIBC_2.2.5 + 0\n",
    "\n",
    "The decoding of unwind sections for machine type Advanced Micro Devices X86-64 is not currently supported.\n",
    "\n",
    "Symbol table '.dynsym' contains 7 entries:\n",
    "   Num:    Value          Size Type    Bind   Vis      Ndx Name\n",
    "     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND \n",
    "     1: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTab\n",
    "     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND printf@GLIBC_2.2.5 (2)\n",
    "     3: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@GLIBC_2.2.5 (2)\n",
    "     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__\n",
    "     5: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable\n",
    "     6: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@GLIBC_2.2.5 (2)\n",
    "\n",
    "Symbol table '.symtab' contains 63 entries:\n",
    "   Num:    Value          Size Type    Bind   Vis      Ndx Name\n",
    "     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND \n",
    "     1: 0000000000000238     0 SECTION LOCAL  DEFAULT    1 \n",
    "     2: 0000000000000254     0 SECTION LOCAL  DEFAULT    2 \n",
    "     3: 0000000000000274     0 SECTION LOCAL  DEFAULT    3 \n",
    "     4: 0000000000000298     0 SECTION LOCAL  DEFAULT    4 \n",
    "     5: 00000000000002b8     0 SECTION LOCAL  DEFAULT    5 \n",
    "     6: 0000000000000360     0 SECTION LOCAL  DEFAULT    6 \n",
    "     7: 00000000000003e4     0 SECTION LOCAL  DEFAULT    7 \n",
    "     8: 00000000000003f8     0 SECTION LOCAL  DEFAULT    8 \n",
    "     9: 0000000000000418     0 SECTION LOCAL  DEFAULT    9 \n",
    "    10: 00000000000004d8     0 SECTION LOCAL  DEFAULT   10 \n",
    "    11: 00000000000004f0     0 SECTION LOCAL  DEFAULT   11 \n",
    "    12: 0000000000000510     0 SECTION LOCAL  DEFAULT   12 \n",
    "    13: 0000000000000530     0 SECTION LOCAL  DEFAULT   13 \n",
    "    14: 0000000000000540     0 SECTION LOCAL  DEFAULT   14 \n",
    "    15: 00000000000006f4     0 SECTION LOCAL  DEFAULT   15 \n",
    "    16: 0000000000000700     0 SECTION LOCAL  DEFAULT   16 \n",
    "    17: 0000000000000714     0 SECTION LOCAL  DEFAULT   17 \n",
    "    18: 0000000000000750     0 SECTION LOCAL  DEFAULT   18 \n",
    "    19: 0000000000200db8     0 SECTION LOCAL  DEFAULT   19 \n",
    "    20: 0000000000200dc0     0 SECTION LOCAL  DEFAULT   20 \n",
    "    21: 0000000000200dc8     0 SECTION LOCAL  DEFAULT   21 \n",
    "    22: 0000000000200fb8     0 SECTION LOCAL  DEFAULT   22 \n",
    "    23: 0000000000201000     0 SECTION LOCAL  DEFAULT   23 \n",
    "    24: 0000000000201010     0 SECTION LOCAL  DEFAULT   24 \n",
    "    25: 0000000000000000     0 SECTION LOCAL  DEFAULT   25 \n",
    "    26: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c\n",
    "    27: 0000000000000570     0 FUNC    LOCAL  DEFAULT   14 deregister_tm_clones\n",
    "    28: 00000000000005b0     0 FUNC    LOCAL  DEFAULT   14 register_tm_clones\n",
    "    29: 0000000000000600     0 FUNC    LOCAL  DEFAULT   14 __do_global_dtors_aux\n",
    "    30: 0000000000201010     1 OBJECT  LOCAL  DEFAULT   24 completed.7697\n",
    "    31: 0000000000200dc0     0 OBJECT  LOCAL  DEFAULT   20 __do_global_dtors_aux_fin\n",
    "    32: 0000000000000640     0 FUNC    LOCAL  DEFAULT   14 frame_dummy\n",
    "    33: 0000000000200db8     0 OBJECT  LOCAL  DEFAULT   19 __frame_dummy_init_array_\n",
    "    34: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS hello.c\n",
    "    35: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS crtstuff.c\n",
    "    36: 0000000000000854     0 OBJECT  LOCAL  DEFAULT   18 __FRAME_END__\n",
    "    37: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS \n",
    "    38: 0000000000200dc0     0 NOTYPE  LOCAL  DEFAULT   19 __init_array_end\n",
    "    39: 0000000000200dc8     0 OBJECT  LOCAL  DEFAULT   21 _DYNAMIC\n",
    "    40: 0000000000200db8     0 NOTYPE  LOCAL  DEFAULT   19 __init_array_start\n",
    "    41: 0000000000000714     0 NOTYPE  LOCAL  DEFAULT   17 __GNU_EH_FRAME_HDR\n",
    "    42: 0000000000200fb8     0 OBJECT  LOCAL  DEFAULT   22 _GLOBAL_OFFSET_TABLE_\n",
    "    43: 00000000000006f0     2 FUNC    GLOBAL DEFAULT   14 __libc_csu_fini\n",
    "    44: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTab\n",
    "    45: 0000000000201000     0 NOTYPE  WEAK   DEFAULT   23 data_start\n",
    "    46: 0000000000201010     0 NOTYPE  GLOBAL DEFAULT   23 _edata\n",
    "    47: 00000000000006f4     0 FUNC    GLOBAL DEFAULT   15 _fini\n",
    "    48: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND printf@@GLIBC_2.2.5\n",
    "    49: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@@GLIBC_\n",
    "    50: 0000000000201000     0 NOTYPE  GLOBAL DEFAULT   23 __data_start\n",
    "    51: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__\n",
    "    52: 0000000000201008     0 OBJECT  GLOBAL HIDDEN    23 __dso_handle\n",
    "    53: 0000000000000700     4 OBJECT  GLOBAL DEFAULT   16 _IO_stdin_used\n",
    "    54: 0000000000000680   101 FUNC    GLOBAL DEFAULT   14 __libc_csu_init\n",
    "    55: 0000000000201018     0 NOTYPE  GLOBAL DEFAULT   24 _end\n",
    "    56: 0000000000000540    43 FUNC    GLOBAL DEFAULT   14 _start\n",
    "    57: 0000000000201010     0 NOTYPE  GLOBAL DEFAULT   24 __bss_start\n",
    "    58: 000000000000064a    54 FUNC    GLOBAL DEFAULT   14 main\n",
    "    59: 0000000000201010     0 OBJECT  GLOBAL HIDDEN    23 __TMC_END__\n",
    "    60: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable\n",
    "    61: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@@GLIBC_2.2\n",
    "    62: 00000000000004f0     0 FUNC    GLOBAL DEFAULT   11 _init\n",
    "\n",
    "Version symbols section '.gnu.version' contains 7 entries:\n",
    " Addr: 00000000000003e4  Offset: 0x0003e4  Link: 5 (.dynsym)\n",
    "  000:   0 (*local*)       0 (*local*)       2 (GLIBC_2.2.5)   2 (GLIBC_2.2.5)\n",
    "  004:   0 (*local*)       0 (*local*)       2 (GLIBC_2.2.5)\n",
    "\n",
    "Version needs section '.gnu.version_r' contains 1 entry:\n",
    " Addr: 0x00000000000003f8  Offset: 0x0003f8  Link: 6 (.dynstr)\n",
    "  000000: Version: 1  File: libc.so.6  Cnt: 1\n",
    "  0x0010:   Name: GLIBC_2.2.5  Flags: none  Version: 2\n",
    "\n",
    "Displaying notes found in: .note.ABI-tag\n",
    "  Owner                 Data size\tDescription\n",
    "  GNU                  0x00000010\tNT_GNU_ABI_TAG (ABI version tag)\n",
    "    OS: Linux, ABI: 3.2.0\n",
    "\n",
    "Displaying notes found in: .note.gnu.build-id\n",
    "  Owner                 Data size\tDescription\n",
    "  GNU                  0x00000014\tNT_GNU_BUILD_ID (unique build ID bitstring)\n",
    "    Build ID: 722f29701546260f484c99829446373892245fec\n",
    "\n",
    "```\n",
    "\n",
    "---\n",
    "### References\n",
    "- [C Program Compilation Process](https://medium.com/@earthtojhuang/gcc-main-c-9f6ee2e6894b)\n",
    "- [GCC and Make (Compiling, Linking and Building\n",
    "C/C++ Applications)](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html)\n",
    "- [Journey of a C Program to Linux Executable in 4 Stages](https://www.thegeekstuff.com/2011/10/c-program-to-an-executable/)\n",
    "- [How the compiler works](http://lampwww.epfl.ch/~fsalvi/docs/gcc/www.network-theory.co.uk/docs/gccintro/gccintro_68.html)\n",
    "- [Hello World: C, Assembly, Object File and Executable](https://resources.infosecinstitute.com/hello-world-c-assembly-object-file-and-executable/#gref)\n",
    "- [ELF](https://stevens.netmeister.org/631/elf.html)\n"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": null,
   "metadata": {},
   "outputs": [],
   "source": []
  }
 ],
 "metadata": {
  "kernelspec": {
   "display_name": "Python 3",
   "language": "python",
   "name": "python3"
  },
  "language_info": {
   "codemirror_mode": {
    "name": "ipython",
    "version": 3
   },
   "file_extension": ".py",
   "mimetype": "text/x-python",
   "name": "python",
   "nbconvert_exporter": "python",
   "pygments_lexer": "ipython3",
   "version": "3.6.9"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 2
}