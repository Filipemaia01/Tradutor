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
    num resb 32
    valor resb 4
section .text
global _start
_start:
            mov eax, 4
            mov ebx, 1
            mov ecx, msg1
            mov edx, tam_msg1
            int 80h
            mov eax, 3
            mov ebx, 0
            mov ecx, num
            mov edx, 4
            int 80h
            mov ecx, eax
            dec ecx
            xor esi, esi
            xor edi, edi
            xor eax, eax
            mov [valor], eax
            mov ebx, num
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
            mov dl, [num + esi]
            sub dl, 0x30
            cbw
            cwde
            mov eax, [valor]
            mov ebx, eax
            add eax, ebx
            add eax, ebx
            add eax, ebx
            add eax, ebx
            sal eax, 1
            add eax, edx
            mov [valor], eax
            push eax
            push ebx
            push ecx
            push edx
            mov eax, 4
            mov ebx, 1
            mov ecx, msg3
            mov edx, tam_msg3
            int 80h
            pop edx
            pop ecx
            pop ebx
            pop eax
            inc esi
            dec ecx
            jmp inicio
fim:
            cmp edi, 1
            jnz positivo
negativo:
            mov eax, [valor]
            neg eax
            mov [valor], eax
positivo:
            mov ecx, [valor]
            add ecx, 16
repeticoes:
            cmp ecx, 0
            je acabou
            push ecx
            mov eax, 4
            mov ebx, 1
            mov ecx, msg2
            mov edx, tam_msg2
            int 80h
            pop ecx
            dec ecx
            jmp repeticoes

acabou:
            mov eax, 1
            mov ebx, 0
            int 80h
