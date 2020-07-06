#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int countLetters(string text);
int countSentences(string text);
int countWords(string text);
int calculateGrade(int L, int S, int W);

int main(void)
{
    string text = get_string("Text: ");

    //Your program should count the number of letters, words, and sentences in the text.
    // couting letters
    printf("Total # of letters: %i\n", countLetters(text));

    // counting words
    printf("Total # of words: %i\n", countWords(text));

    // counting sentences
    printf("Total # of sentences: %i\n", countSentences(text));

    // calculating the grade
    int grade = calculateGrade(countLetters(text), countSentences(text), countWords(text));
    if (grade < 2)
    {
        printf("Before Grade 1\n");
    } else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }


}


// function that return the number of letters in a text
int countLetters(string text)
{
    int count = 0;
    for(int i = 0, n = strlen(text); i < n; i++)
    {
        // only letters from a to z and from A to Z
        if((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z') )
        {
            count++;
        }
    }
    return count;
}

// function that return the number of sentences
int countSentences(string text){
    int count = 0;
    for(int i = 0, n = strlen(text); i < n; i++)
    {
        // a sentence finishes with '.', '?'', '!', ':' or ';'.
        if(text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
        }
    }
    return count;
}

int countWords(string text)
{
    int count = 0;
    for(int i = 0, n = strlen(text); i < n; i++)
    {
        // I need to treat double space
        // a word finishes with '.', '?'', '!', ':', ';' or ' '.
        // if(text[i] == '.' || text[i] == '?' || text[i] == '!' || text[i] == ':' || text[i] == ';' || text[i] == ' ')
        // {
        //     if(text[i-1] != '.' || text[i-1] != '?' || text[i-1] != '!' || text[i-1] != ':' || text[i-1] != ';' || text[i-1] != ' ')
        //     {
        //         count++;
        //     }
        // }
        if(text[i] == ' ')
        {
            count++;
        }
    }
    return ++count;
}


int calculateGrade(int L, int S, int W)
{
    float avgLettersPer100Words =  ((float) L / (float)W) * 100;
    float avgSentencesPer100Words = ((float) S / (float)W) * 100;

   return round(0.0588 * avgLettersPer100Words - 0.296 * avgSentencesPer100Words - 15.8);

}