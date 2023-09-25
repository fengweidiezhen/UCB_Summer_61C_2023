.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the number of elements to use is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
    # Prologue
    add t0 x0 x0 # Sets register t0 to 0
    addi t4 x0 1
    blt a2 t4 error_1
    blt a3 t4 error_2
    blt a4 t4 error_2
    addi t6 x0 0  # set t6 to be the sum
loop_start:
    slt t1 t0 a2  # Sets t1 to 1 if t0 < len, 0 otherwise
    beq t1 x0 loop_end # Branches to the end if t1 is 1 (t0 >= len)

    mul t1 t0 a3
    slli t2 t1 2  # Sets t2 to t1 * strike1 * 4 (4 is number of bytes in an integer)
    add t2 a0 t2
    lw t3 0(t2)    # Load arr1[t0*strike1] into register t3

    mul t1 t0 a4
    slli t2 t1 2
    add t2 a1 t2
    lw t4 0(t2)    # Load arr2[t0*strike2] into register t4

    mul t5 t3 t4
    add t6 t6 t5
    addi t0 t0 1
    j loop_start

loop_end:
    addi a0 t6 0
    # Epilogue
    jr ra
    
error_1:
    addi a0, x0, 36
    jal exit
error_2:
    addi a0, x0, 37
    jal exit
