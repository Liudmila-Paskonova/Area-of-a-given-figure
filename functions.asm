Global f1
Global f2
Global f3

section .text

f1: ; (e^x)+2
    FINIT
    push ebp
    mov ebp, esp
    sub esp, 8
    fld qword[ebp+8]
    fldl2e
    fmulp
    fist dword[esp]
    fild dword[esp]
    fsub st1, st0
    fxch st1
    f2xm1
    fld1
    faddp
    fscale
    fstp st1
    fld1
    fld1
    faddp
    faddp
    add esp, 8
    mov esp, ebp
    pop ebp
    ret 
  
f2: ; -(1/x)
    FINIT
    push ebp
    mov ebp, esp
    fld1
    fld qword[ebp+8]
    fdivp
    fchs
    mov esp, ebp
    pop ebp
    ret 
      
f3: ; -2/3*(x+1)
    FINIT
    push ebp
    mov ebp, esp
    fld qword[ebp+8]
    fld1
    faddp
    fld1
    fld1
    faddp
    fmulp
    fld1
    fld1
    fld1
    faddp
    faddp
    fdivp
    fchs
    mov esp, ebp
    pop ebp
    ret 
