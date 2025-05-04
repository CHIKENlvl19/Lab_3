import random
import math
from typing import List


def eratosthenes_sieve(limit: int) -> List[int]:
    is_prime = [True] * (limit + 1)
    is_prime[0] = is_prime[1] = False

    for i in range(2, int(math.isqrt(limit)) + 1):
        if is_prime[i]:
            for j in range(i * i, limit + 1, i):
                is_prime[j] = False

    return [i for i, prime in enumerate(is_prime) if prime]


def ax_mod_p(a: int, x: int, p: int) -> int:
    if x == 0:
        return 1 % p
    degree = x % (p - 1)
    if degree == 0 and x != 0:
        degree = p - 1
    return pow(a, degree, p)


def diemitko_test(p: int, q: int) -> bool:
    if ax_mod_p(2, p - 1, p) != 1:
        return False
    exponent = (p - 1) // q
    if ax_mod_p(2, exponent, p) == 1:
        return False
    return True


def prime_generator_gost(t: int, q: int) -> int:
    while True:
        pow_t_minus_1 = 1 << (t - 1)
        numerator = pow_t_minus_1 - 1
        base_N = numerator // q

        xi = random.random()
        N = math.ceil(xi * (pow_t_minus_1 / q)) + base_N
        if N % 2 != 0:
            N += 1

        for u in range(0, 1000, 2):
            p_candidate = (N + u) * q + 1
            if p_candidate >= (1 << t):
                continue
            if diemitko_test(p_candidate, q):
                return p_candidate

        print("Не удалось найти подходящее p, пробуем еще раз.")


def main():
    print("Генерация простого числа по ГОСТ Р 34.10-94")
    t = int(input("Введите необходимое количество бит для генерации числа: "))

    primes = eratosthenes_sieve(500)
    q_size = (t + 1) // 2
    q = random.choice(primes)
    print(f"Выбранное q = {q}")

    p = prime_generator_gost(t, q)
    print(f"Сгенерированное простое число p = {p}")
    print(f"Двоичное представление: {bin(p)[2:]}")


if __name__ == "__main__":
    main()