#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

float count_letters(string text);
float count_words(string text);
float count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

// Расчет индекса index = 0.0588 * L - 0.296 * S - 15.8
    float l = letters / words * 100;
    float s = sentences / words * 100;
    int index = round(0.0588 * l - 0.296 * s - 15.8);
    if (index < 1)
 {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}
// Подсчет количества букв в тексте
float count_letters(string text)
{
    int count_l = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count_l++;
        }
    }
    return count_l;
}
// Подсчет слов в тексте
float count_words(string text)
{
    int count_w = 1;
    for (int j = 0, n = strlen(text); j < n; j++)
    {
        if (text[j] == 32)
        {
            count_w ++;
        }
    }
    return count_w;
}
// Подсчет предложений в тексте
float count_sentences(string text)
{
    int count_s = 0;
    for (int z = 0, n = strlen(text); z < n; z++)
    {
        if (text[z] == 33 || text[z] == 46 || text[z] == 63)
        {
            count_s++;
        }
    }
    return count_s;
}