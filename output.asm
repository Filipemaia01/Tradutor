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
    s_num resb 32
    valor resb 4
section .text
global _start
_start:
            xor eax, eax
            xor edx, edx
            add eax, 50921
            mov [s_num], al
            mov ebx, 10
            xor ecx, ecx
divide:
            div ebx
            add edx, 0x30
            mov [s_num + ecx], dl
            mov edx, 0
            cmp eax, 0
            je fim_d
            inc ecx
            jmp divide
fim_d:
            cmp ecx, 0
            jl fimfunc
            push ecx
            mov eax, 4
            mov ebx, 1
            mov edi, ecx
            mov ecx, s_num
            add ecx, edi
            mov edx, 1
            int 80h
            pop ecx
            dec ecx
            jmp fim_d
fimfunc:
            mov eax, 1
            mov ebx, 0
            int 80h
