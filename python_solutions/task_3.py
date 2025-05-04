import math
from typing import Tuple

def gcd(a: int, b: int) -> int:
    while b != 0:
        a, b = b, a % b
    return abs(a)

def simplify(numerator: int, denominator: int) -> Tuple[int, int]:
    if denominator == 0:
        raise ZeroDivisionError("Знаменатель не может быть нулём.")

    g = gcd(abs(numerator), abs(denominator))
    numerator //= g
    denominator //= g

    if denominator < 0:
        numerator *= -1
        denominator *= -1

    return numerator, denominator

def compute_numerator(a: int, b: int) -> int:
    if b == 1:
        return 0

    try:
        match a:
            case 1:
                return b
            case 2:
                return b * (b + 1)
            case 3:
                return b * (b * b + 4 * b + 1)
            case 4:
                return b * (b * b * b + 11 * b * b + 11 * b + 1)
            case 5:
                return b * (b * b * b * b + 26 * b * b * b + 66 * b * b + 26 * b + 1)
            case 6:
                return b * ((b**5) + 57 * (b**4) + 302 * (b**3) + 302 * (b**2) + 57 * b + 1)
            case 7:
                return b * ((b**6) + 120 * (b**5) + 1191 * (b**4) + 2416 * (b**3) + 1191 * (b**2) + 120 * b + 1)
            case 8:
                return b * ((b**7) + 247 * (b**6) + 4293 * (b**5) + 15619 * (b**4) + 15619 * (b**3) + 4293 * (b**2) + 247 * b + 1)
            case 9:
                return b * ((b**8) + 502 * (b**7) + 14608 * (b**6) + 88234 * (b**5) + 156190 * (b**4) + 88234 * (b**3) + 14608 * (b**2) + 502 * b + 1)
            case 10:
                return b * ((b**9) + 1013 * (b**8) + 47840 * (b**7) + 455192 * (b**6) + 1310354 * (b**5) + 1310354 * (b**4) + 455192 * (b**3) + 47840 * (b**2) + 1013 * b + 1)
            case _:
                raise ValueError("a должно быть от 1 до 10")
    except OverflowError:
        raise ValueError("Числитель слишком велик для расчёта.")

def main():
    a, b = map(int, input("Введите два целых числа для вычисления суммы ряда: ").split())

    if b == 1:
        print("infinity")
        return

    numerator = compute_numerator(a, b)
    denominator = (b - 1) ** (a + 1)

    sim_num, sim_den = simplify(numerator, denominator)

    print(f"Сумма ряда равна {sim_num}/{sim_den}")

if __name__ == "__main__":
    main()