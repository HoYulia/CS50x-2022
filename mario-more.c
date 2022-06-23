#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Запрашиваем высоту пирамиды, при условии [1;8]
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    // Цикл количества строк и столбцов
    for (int i = 0; i < n; i++)
    {
        // Цикл пустых столбиков для пирамиды №1
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        // Цикл столбиков # для пирамиды №1
        for (int z = 0; z < i + 1; z++)
        {
            printf("#");
        }
        printf("  ");
        // Цикл столбиков # для пирамиды №2
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("\n");
    }
}