.globl f # this allows other files to find the function f
.data
output: .word   6, 61, 17, -38, 19, 42, 5
.text
# f takes in two arguments:
# a0 is the value we want to evaluate f at
# a1 is the address of the "output" array (defined above).
# The return value should be stored in a0
f:
    # Your code here
    la t0 output
    mv t1 a0
    addi t1 t1 3
    slli t2 t1 2
    add t2 t2 t0
    lw t3 0(t2)
    mv a0 t3
    mv a1 t0
    # This is how you return from a function. You'll learn more about this later.
    # This should be the last line in your program.
    jr ra
