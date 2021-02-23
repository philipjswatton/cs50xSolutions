#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

//index = 0.0588 * L - 0.296 * S - 15.8

//L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text

/*
Implement your program in a file called readability.c in a ~/pset2/readability directory.

Your program must prompt the user for a string of text (using get_string).

Your program should count the number of letters, words, and sentences in the text. You may assume that a letter is any lowercase character
from a to z or any uppercase character from A to Z, any sequence of characters separated by spaces should count as a word, and that any occurrence
of a period, exclamation point, or question mark indicates the end of a sentence.

Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.

If the resulting index number is 16 or higher (equivalent to or greater than a senior undergraduate reading level), your program should output
"Grade 16+" instead of giving the exact index number. If the index number is less than 1, your program
should output "Before Grade 1".
*/

int main(void)
{
    //get user input
    string text = get_string("Text: ");

    //count n of letters
    int letters = count_letters(text);

    //count n of words
    int words = count_words(text);
    
    //count n of sentences
    int sentences = count_sentences(text);
    
    float L = ((float)letters/words) * 100;
    float S = ((float)sentences/words) * 100;
    
    float index = 0.0588 * L - 0.296 * S - 15.8;
    index = round(index);
    
    if(index < 16 && index > 0)
    {
        printf("Grade %0.0f\n", index);
    } else if(index < 1)
    {
        printf("Before Grade 1\n");
    } else
    {
        printf("Grade 16+\n");
    }
}





// function to count number of letters
int count_letters(string text)
{
    int letters = 0;
    for(int i = 0, n = strlen(text); i < n; i++) //syntactic sugar - declaring stringlength inside the loop to avoid time/efficiency trade offs
    {
        if(isalpha(text[i]))
        {
            letters++;
        }
    }
    return letters;
}


//function to count number of words
//assumes no spaces at the beginning or end of sentences, no double spaces, etc
//so just counts number of spaces and adds 1
int count_words(string text)
{
    int words = 1;
    for(int i = 0, n = strlen(text); i < n; i++)
    {
        if(isspace(text[i]))
        {
            words++;
        }
    }
    return words;
}



//function to count sentences
//not worrying about 'secondary boundary selection', e.g. Mr. Smith had toast. (1 sentence in reality, 2 in this program)
//for now, considering any sequence ending with ".", "!" or "?" to be a sentence

int count_sentences(string text)
{
    int sentences = 0;
    for(int i = 0, n = strlen(text); i < n; i++)
    {
        if(text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentences++;
        }
    }
    return sentences;
}