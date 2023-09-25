.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
#   - If malloc returns an error,
#     this function terminates the program with error code 26
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fread error or eof,
#     this function terminates the program with error code 29
# ==============================================================================
read_matrix:
	# Prologue
    addi sp, sp, -20
    sw s0 0(sp)
    sw s1 4(sp)
    sw s2 8(sp)
    sw s3 12(sp)
    sw ra 16(sp)
    
    mv s0 a0
    mv s1 a1 
    mv s2 a2 
    mv a1 x0
    jal fopen


    addi t0 x0 -1
    beq a0 t0 error_2

    mv s0 a0 
    addi a2 x0 4
    add a1 x0 s1
    jal fread 

    addi t0 x0 4
    bne t0 a0 error_4
    mv a0 s0
    mv a1 s2
    addi a2 x0 4
    jal fread 

    addi t0 x0 4
    bne t0 a0 error_4
    lw t0 0(s1)
    lw t1 0(s2)

    mul s3 t0 t1
    addi t4 x0 4
    mul s3 s3 t4
    mv a0 s3
    jal malloc

    beq a0, x0, error_1
    mv s1 a0
    mv a1 a0
    mv a0 s0 
    mv a2 s3
    jal fread

    bne a0 s3 error_4
    mv a0 s0 
    jal fclose
    addi t0 x0 -1
    beq a0 t0 error_3
    mv a0 s1

	# Epilogue
    lw s0 0(sp)
    lw s1 4(sp)
    lw s2 8(sp)
    lw s3 12(sp)
    lw ra 16(sp)
    addi sp, sp, 20
	ret
    
error_1: # malloc_error
    addi a0 x0 26
    j exit
    
error_2: # fopen_error
    addi a0 x0 27
    j exit
    
error_3: # fclose_error
    addi a0 x0 28
    j exit
    
error_4: # fread_error
    addi a0 x0 29
    j exit
    
