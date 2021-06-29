.model tiny
org 100h

.data
msg db "Program completed successfully!$"

.code
mov al, 80h 
mov dx, 3FBh  
out dx, al 
mov dx, 3F8h   
mov al, 00h 
out dx, al  
mov al, 0Ch 
mov dx, 3F9h    
out dx, al  
mov dx, 3FBh    
mov al, 00000011b 
out dx, al  
mov dx,3FCH 
mov al, 00001011b 
out dx, al 
mov DX, 3F9h    
mov al, 0   
out dx, al
mov dx, 3F8h    
mov al, 0AAh 
out dx, al  
mov ah,9
lea dx, msg
int 21h
ret
