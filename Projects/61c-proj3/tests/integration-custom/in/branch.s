addi t0 x0 1
addi t2 x0 3
addi t3 x0 3
addi t4 x0 4
start:
    addi t0 t0 1
    addi t3 x0 1
    addi t4 x0 1
    blt t0 t2 start
    beq t3 t3 equal
equal:
    bge t3 t3 bigequal
    addi t2 x0 3
    addi t2 x0 3
bigequal:
    bgeu t3 t3 bigequalu
    addi t2 x0 3
    addi t2 x0 3
bigequalu:
    bltu t3 t4 lessthanu
    addi t2 x0 3
    addi t2 x0 3
lessthanu:
    bne t3 t3 notequal
    addi t2 x0 3
    addi t2 x0 3
notequal:
    addi t2 x0 3
    addi t2 x0 3

    
    

