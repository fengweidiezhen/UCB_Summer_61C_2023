.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
    # Prologue
    add t0 x0 x0 # Sets register t0 to 0
    addi t6 x0 0
    addi t5 x0 1
    blt a1 t5 error
loop_start: 
    slt t1 t0 a1  # Sets t1 to 1 if t0 < len, 0 otherwise
    beq t1 x0, loop_end # Branches to the end if t1 is 1 (t0 >= len)
    slli t2 t0 2  # Sets t2 to t0 * 4 (4 is number of bytes in an integer)
    add t3, a0, t2
    lw t4 0(t3)    # Load arr[t0] into register t4
    bge t4 x0 loop_continue
    sw t6 0(t3)    # Stores this updated value back at arr[t0]

loop_continue:
    addi t0, t0, 1  # Increments t0 to move to the next element
    jal x0,loop_start
loop_end:
    

    # Epilogue
    jr ra
error:
    addi a0, x0, 36
    jal exit
    
