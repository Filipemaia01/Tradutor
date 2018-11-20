section .data
    msg1 db 'Informe o primeiro numero: '
    tam_msg1 EQU $-msg1
    msg2 db 'hello '
    tam_msg2 EQU $-msg2
    msg3 db 'loop '
    tam_msg3 EQU $-msg3
    endl db 0dh,0ah
    tam_endl EQU $-endl
section .bss
    s_num resb 10
    valor resb 4
section .text
global _start
_start:
            xor eax, eax
            add eax, -987
            mov [valor], eax
            push s_num
            push dword [valor]
            call output
            mov eax, 1
            mov ebx, 0
            int 80h



output:
            enter 0,0
            mov eax, [ebp+8]
            mov edi, [ebp+12]
            xor edx, edx
            xor ecx, ecx
            mov ebx, 10
            cmp eax, 0
            jge divide
            neg eax
            xor esi, esi
            add esi, 1
divide:
            div ebx
            add edx, 0x30
            mov byte [edi + ecx], dl
            mov edx, 0
            cmp eax, 0
            je fim_d
            inc ecx
            jmp divide
fim_d:
            cmp esi, 1
            jne positivo
            inc ecx
            mov byte [edi + ecx], 0x2D

positivo:
            cmp ecx, 0
            jl fimfunc
            push ecx
            mov eax, 4
            mov ebx, 1
            mov esi, ecx
            mov ecx, edi
            add ecx, esi
            mov edx, 1
            int 80h
            pop ecx
            dec ecx
            jmp positivo
fimfunc:
            leave
            ret 4
