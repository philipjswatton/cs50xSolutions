import cs50

# Main function
def main():

    # Get height from user, make sure it's greater than 0 but less than 9
    while True:
        height = cs50.get_int("Height: ")
        if (height > 0 and height < 9):
            break

    #Printing time
    for i in (range(0, height)):
        space(i, height)
        hashes(i, height)
        print("  ", end="")
        hashes(i, height)
        print()


# Function for printing spaces
def space(i, height):
    for j in range(0, height-i-1):
        print(" ", end="")

# Function for printing hashes
def hashes(i, height):
    for j in range(height, height+i+1):
        print("#", end="")

# Run
main()