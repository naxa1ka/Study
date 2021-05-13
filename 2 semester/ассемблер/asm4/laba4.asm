org 100h
mov cx, 9

cycle:
    cmp [x], 0
    je y2
    jg y3
    
    mov ax, [a]
    imul [b]
    mov bx, [c]
    sub ax, bx
    mov bx, [x]
    xor dx, dx
    cwd
    idiv bx
    push ax
    jmp end_ass
end_ass:
    pop ax
    push cx
    call OutInt
    call print_nl
    inc [x]
    pop cx
    loop cycle
    jmp end_end
    
y2:
    mov ax, [a]
    imul [b]
    mov bx, [d]
    sub bx, ax
    mov ax, bx
    push ax 
    jmp end_ass
    
y3:
    mov bx, [c]
    add bx, [d]
    push bx
    mov ax, [x]
    mov bx, [b]
    imul bx
    mov bx, [a]
    imul bx
    pop bx
    xor dx, dx
    cwd
    idiv bx
    push ax
    jmp end_ass
    end_end: 
    mov ah, 1
    int 21h
ret


OutInt proc
       test    ax, ax
       jns     oi1
       
       mov  cx, ax
       mov     ah, 02h
       mov     dl, '-'
       int     21h
       mov  ax, cx
       neg     ax

oi1:  
        xor     cx, cx
        mov     bx, 10
oi2:
        xor     dx,dx
        div     bx

        push    dx
        inc     cx

        test    ax, ax
        jnz     oi2

        mov     ah, 02h
oi3:
        pop     dx

        add     dl, '0'
        int     21h

        loop    oi3
        
        ret
 
OutInt endp

print_nl proc 
    pusha 
    mov ah, 2
    mov dl, 0Dh
    int 21h  
    mov dl, 0Ah
    int 21h   
    popa      
    ret
endp


a dw 14
b dw 2 
c dw -25
d dw -6
x dw -6 


