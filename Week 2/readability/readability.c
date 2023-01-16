#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Ask user for an input
    string text = get_string("Text: ");

    //uso funtions to know letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    //convert values into float
    float L = ((float)letters / (float)words) * 100;
    float S = ((float)sentences / (float)words) * 100;
    // apply the formula
    float index = 0.0588 * L - 0.296 * S - 15.8;

    int new_index = round(index);

    // print the grade of the text
    if (new_index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (new_index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", new_index);
    }

}


int count_letters(string text)
{
    // count letters
    int letters = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (((int)text[i] >= 65 && (int)text[i] <= 90) || ((int)text[i] >= 97 && (int)text[i] <= 122))
        {
            letters += 1;
        }
    }

    return letters;
}

int count_words(string text)
{
    //count words, initial word = 1
    int words = 1;

    for (int i = 0; i < strlen(text); i++)
    {
        if ((int)text[i] == ' ')
        {
            words += 1;
        }
    }

    return words;
}

int count_sentences(string text)
{
    // count sentences
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
    }

    return sentences;
}