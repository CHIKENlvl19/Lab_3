import random
import math
import time

def eratosthenes_sieve(n: int) -> list[int]:
    """Решето Эратосфена до n."""
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(math.isqrt(n)) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False
    return [i for i, prime in enumerate(is_prime) if prime]

def is_prime(p: int) -> bool:
    """Проверка на простоту методом деления на 6k ± 1."""
    if p <= 1 or p % 2 == 0 or p % 3 == 0:
        return False
    root = math.isqrt(p) + 1
    max_i = (root + 1) // 6

    for i in range(1, max_i + 1):
        d1 = 6 * i - 1
        d2 = 6 * i + 1
        if d1 <= root and p % d1 == 0:
            return False
        if d2 <= root and p % d2 == 0:
            return False
    return True

def ax_mod_p(a: int, x: int, p: int) -> int:
    """Быстрое возведение в степень по модулю."""
    degree = x % (p - 1)
    result = 1
    for _ in range(degree):
        result = (result * a) % p
    return result

def dec_to_bin(number: int) -> list[int]:
    """Перевод числа в двоичное представление."""
    binary = []
    while number != 0:
        binary.append(number % 2)
        number //= 2
    return binary

def ax_mod_p_via_log(a: int, x: int, p: int) -> int:
    """Возведение в степень по модулю через двоичное разложение."""
    if x == 0:
        return 1 % p
    if p == 1:
        return 0

    max_power_of_two = int(math.log2(x)) + 1
    if 2 ** max_power_of_two < x:
        max_power_of_two += 1

    row_of_as = []
    for i in range(max_power_of_two + 1):
        exponent = 1 << i
        row_of_as.append(ax_mod_p(a, exponent, p))

    bin_x = dec_to_bin(x)
    result = 1
    for i in range(len(bin_x)):
        if i < len(row_of_as) and bin_x[i] == 1:
            result = (result * row_of_as[i]) % p
    return result

def gcd(a: int, b: int) -> int:
    """Алгоритм Евклида."""
    while b != 0:
        a, b = b, a % b
    return a

def fermat_condition(p: int, k: int) -> bool:
    """Проверка условия Ферма для оснований из списка."""
    a_values = [2, 3, 5, 7, 11, 13, 17, 19, 23]
    if k > len(a_values):
        k = len(a_values)

    for i in range(k):
        a = a_values[i]
        if a >= p:
            continue
        if gcd(a, p) != 1:
            return False
        if ax_mod_p(a, p - 1, p) != 1:
            return False
    return True

def mod_validation(p: int, k: int) -> bool:
    """Проверка модуля на простоту и условие Ферма."""
    if not is_prime(p):
        print("Модуль не является простым, попробуйте другой.")
        exit(1)
    if not fermat_condition(p, k):
        print("Модуль не удовлетворяет условию Ферма, попробуйте другой.")
        exit(1)
    return True

def m_generator(bits: int, primes: list[int]) -> int:
    """Генерация m из случайных простых чисел."""
    target_min = 1 << (bits - 2)
    target_max = (1 << (bits - 1)) - 1

    m = 1
    while True:
        q = primes[random.randint(0, len(primes) - 1)]
        alpha = random.randint(1, 10)
        new_m = m * (q ** alpha)
        if new_m > target_max:
            continue
        m = new_m
        if target_min <= m <= target_max:
            break
    return m

def n_calculation(m: int) -> int:
    """Вычисление n = 2m + 1."""
    return 2 * m + 1

def n_minus_one_decomposition(n: int) -> list[int]:
    """Разложение n-1, убираем степени 2."""
    n_minus_one = n - 1
    while n_minus_one % 2 == 0:
        n_minus_one //= 2

    decomposition = []
    i = 3
    while i * i <= n_minus_one:
        while n_minus_one % i == 0:
            decomposition.append(i)
            n_minus_one //= i
        i += 2
    if n_minus_one > 1:
        decomposition.append(n_minus_one)

    return sorted(list(set(decomposition)))

def miller_test(n: int, decomposition: list[int], t: int) -> bool:
    """Тест Миллера на простоту."""
    random_aj = []
    for _ in range(t):
        a = random.randint(2, n - 1)
        if a not in random_aj:
            random_aj.append(a)

    # Шаг 2: Проверка a^x ≡ 1 mod n
    for a in random_aj:
        if ax_mod_p_via_log(a, n - 1, n) != 1:
            return False

    # Шаг 3: Проверка для каждого множителя
    for q in decomposition:
        all_fail = True
        for a in random_aj:
            if ax_mod_p_via_log(a, (n - 1) // q, n) != 1:
                all_fail = False
                break
        if all_fail:
            return False
    return True

def euler_phi(n: int) -> float:
    """Вычисление функции Эйлера φ(n)."""
    if n == 1:
        return 1
    result = n
    i = 2
    while i * i <= n:
        if n % i == 0:
            while n % i == 0:
                n //= i
            result -= result // i
        i += 1
    if n > 1:
        result -= result // n
    return result

def main():
    """Основная функция."""
    random.seed(time.time())
    print("Тест Миллера для генерации и проверки простых чисел")
    bits = int(input("Введите требуемый размер числа n в битах: "))
    t = int(input("Введите параметр надежности t (количество проверок): "))

    primes = eratosthenes_sieve(500)
    m = m_generator(bits, primes)
    n = n_calculation(m)
    decomposition = n_minus_one_decomposition(n)
    is_prime = miller_test(n, decomposition, t)

    phi_n_minus_1 = euler_phi(n - 1)
    probability_error = (phi_n_minus_1 / (n - 1)) ** t * 100

    print(f"Сгенерированное число n = {n}")
    print(f"Разложение n-1 = {n-1}: {' '.join(map(str, decomposition))}")
    if is_prime:
        print(f"Число {n} вероятно простое")
    else:
        print(f"Число {n} составное")
        print(f"Вероятность ошибки: {probability_error:.2f}%")

if __name__ == "__main__":
    main()