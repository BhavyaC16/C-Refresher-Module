section .text
extern printf
global add
global display_result
add:
  add rdi, rsi
  mov rax, rdi
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