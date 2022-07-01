from cs50 import get_int


def main():
    height = get_height()
    for col in range(1, height + 1):
        print_symb(height, col)
# Print symbols


def print_symb(n, col):
    print(" " * (n - col) + "#" * col, end="\n")
# Input validation


def get_height():
    while True:
        h = get_int("Height: ")
        if 1 <= h <= 8:
            break
    return h


main()