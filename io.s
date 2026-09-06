global outb             ; make the label outb visible outside this file
global inb              ; 
outb:
    push ebp
    mov ebp, esp
    mov al, [ebp+12]
    mov dx, [ebp+8]
    out dx, al
    mov esp,ebp
    pop ebp
    ret
inb:
    push ebp
    mov ebp, esp
    mov dx ,[ebp+8]
    in al,dx
    mov esp,ebp
    pop ebp
    ret