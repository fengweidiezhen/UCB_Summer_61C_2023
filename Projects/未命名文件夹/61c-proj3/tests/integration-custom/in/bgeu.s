addi t0 x0 -0        # Set t0 to 10
addi t1 x0 -10        # Set t1 to 20
addi s0 x0 5         # Set s0 to 5
addi s1 x0 5         # Set s1 to 5

# Compare t0 and t1 using bgeu
bgeu t0, t1, greater_or_equal
# If t0 < t1, execute this block
addi a0 x0 1         # Set return value to 1 (true)
j end

greater_or_equal:
    # If t0 >= t1, execute this block
    addi a0 x0 0         # Set return value to 0 (false)

end:
    # Exit the program
    addi a7 x0 10





