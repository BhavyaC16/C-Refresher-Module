## Combining C and Assembly Language Programs
C Programming Language Refresher Module for Operating Systems
Assignment 0.2<br>
__Submitted by__: Bhavya Chopra<br>
__Roll Number__: 2018333<br>
__E-mail__: bhavya18333@iiitd.ac.in

---

### Calling ASM routine from C program

To make the routines `add` and `display_result` present in the assembly code `add.s` available for the C program, they have been marked `global` in the `.text` section as follows:
```asm
section .text
  global add
  global display_result

```
Also, the function headers for these have been marked as `extern` to aid the compiler with the linking process:
```c
extern int add(int a, int b);
extern void display_result(char * result, int len);

```
---

### x86-64 Register Calling 

When any ASM routine is called from the C program, the actual arguments of the routine call are stored in the general registers and the stack. If there are 6 or less arguments, they are passed to the registers. In case of more than 6 arguments, the first six are passed to the registers, and the remaining are pushed to the program's stack. The first six arguments are stored in the registers as follows:
- `rdi`: first argument
- `rsi`: second argument
- `rdx`: third argument
- `rcx`: fourth argument
- `r8`: fifth argument
- `r9`: sixth argument

The `add` routine takes the two integer values input by the user as arguments, and stores them in the `rdi` and `rsi` registers. After adding `rsi` to `rdi`, the value stored in `rdi` is moved to `rax` for returning to the C program as follows:
```asm
add:
  add rdi, rsi
  mov rax, rdi
  ret
```
Similarly, the `display_result` routine takes the display string and its length as arguments, and stores them in registers `rdi` and `rsi`. For making the syscall for write, the string length in `rsi` is moved to `rdx`, the result string in `rdi` is moved to `rsi`, `rax` is changed to `1` to indicate `sys_write`, and `rdi` is changed to `1` to indicate `STDOUT` as follows:
```asm
  mov rdx, rsi
  mov rsi, rdi
  mov rax, 1
  mov rdi, 1
  syscall
```
For the exist syscall after displaying the result, `rax` is changed to `60` to indicate `sys_exit`, `rdi` is changed to `0` to indicate successful execution as follows:
```asm
  mov rax, 60
  mov rdi, 0
  syscall
```
---

### Resources
 - [Hello world in Linux x86-64 assembly](https://jameshfisher.com/2018/03/10/linux-assembly-hello-world/)
 - [WikiBooks: X86 Assembly/Interfacing with Linux](https://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux#syscall)
 - [LINUX SYSTEM CALL TABLE FOR X86 64](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)
 - [Calling assembly functions from C and C++](http://www.keil.com/support/man/docs/armclang_intro/armclang_intro_lmi1470147220260.htm)
