# Simple Assembly Code for RISC-V CPU Testing

# Arithmetic Instructions
add x1, x2, x3        # x1 = x2 + x3
sub x4, x5, x6        # x4 = x5 - x6
mul x7, x8, x9        # x7 = x8 * x9

# Logical Instructions
and x10, x11, x12     # x10 = x11 & x12
or x13, x14, x15      # x13 = x14 | x15
xor x16, x17, x18     # x16 = x17 ^ x18

# Conditional Branching Instructions
beq x19, x20, label1  # Branch to label1 if x19 == x20
bne x21, x22, label2  # Branch to label2 if x21 != x22
blt x23, x24, label3  # Branch to label3 if x23 < x24

# Memory Access Instructions
lw x25, 100(x26)      # Load word from memory at address (x26 + 100) into x25
sw x27, -50(x28)      # Store word from x27 into memory at address (x28 - 50)

# Unconditional Jump
j label4              # Jump to label4 unconditionally

# Define Labels
label1:
    # Your code here

label2:
    # Your code here

label3:
    # Your code here

label4:
    # Your code here

# End of Assembly Code