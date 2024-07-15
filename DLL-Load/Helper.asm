.CODE

SimpleCallback PROC

mov rcx, [rdx]
mov rax, [rdx + 8]
xor rdx, rdx
jmp rax

SimpleCallback ENDP

END
