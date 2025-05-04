import random
import math
from typing import Tuple, List, Set
from time import time


def gcd(a: int, b: int) -> int:
    while b != 0:
        a, b = b, a % b
    return a


def ax_mod_p(a: int, x: int, p: int) -> int:
    return pow(a, x, p)


def eratosthenes_sieve(n: int) -> List[int]:
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(math.isqrt(n)) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False
    return [i for i, prime in enumerate(is_prime) if prime]


def f_generator(bits: int, primes: List[int]) -> Tuple[int, List[int]]:
    f_bits = (bits + 1) // 2
    f_min = 1 << (f_bits - 1)
    f_max = (1 << f_bits) - 1

    f = 1
    f_decomposition = []

    # Первый множитель
    q_initial = random.choice(primes)
    alpha_initial = random.randint(2, 6)
    q_initial_pow = q_initial ** alpha_initial
    f = q_initial_pow
    f_decomposition.append(q_initial)

    max_attempts = 1000
    attempt = 0
    while f < f_min and attempt < max_attempts:
        q = random.choice(primes)
        alpha = random.randint(2, 6)
        q_pow_alpha = q ** alpha
        if f * q_pow_alpha > f_max:
            continue
        f *= q_pow_alpha
        f_decomposition.append(q)
        attempt += 1

    # Уникальные множители
    unique_factors = sorted(list(set(f_decomposition)))
    return f, unique_factors


def r_generator(f_bits: int, f: int) -> int:
    r_bits = f_bits - 1
    r_min = 1 << (r_bits - 1)
    r_max = (1 << r_bits) - 1

    for attempt in range(1000):
        r = random.randint(r_min, r_max)
        if r % 2 != 0:
            r += 1
        if gcd(r, f) == 1 and r < f:
            return r
    raise RuntimeError("Не удалось сгенерировать подходящее R.")


def poklington_test(n: int, f: int, f_factors: List[int], r: int, t: int) -> bool:
    if f <= math.isqrt(n) - 1:
        print(f"Ошибка: F должно быть > sqrt({n}) - 1")
        return False

    seen = set()
    random_aj = []
    while len(random_aj) < t:
        a = random.randint(2, n - 2)
        if a not in seen:
            random_aj.append(a)
            seen.add(a)

    for a in random_aj:
        if ax_mod_p(a, n - 1, n) != 1:
            return False

    for q in f_factors:
        all_one = True
        for a in random_aj:
            x = (n - 1) // q
            if ax_mod_p(a, x, n) != 1:
                all_one = False
                break
        if all_one:
            return False

    return True


def main():
    random.seed(int(time()))

    print("Тест Поклингтона для генерации и проверки простых чисел")
    bits = int(input("Введите требуемый размер числа n в битах: "))
    t = int(input("Введите параметр надежности t (количество проверок): "))

    primes = eratosthenes_sieve(1 << (bits // 2))

    f_bits = (bits + 1) // 2
    f, f_factors = f_generator(f_bits, primes)

    r = r_generator(f_bits, f)

    n = r * f + 1

    is_prime = poklington_test(n, f, f_factors, r, t)

    print(f"Сгенерированное число n = {n}")
    print(f"Разложение F = {f} (множители: {' '.join(map(str, f_factors))})")
    print(f"R = {r}")
    if is_prime:
        print(f"Число {n} , вероятно, простое.")
    else:
        print(f"Число {n} составное.")


if __name__ == "__main__":
    main()