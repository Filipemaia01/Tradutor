section .data
    msg1 db 'C_INPUT: '
    tam_msg1 EQU $-msg1
    msg2 db 'C_OUTPUT: '
    tam_msg2 EQU $-msg2
section .bss
    char_in resb 1
section .text
global _start
_start:
            push eax
            mov eax, 4
            mov ebx, 1
            mov ecx, msg1
            mov edx, tam_msg1
            int 80h

            push char_in
            call c_input
            pop eax

            push eax
            mov eax, 4
            mov ebx, 1
            mov ecx, msg1
            mov edx, tam_msg1
            int 80h

            push char_in
            call c_output
            pop eax

            mov eax, 1
            mov ebx, 0
            int 80h



c_input:
            enter 0,0
            mov eax, 3
            mov ebx, 0
            mov ecx, [ebp+8]
            mov edx, 1
            int 80h
            mov eax, 1
            leave
            ret 4


c_output:
            enter 0,0
            mov eax, 4
            mov ebx, 1
            mov ecx, [ebp+8]
            mov edx, 1
            int 80h
            mov eax, 1
            leave
            ret 4
