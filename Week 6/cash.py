from cs50 import get_float


# Total number of coins to give the customer
def get_change(total):
    quarters, dimes, nickels, pennies = 0, 0, 0, 0
    while total > 0:
        if total >= 25:
            total -= 25
            quarters += 1
        elif 10 <= total < 25:
            total -= 10
            dimes += 1
        elif 5 <= total < 10:
            total -= 5
            nickels += 1
        else:
            total -= 1
            pennies += 1
    return quarters + dimes + nickels + pennies


# Ask how many cents the customer is owed
while True:
    cents = get_float("Change owed : ")
    if 0 < cents:
        break

print(get_change(cents * 100))