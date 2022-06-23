#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Запрашиваем высоту пирамиды, при условии [1;8]
    int n;
    while (true)
    {
        n = get_int("Height: ");
        if (n > 0 && n < 9)
        {
            break;
        }
    }
    // Цикл количества строк и столбцов
    for (int i = 0; i < n; i++)
    {
        // Цикл точки в строке
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        // Цикл #
        for (int z = 0; z < i + 1; z++)
        {
            printf("#");
        }
        printf("\n");
    }
}