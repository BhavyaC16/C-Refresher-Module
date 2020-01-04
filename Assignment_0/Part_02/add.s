section .text
global add
global display_result
global display_statement
add:
  add rdi, rsi
  mov rax, rdi
  ret

display_statement:
  mov rax, 1
  mov rdi, 1
  mov rsi, msg
  mov rdx, msglen
  syscall
  ret 

display_result:
  mov rdx, rsi
  mov rsi, rdi
  mov rax, 1
  mov rdi, 1
  syscall

  mov rax, 60
  mov rdi, 0
  syscall

section .rodata
  msg: db "The sum is:", 10
  msglen: equ $ - msg