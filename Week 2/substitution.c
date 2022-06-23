#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Проверка ключа на количество аргументов (2: название программы + ключ)
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // Проверка ключа на количество букв (26шт.)
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // Проверка ключа на соответсвие алфавиту
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]) == false)
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }
    // Проверка ключа на дубликаты букв
    int count = 0;
    int total = 0;
    for (int i = 0; i < 26; i++)
    {
        count = 0;
        for (int k = 0; k < 26; k++)
        {
            if ((tolower(argv[1][i]) != tolower(argv[1][k])) && (i != k))
            {
                count++;
            }
        }
        if (count == 25)
        {
            total++;
        }
    }
    if (total != 26)
    {
        printf("Key must not contain reapited characters. %i\n", total);
        return 1;
    }
    // Шифрование текста
    string text = get_string("plaintext: ");

    for (int z = 0, n = strlen(text); z < n; z++)
    {
        if (islower(text[z]) && isalpha(text[z]))
        {
            //Нахождение координат элементов text согласно алфавиту ASCII и замена новым элементом из key
            text[z] = tolower(argv[1][text[z] - 'a']);
        }
        else if (isupper(text[z]) && isalpha(text[z]))
        {
            text[z] = toupper(argv[1][text[z] - 'A']);
        }
    }
    printf("ciphertext: %s\n", text);
}