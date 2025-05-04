import math

def line():
    print("-------------------")

def value_print(x, y):
    print(f"| {x:.1f} | {y:.2f} |")

def main():
    print("Таблица значений функции:")
    line()
    print("|   x   |    y    |")
    line()

    x = -6.0
    while x <= -2.0:
        y = -0.992 * (x + 3.5) ** 2 + 2.2
        value_print(x, y)
        x += 1.0

    while x <= 2.0:
        try:
            y = -math.sqrt(4 - x**2)
        except ValueError:
            y = float('nan')
        value_print(x, y)
        x += 1.0

    while x <= 8.0:
        try:
            y = math.log(x, 2) - 1
        except ValueError:
            y = float('nan')
        value_print(x, y)
        x += 1.0

    while x <= 10.0:
        y = -x + 9
        value_print(x, y)
        x += 1.0

    line()

if __name__ == "__main__":
    main()