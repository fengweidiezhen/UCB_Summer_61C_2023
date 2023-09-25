addi t0 x0 10
addi t1 x0 -9
start:
    addi t0 t0 -1
    bgeu t0 t1 start
addi s0 x0 1