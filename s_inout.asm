section .data
    msg1 db 'S_INPUT: '
    tam_msg1 EQU $-msg1
    msg2 db 'S_OUTPUT: '
    tam_msg2 EQU $-msg2
    endl db 0dh,0ah
    tam_endl EQU $-endl
section .bss
    string_in resb 100
    palavra resb 4
section .text
global _start
_start:
            push eax
            mov eax, 4
            mov ebx, 1
            mov ecx, msg1
            mov edx, tam_msg1
            int 80h
            mov eax, 3
            mov ebx, 0
            mov ecx, string_in
            mov edx, 100
            int 80h
            push string_in
            push palavra
            mov ecx, 6
            push ecx
            call s_input
            pop eax

            push eax
            mov eax, 4
            mov ebx, 1
            mov ecx, msg2
            mov edx, tam_msg2
            int 80h
            push palavra
            mov ecx, 6
            push ecx
            call s_output
            pop eax
acabou:
            mov eax, 4
            mov ebx, 1
            mov ecx, endl
            mov edx, tam_endl
            int 80h
            pop eax
            mov eax, 1
            mov ebx, 0
            int 80h



s_input:
            enter 0,0
            mov ebx, [ebp+16]
            mov eax, [ebp+12]
            mov ecx, [ebp+8]
            xor esi, esi
transcreve:
            cmp ecx, 1
            jl fim_transcreve
            mov dl, [ebx+esi]
            mov [eax+esi], dl
            inc esi
            dec ecx
            jmp transcreve
fim_transcreve:
            mov eax, esi
            leave
            ret 12



s_output:
            enter 0,0
            mov ebx, [ebp+12]
            mov esi, [ebp+8]
            xor ecx, ecx
printa:
            cmp esi, 1
            jl fim_printa
            push ecx
            push ebx
            mov eax, 4
            add ecx, ebx
            mov ebx, 1
            mov edx, 1
            int 80h
            pop ebx
            pop ecx
            dec esi
            inc ecx
            jmp printa
fim_printa:
            mov eax, ecx
            leave
            ret 8
