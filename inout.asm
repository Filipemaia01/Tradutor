section .data
    msg1 db 'INPUT: '
    tam_msg1 EQU $-msg1
    msg2 db 'hello '
    tam_msg2 EQU $-msg2
    msg3 db 'loop '
    tam_msg3 EQU $-msg3
    endl db 0dh,0ah
    tam_endl EQU $-endl
section .bss
    num resb 12
    s_num resb 12
    valor resb 4
    aux resb 4
section .text
global _start
_start:
            mov eax, 9
            push eax
            mov eax, 4
            mov ebx, 1
            mov ecx, msg1
            mov edx, tam_msg1
            int 80h
            mov eax, 3
            mov ebx, 0
            mov ecx, num
            mov edx, 12
            int 80h
            push num
            push eax
            call input
            mov dword [valor], eax
            pop eax

            push eax
            push s_num
            push dword [valor]
            call output
            pop eax
acabou:
            mov eax, 1
            mov ebx, 0
            int 80h



input:
            enter 0,0
            mov ecx, [ebp+8]
            dec ecx
            xor esi, esi
            xor edi, edi
            xor eax, eax
            mov ebx, [ebp+12]
            cmp byte [ebx], 0x2D
            jnz inicio
            dec ecx
            inc esi
            inc edi
inicio:
            cmp ecx, 1
            jl fim
converte:
            xor edx, edx
            mov dl, [ebx + esi]
            cbw
            cwde
            sub dl, 0x30
            push ebx
            mov ebx, eax
            add eax, ebx
            add eax, ebx
            add eax, ebx
            add eax, ebx
            sal eax, 1
            add eax, edx
            pop ebx
            inc esi
            dec ecx
            jmp inicio
fim:
            cmp edi, 1
            jnz positivo
negativo:
            neg eax
positivo:
            leave
            ret 8



output:
            enter 0,0
            mov eax, [ebp+8]
            mov edi, [ebp+12]
            xor edx, edx
            xor ecx, ecx
            xor esi, esi
            mov ebx, 10
            cmp eax, 0
            jge divide
            neg eax
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
            jne positivo_out
            inc ecx
            mov byte [edi + ecx], 0x2D
positivo_out:
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
            jmp positivo_out
fimfunc:
            leave
            ret 8
