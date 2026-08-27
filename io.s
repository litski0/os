global outb             ; make the label outb visible outside this file
global inb              ;
outb:
    mov al, [esp+8]
    mov dx, [esp+4]
    out dx, al
    ret
inb:
    mov dx ,[esp+4]
    in al,dx
    ret