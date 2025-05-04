from typing import List


def game_winner(numbers: List[int], m: int) -> int:
    n = len(numbers)

    prefix_sums = [0] * (n + 1)
    for i in range(n):
        prefix_sums[i + 1] = prefix_sums[i] + numbers[i]

    max_sum = [0] * (n + 2)

    for i in range(n - 1, -1, -1):
        max_diff = float('-inf')
        max_k = min(m, n - i)

        for k in range(1, max_k + 1):
            current_sum = prefix_sums[i + k] - prefix_sums[i]
            max_diff = max(max_diff, current_sum - max_sum[i + k])

        max_sum[i] = max_diff

    return 1 if max_sum[0] > 0 else 0


def main():
    print("Введите количество чисел n и допустимое количество вычеркиваемых m:")
    n, m = map(int, input().split())

    print(f"Введите {n} целых чисел:")
    numbers = list(map(int, input().split()))

    result = game_winner(numbers, m)
    print(f"Результат: {result}")


if __name__ == "__main__":
    main()