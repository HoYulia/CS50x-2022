from cs50 import get_int
import re

# Check count of digit in card
card = get_int("Number: ")
while card < 1 or card > 9999999999999999:
    card = get_int("Number: ")

# Count digit in card
count = len(str(card))

# Decimal conversation


def get_dec_num(n):
    return n // 10 + n % 10
    

# Luhn’s Algorithm
copy_card = card
sum1, sum2 = 0, 0

while copy_card > 0:
    l_dig1 = copy_card % 100 // 10 * 2
    l_dig2 = copy_card % 10
    if l_dig1 > 9:
        l_dig1 = get_dec_num(l_dig1)
    sum1 += l_dig1
    sum2 += l_dig2
    copy_card = copy_card // 100
sum = sum1 + sum2

# First two digits of the card
company_id = str(card)[:2]

# Card verification
if str(sum).endswith("0"):
    if count == 16 and (51 <= int(company_id) <= 55):
        print("MASTERCARD")
    elif count in [13, 16] and re.search("^4", company_id):
        print("VISA")
    elif count == 15 and re.findall("34|37", company_id):
        print("AMEX")
else:
    print("INVALID")