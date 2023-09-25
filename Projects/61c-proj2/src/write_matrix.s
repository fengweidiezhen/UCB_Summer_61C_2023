.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fwrite error or eof,
#     this function terminates the program with error code 30
# ==============================================================================
write_matrix:

	# Prologue
    addi sp sp -28
    sw ra 0(sp)
    sw s0 4(sp)
    sw s1 8(sp)
    sw s2 12(sp)
    sw s3 16(sp)
    sw s4 20(sp)
    sw s5 24(sp)
    
    
    mv s1 a1
    mv s2 a2
    mv s3 a3
    li a1 1 
    jal fopen

    li t1 -1
    beq t1 a0 error_27
    mv s0 a0 

    li a0 4
    jal malloc
    mv s4 a0

    li a0 4
    jal malloc
    mv s5 a0

    sw s2 0(s4) 
    sw s3 0(s5) 
    
    li a2 1
    li a3 4
    mv a0 s0
    mv a1 s4
    jal fwrite

    li t0 1
    bne t0 a0 error_30
    
    li a2 1
    li a3 4
    mv a0 s0
    mv a1 s5
    jal fwrite

    li t0 1
    bne t0 a0 error_30
    
    mul a2 s2 s3
    mv a0 s0
    mv a1 s1
    li a3 4
    jal fwrite
    mul t0 s2 s3
    bne t0 a0 error_30
    
    mv a0 s0
    jal fclose
    bne a0 x0 error_28

    mv a0 s4
    jal free
    mv a0 s5
    jal free
    
	# Epilogue
    lw ra 0(sp)
    lw s0 4(sp)
    lw s1 8(sp)
    lw s2 12(sp)
    lw s3 16(sp)
    lw s4 20(sp)
    lw s5 24(sp)
    addi sp sp 28
	ret
    
error_27: # fopen_error
    addi a0 x0 27
    j exit

error_28: # fclose_error
    addi a0 x0 28
    j exit
     
error_30: # fwrite_error
    addi a0 x0 30
    j exit
    
