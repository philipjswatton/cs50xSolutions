#include <cs50.h>
#include <stdio.h>
#include <math.h>

//American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers

//American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55; and all Visa numbers start with 4


// *** Checksum Calculation ***
//Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
//Add the sum to the sum of the digits that weren’t multiplied by 2.
//If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!




int main(void) {
    //geting the card number
    long cardno = get_long("Card number: "); //uses 'long' data format which allows for large numbers but NOT decimal places
    
    
    //calculating checksum
    if (cardno <= 0) {
        printf("INVALID\n"); //a) filters out a lot of obviously wrong numbers (negative), b) method used to calculate length won't work if 0 is inputted
    } else {
        double length = floor(log10(cardno)) + 1; //number with n digits has value between 10^(n -1) and 10^n, taking log10(abs()) will work for negative numbers, doing log10 and taking the floor gives n - 1; so + 1 will give n
        //needs to be a double for the floor & ceiling calculations later on
        
        //calculating first part of checksum - Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products’ digits together.
        int checkno1 = 0; //initialising a variable which will ultimately give the value of the first half of our checksum
        
        long calcno = cardno; //using another number to do the checksum as we'll be adjusting its value throughout
        calcno /= 10; //uses lack of decimal places for long, means that dividing by 10 just 'removes' the last digit
        
        for(int i = 0; i < floor(length/2); i++) { //floor(length/2) gives half the numbers if even, half rounded down if odd, which is starting from second to last number the amount to use in the checksum
            
            //x % 10 returns the last digit, as everything above will be divisble by 10 and modulo returns the actual 'remainder' that was not divisble by 10. Rest does *2 and adds the value to the check
            if ((calcno % 10) * 2 <= 9) { //if one digit
                checkno1 += (calcno % 10) * 2; 
            } else { //if > one digit (i.e remainder was 5+, max for %10 is 9 so this can be kept reasonably simple)
                //for remainders larger than 9, want to sum their digits for this portion of the checksum
                checkno1 += ((calcno % 10) * 2) / 10; //second number (decimal behaviour of long data type)
                checkno1 += ((calcno % 10) * 2) % 10; //first number
            }
            calcno /= 100; //uses same earlier behaviour re decimal places to skip two places
        }
        
        //calculating second part and adding to part 1 - Add the sum to the sum of the digits that weren’t multiplied by 2.
        int checkno2 = 0;
        
        long calcno2 = cardno; //making a number we do the math with as redefining isn't allowed
        
        for (int j = 0; j < ceil(length/2); j++) { //taking the ceiling gives half again for even numbers, larger number for odd numbers (which is correct if starting from the last number)
            checkno2 += calcno2 %10; //taking the number
            calcno2 /= 100; //skipping two
        }
        
        int check = checkno1 + checkno2; //summing the two portions
        
        
        //2 it's not working on - mastercard (5555555555554444) & visa 4222222222222
        
        
        //part 3 of checksum - If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
        if (check % 10 == 0) {
            
            //final part - verifying the number fits the criteria for one of the three kinds
            
            //american express uses 15-digit numbers, start with 34 or 37
            //MasterCard uses 16-digit numbers, start with 51, 52, 53, 54, or 55
            //Visa uses 13- and 16-digit numbers, all start with 4
            
            
            if (length == 15 && cardno / (10^13) == 34) {
                
            }
            if (cardno >= (340000000000000) && cardno < (350000000000000)) { //can't have decimal places so e.g. 34 * 10^13 instead of 3.4 * 10^14
                printf("AMEX\n");
            } else if (cardno >= (370000000000000) && cardno < (380000000000000)) {
                printf("AMEX\n");
            } else if (cardno >= (5100000000000000) && cardno < (5600000000000000)) {
                printf("MASTERCARD\n");
            } else if (cardno >= (4000000000000) && cardno < (5000000000000)) {
                printf("VISA\n");
            } else if (cardno >= (4000000000000000) && cardno < (5000000000000000)) { //(cardno >= (4 * 10^15) && cardno < (5 * 10^15))
                printf("VISA\n");
            } else {
                printf("INVALID\n");
            }
            
            
        } else {
            printf("INVALID\n");
        }
    }
}





//So that we can automate some tests of your code, we ask that your program’s last line of output be AMEX\n or MASTERCARD\n or VISA\n or INVALID\n