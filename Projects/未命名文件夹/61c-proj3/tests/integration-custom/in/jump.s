jal ra start
addi t0 x0 1
start:
    addi t1 x0 1
    jal ra end
    addi t1 t1 1
end:
    addi t1 t1 2
