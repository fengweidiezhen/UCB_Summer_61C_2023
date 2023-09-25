.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    add t0 x0 x0 # Sets register t0 to 0
    addi t5 x0 1
    lw t6 0(a0)
    addi t4 x0 0
    blt a1 t5 error
loop_start: 
    slt t1 t0 a1  # Sets t1 to 1 if t0 < len, 0 otherwise
    beq t1 x0, loop_end # Branches to the end if t1 is 1 (t0 >= len)
    slli t2 t0 2  # Sets t2 to t0 * 4 (4 is number of bytes in an integer)
    add t2 a0 t2
    lw t3 0(t2)    # Load arr[t0] into register t3
    blt t6 t3 loop_continue
    addi t0 t0 1
    j loop_start  # Stores this updated value back at arr[t0]

loop_continue:
    addi t6 t3 0  
    addi t4 t0 0
    addi t0 t0 1
    j loop_start
loop_end:
    # Epilogue
    addi a0 t4 0
    jr ra
error:
    addi a0, x0, 36
    jal exit
