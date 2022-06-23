#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{

    // Проверка ключа на количество аргументов (2: название программы + ключ)
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Ключ состоит из десятичных чисел
    for (int i = 0, l = strlen(argv[1]); i < l; i++)
    {
        if (isdigit(argv[1][i]) == false)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    // Конвертация ключа из строки в число
    int key = atoi(argv[1]);
    // Шифр текста
    string plain = get_string("plaintext: ");

    for (int j = 0, l = strlen(plain); j < l; j++)
    {
        // Перебор и шифр маленькх букв
        if (isalpha(plain[j]) && islower(plain[j]))
        {
            plain[j] = (plain[j] - 'a' + key) % 26 + 'a';
        }
        // Перебор и шифр больших букв
        if (isalpha(plain[j]) && isupper(plain[j]))
        {
            plain[j] = (plain[j] - 'A' + key) % 26 + 'A';
        }
    }
    printf("ciphertext: %s\n", plain);
    return 0;
}