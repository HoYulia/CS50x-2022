#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ограничение на количество цифр в карте [от 1 до 16 цифр]
    long long card;
    do
    {
        card = get_long_long("Number:\n");
    }
    while (card < 1 || card > 9999999999999999);

    // Создаем переменные счетчики
    int count = 0;
    int sum1 = 0;
    int sum2 = 0;
    int ls_dig = 0;
    int ls_dig1 = 0;
    int ls_dig2 = 0;
    long long copy_card = card;
    long long copy_card2 = card;
    long long company_id = card;

    // Количество цифр в номере карты
    while (card > 0)
    {
        ls_dig = card % 10;
        count++;
        card = card / 10;
    }
    // Сумма вторых цифр карты (с права на лево)
    for (int j = 0; j < count / 2; j++)
    {
        ls_dig1 = copy_card % 100 / 10 * 2;
        if (ls_dig1 > 9)
        {
            ls_dig1 = ls_dig1 / 10 + ls_dig1 % 10;
        }
        sum1 = sum1 + ls_dig1;
        copy_card = copy_card / 100;
    }
    // Сумма первых цифр карты (с права на лево)
    for (int i = 0; i < count / 2 + 1; i++)
    {
        ls_dig2 = copy_card2 % 10;
        sum2 = sum2 + ls_dig2;
        copy_card2 = copy_card2 / 100;
    }
    int sum = sum1 + sum2;
    // Первые две цифры карты
    while (company_id >= 99)
    {
        company_id /= 10;
    }

    // Определение платежной системы
    if (count == 16 && (51 <= company_id && company_id <= 55) && (sum % 10 == 0))
    {
        printf("MASTERCARD\n");
    }
    else if ((count == 13 || count == 16) && (company_id / 10 == 4) && (sum % 10 == 0))
    {
        printf("VISA\n");
    }
    else if (count == 15 && (company_id == 34 || company_id == 37) && (sum % 10 == 0))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }

}