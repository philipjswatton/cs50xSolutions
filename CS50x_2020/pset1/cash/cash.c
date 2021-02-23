#include <cs50.h>
#include <stdio.h>
#include <math.h>

//prototype code for functions:
int get_owed(void);


//Use get_float to get the user’s input and printf to output your answer. Assume that the only coins available are quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢)
int main(void) {
    int c = get_owed(); //get change owed in cents from function written below
    int n = 0; //initialize number of coins to give back at 0
    
    //quarters
    if (c / 25 >= 1) {
        do
        {
            c = c - 25; //take one quarter out
            n++; //add 1 to the number of coins to return
        }
        while (c / 25 >= 1);
    }
    
    //dimes
    if (c / 10 >= 1) {
        do
        {
            c = c - 10; //take one dime out
            n++; //add 1 to the number of coins to return
        }
        while (c / 10 >= 1);
    }
    
    //nickles
    if (c / 5 >= 1) {
        do
        {
            c = c - 5; //take one nickle out
            n++; //add 1 to the number of coins to return
        }
        while (c / 5 >= 1);
    }
    
    //pennies
    if (c / 1 >= 1) {
        do
        {
            c = c - 1; //take one penny out
            n++; //add 1 to the number of coins to return
        }
        while (c / 1 >= 1);
    }
    
    printf("%i\n", n);
}



//full function for getting value of changed owed and converting to cents
int get_owed(void) {
    float d; //initialize dollars
    do
    {
        d = get_float("Change owed: "); //gets value in dollars format, e.g. 9.00 would be $9, 0.9 would be 90 cents
    }
    while (d < 0);
    int c = round(d * 100); //converts dollars to cents, ensures proper rounding
    return c;
}



