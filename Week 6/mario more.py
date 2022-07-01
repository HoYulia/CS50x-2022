from cs50 import get_int


def main():
    height = get_height()
    for col in range(1, height + 1):
        print_pyramid1(height, col)
        print_pyramid2(height, col)
# Print pyramids


def print_pyramid1(n, col):
    print(" " * (n - col) + "#" * col, end="  ")


def print_pyramid2(n, col):
    print("#" * col, end="\n")
# Input validation


def get_height():
    while True:
        h = get_int("Height: ")
        if 1 <= h <= 8:
            break
    return h


main()