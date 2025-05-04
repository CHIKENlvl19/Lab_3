import math
import numpy as np
from typing import List, Tuple

T = 60

def coffee_cooling(Tk: float, Tsr: float, r: float) -> List[float]:
    coffee = []
    for _ in range(T):
        coffee.append(Tk)
        Tk -= r * (Tk - Tsr)
    return coffee

def linear_regression(coffee: List[float]) -> Tuple[float, float]:
    n = len(coffee)
    time_points = list(range(n))

    sum_xy = sum(x * y for x, y in zip(time_points, coffee))
    sum_x = sum(time_points)
    sum_y = sum(coffee)
    sum_xx = sum(x * x for x in time_points)

    slope = (n * sum_xy - sum_x * sum_y) / (n * sum_xx - sum_x * sum_x)
    intercept = (sum_y - slope * sum_x) / n

    return slope, intercept

def pearson_correlation(coffee: List[float]) -> float:
    n = len(coffee)
    time_points = list(range(n))

    avg_x = sum(coffee) / n
    avg_y = (n - 1) / 2.0

    sum_xy = sum((x - avg_x) * (y - avg_y) for x, y in zip(coffee, time_points))
    sum_xx = sum((x - avg_x) ** 2 for x in coffee)
    sum_yy = sum((y - avg_y) ** 2 for y in time_points)

    try:
        correlation = sum_xy / math.sqrt(sum_xx * sum_yy)
    except ZeroDivisionError:
        correlation = 0.0

    return -correlation

def main():
    Tk = float(input("Введите температуру кофе: "))
    Tsr = float(input("Введите температуру окружающей среды: "))
    r = float(input("Введите коэффициент остывания: "))

    coffee_data = coffee_cooling(Tk, Tsr, r)

    print("\nТаблица остывания кофе")
    print("_______________________________")
    print("|  время, м |  температура, С |")
    print("--------------------------------")

    for i in range(T):
        print(f"|  {i:6.3f}   |    {coffee_data[i]:8.3f}     |")
        print("-------------------------------")

    slope, intercept = linear_regression(coffee_data)
    print(f"\nАппроксимирующая прямая: y = {slope:.3f} * x + {intercept:.3f}")

    correlation = pearson_correlation(coffee_data)
    print(f"Коэффициент корреляции: {correlation:.3f}")

if __name__ == "__main__":
    main()