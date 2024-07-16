.CODE

SimpleCallback PROC

    mov rbx, rdx
    mov rax, [rbx]
    mov rcx, [rbx + 8h]
    mov rdx, [rbx + 10h]
    xor r8, r8
    mov r9, [rbx + 18h]
    mov r10, [rbx + 20h]
    mov [rsp+30h], r10
    mov r10, 3000h
    mov [rsp+28h], r10
    jmp rax

SimpleCallback ENDP

END
