.globl classify

.text
# =====================================
# COMMAND LINE ARGUMENTS
# =====================================
# Args:
#   a0 (int)        argc
#   a1 (char**)     argv
#   a1[1] (char*)   pointer to the filepath string of m0
#   a1[2] (char*)   pointer to the filepath string of m1
#   a1[3] (char*)   pointer to the filepath string of input matrix
#   a1[4] (char*)   pointer to the filepath string of output file
#   a2 (int)        silent mode, if this is 1, you should not print
#                   anything. Otherwise, you should print the
#                   classification and a newline.
# Returns:
#   a0 (int)        Classification
# Exceptions:
#   - If there are an incorrect number of command line args,
#     this function terminates the program with exit code 31
#   - If malloc fails, this function terminates the program with exit code 26
#
# Usage:
#   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>
.globl classify

.text
classify:
    # Error Check
    li t1 5
    bne a0 t1 error_31

    # Prologue
    ebreak
    addi sp sp -56
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw s4 16(sp)
    sw s5 20(sp)
    sw s6 24(sp)
    sw s7 28(sp)
    sw s8 32(sp)
    sw s9 36(sp)
    sw s10 40(sp)
    sw s11 44(sp)
    sw ra 48(sp)
    lw t0 16(a1)
    sw t0 52(sp)
    
    
    mv s0 a0
    mv s1 a1
    mv s2 a2
    
   

    lw s3 4(s1)
    li a0 4
    jal malloc
    beq a0 x0 error_26
    mv s4 a0 

    li a0 4
    jal malloc
    beq a0 x0 error_26
    mv s5 a0 

    mv a2 s5
    mv a1 s4
    mv a0 s3
    jal read_matrix

    mv s3 a0 
    lw s6 8(s1)
    li a0 4
    jal malloc
    beq a0 x0 error_26
    mv s7 a0

    li a0 4
    jal malloc
    beq a0 x0 error_26
    mv s8 a0 

    mv a2 s8 
    mv a1 s7
    mv a0 s6 
    jal read_matrix

    mv s6 a0 
    lw s9 12(s1)
    li a0 4
    jal malloc
    beq a0 x0 error_26
    mv s10 a0 

    li a0 4
    jal malloc
    beq a0 x0 error_26
    mv s11 a0 

    mv a2 s11
    mv a1 s10
    mv a0 s9
    jal read_matrix
    mv s9 a0 
    lw t1 0(s4)
    lw t2 0(s11)
    mul t0 t1 t2
    mv s1 t0 
    li t1 4

    mul t0 t0 t1
    mv a0 t0
    jal malloc
    beq a0 x0 error_26
    mv s0 a0

    lw a5 0(s11)
    lw a4 0(s10)
    lw a1 0(s4)
    lw a2 0(s5)

    mv a6 s0
    mv a3 s9
    mv a0 s3
    jal matmul

    # Compute h = relu(h)
    mv a1 s1
    mv a0 s0
    jal relu

    # Compute o = matmul(m1, h)
    lw t2 0(s11)
    lw t1 0(s7)
    mul t0 t1 t2
    li t1 4
    mul t1 t1 t0
    mv a0 t1
    jal malloc
    beq a0 x0 error_26
    mv s1 a0

    mv a0 s6
    lw a1 0(s7)
    lw a2 0(s8)
    mv a3 s0
    lw t0 0(s4)
    mv a4 t0
    lw t0 0(s11)
    mv a5 t0
    mv a6 s1
    jal matmul

    # Write output matrix o
    lw t1 52(sp)
    mv a0 t1
    mv a1 s1
    lw t1 0(s7)
    mv a2 t1
    lw t1 0(s11)
    mv a3 t1
    jal write_matrix
    # jal free
    mv a0 s0
    jal free

    # Compute and return argmax(o)
    mv a0 s1
    lw t1 0(s11)
    lw t0 0(s7)
    mul a1 t0 t1
    jal argmax
    mv s0 a0

    # If enabled, print argmax(o) and newline
    ebreak
    beq x0 s2 print
    
return:
    mv a0 s1
    jal free
    mv a0 s3
    jal free
    mv a0 s4
    jal free
    mv a0 s5
    jal free
    mv a0 s6
    jal free
    mv a0 s7
    jal free
    mv a0 s8
    jal free
    mv a0 s9
    jal free
    mv a0 s10
    jal free
    mv a0 s11
    jal free

    mv a0 s0
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw s4 16(sp)
    lw s5 20(sp)
    lw s6 24(sp)
    lw s7 28(sp)
    lw s8 32(sp)
    lw s9 36(sp)
    lw s10 40(sp)
    lw s11 44(sp)
    lw ra 48(sp)
    addi sp sp 56
    ebreak
    ret

print:
    ebreak
    mv a0 s0
    jal print_int

    li a0 '\n'
    jal print_char


    j return 


error_26: # malloc error
    addi a0 x0 26
    j exit

error_31: # command error
    addi a0 x0 31
    j exit



