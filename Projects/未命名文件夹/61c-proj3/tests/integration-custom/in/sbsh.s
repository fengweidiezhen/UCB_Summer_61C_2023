# Set the value of x0 to zero
li x0, 0

# Set the value of sp (stack pointer) to the top of the stack
# Assuming the stack starts at address 0x80000000

li sp 0x80000000


# Initialize data to store
li t0, 0x1234
li t1, 0xABCD
li s1, 0x5678
li s2, 0xEF01

# Store byte
sb t0, 0(sp)   # Store the lowest byte of t0 to the address pointed by sp
sb t1, 1(sp)   # Store the lowest byte of t1 to the next address
sb s1, 2(sp)   # Store the lowest byte of s1 to the next address
sb s2, 3(sp)   # Store the lowest byte of s2 to the next address

# Store half-word
sh t0, 4(sp)   # Store the lowest half-word of t0 to the next address (2 bytes)
sh t1, 6(sp)   # Store the lowest half-word of t1 to the next address
sh s1, 8(sp)   # Store the lowest half-word of s1 to the next address
sh s2, 10(sp)  # Store the lowest half-word of s2 to the next address

# End of program