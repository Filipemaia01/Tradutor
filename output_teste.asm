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
            mov eax, 12
            mov [s_num], eax
            xor edx, edx
            mov ebx, 10
            xor ecx, ecx
divide:
            div ebx
            add edx, 0x30
            mov [s_num + ecx], dl
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
            mov ecx, s_num
