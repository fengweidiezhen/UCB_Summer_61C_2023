.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:
    addi t0 x0 1
    blt a1 t0 Error
    blt a2 t0 Error
    blt a4 t0 Error
    blt a5 t0 Error
    bne a2 a4 Error
    # Error checks
    addi sp sp -32
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw s6 24(sp)
    sw ra 28(sp)
    mv s0 a0
    mv s1 a1
    mv s2 a2
    mv s3 a3
    mv s4 a4
    mv s5 a5
    mv s6 a6

    # Prologue
    addi t1 x0 0 # j
    addi t2 x0 0 # i
outer_loop_start:
    beq t2 s1 outer_loop_end # i < a1

inner_loop_start:
    beq t1 s5 inner_loop_end # j < a5
    add t3 x0 s2
    mul t3 t3 t2
    slli t3 t3 2
    add t3 t3 s0
    mv a0 t3

    slli t4 t1 2
    add t4 t4 s3
    mv a1 t4
    mv a2 s2
    
    addi a3 x0 1
    mv a4 s5

    addi sp sp -8
    sw t1 0(sp)
    sw t2 4(sp) 

    jal ra dot

    lw t1 0(sp)
    lw t2 4(sp)
    addi sp sp 8
    
    lw ra 28(sp)

    add t6 x0 s5
    mul t6 s5 t2
    add t6 t6 t1
    slli t6 t6 2
    add t6 t6 s6
    sw a0 0(t6) 

    # multiplication
    
    addi t1 t1 1

    j inner_loop_start
inner_loop_end:
    addi t1 x0 0
    addi t2 t2 1
    j outer_loop_start

outer_loop_end:
    
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s5 20(sp)
    lw s6 24(sp)
    lw ra 28(sp)
    addi sp sp 32
    # Epilogue
    jr ra
Error:
    addi a0 x0 38
    j exit
