.CODE

SimpleCallback PROC

mov rbx, rdx
mov rax, [rbx]
mov rcx, [rbx + 8]
mov rdx, [rbx + 16]
mov r8, [rbx + 24]
mov r9, [rbx + 32]
jmp rax

SimpleCallback ENDP

END
