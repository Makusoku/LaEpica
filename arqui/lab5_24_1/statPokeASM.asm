global  statPokeASM
section     .text

; double -> 64 bits (8 bytes)
;(double* finalStats,double* baseStats,double* instructionValues,double* NTVs,int numPoke)
;   rdi     ->      *finalStats (double)    -> rpta
;   rsi     ->      *baseStats (double)
;   rdx     ->      *instructionValues (double)
;   rcx     ->      *NTVs (double)
;   r8      ->      numPoke (int)

;   finalStats[i] = 5 + (baseStats[i] * 2 + instructionValues[i] * 4) + NTVs[i];

statPokeASM:   
    mov     r11,    5
    cvtsi2sd    xmm5,   r11
    mov     r11,    2
    cvtsi2sd    xmm6,   r11
    mov     r11,    4
    cvtsi2sd    xmm7,   r11 
    
    loop:      
        xorpd	xmm3,	xmm3
        movsd   xmm0,  [rsi]
        movsd   xmm1,  [rdx]
        movsd   xmm2,  [rcx]
        addsd   xmm3,   xmm5
        addsd   xmm3,   xmm2
        mulsd   xmm0,   xmm6
        addsd   xmm3,   xmm0
        mulsd   xmm1,   xmm7
        addsd   xmm3,   xmm1  

        movsd   [rdi],  xmm3
        add     rdi,    8
        add     rsi,    8
        add     rdx,    8
        add     rcx,    8
        dec     r8 
        jnz     loop
    done:
        ret        