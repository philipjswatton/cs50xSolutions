import cs50
import math

def main():

    # Get card number via user input
    num = cs50.get_int("Card number: ")

    # Length of the number
    digits = len(str(num))

    # Number should be length 13, 15, or 16
    if (digits not in [13,15,16]):
        print("INVALID")
        return 0

    # Run algo - multiply every other digit from 2nd to last by 2, sum up the *digits* of the product. Sum other digits. Add these sums. If the last digit of the output is 0, it's a valid number
    temp = num
    prodsum = 0
    restsum = 0
    double = False #start off not doubling digit

    for i in range(0, digits):
        if double == False:
            restsum += temp % 10
            double = True
            temp = math.floor(temp / 10)
        else:
            newprod = (temp % 10) * 2
            if len(str(newprod)) == 1:
                prodsum += (temp % 10) * 2
            else:
                for j in range(0, len(str(newprod))):
                    prodsum += newprod % 10
                    newprod = math.floor(newprod / 10)
            double = False
            temp = math.floor(temp / 10)

    check = prodsum + restsum

    if check % 10 != 0:
        print("INVALID")
        return 0

    # Check start of card:
    # - american express uses 15-digit numbers, start with 34 or 37
    # - MasterCard uses 16-digit numbers, start with 51, 52, 53, 54, or 55
    # - Visa uses 13- and 16-digit numbers, all start with 4
    num = str(num)
    start = num[:2]

    if start in ["34", "37"] and digits == 15:
        print("AMEX")
    elif start in map(str, range(51,56)) and digits == 16:
        print("MASTERCARD")
    elif start[0] == "4" and digits in [13,16]:
        print("VISA")
    else:
        print("INVALID")

    return 0

# Run program
main()