#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <utility>

using namespace std;

vector<int> EratosthenesSieve(int n) {
    vector<bool> isPrime(n + 1, true);

    isPrime[0] = isPrime[1] = false;

    for(int i = 2; i * i <=  n; i++)
    {
        if(isPrime[i])
        {
            for(int j = i * i; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    vector<int> primeNumbers;
    for(int i = 2; i <= n; i++)
    {
        if(isPrime[i])
        {
            primeNumbers.push_back(i);
        }
    }

    return primeNumbers;
}

int FGenerator(int bits, vector<int> primeNumbers) {
    int F_bits = (bits / 2) + 1;
    int F_min = 1 << (F_bits - 1);
    int F_max = (1 << F_bits) - 1;

    int F = 1;
    vector<int> FDecomposition;

    while (true)
    {
        int q = primeNumbers[ rand() % primeNumbers.size() ];
        int alpha = rand() % 10 + 1;

        if(static_cast<long long>(F) * pow(q, alpha))
        {
            continue;
        }

        F *= pow(q, alpha);
        FDecomposition.push_back(q);

        if(F >= F_min && F <= F_max)
        {
            break;
        }
    }

    return F;
}

pair< int, vector< pair<int, int> > > FGenerator(int bits, const vector<int>& primeNumbers) {
    int F_bits = (bits / 2) + 1; // Размер F на 1 бит больше половины bits
    int F_min = 1 << (F_bits - 1);
    int F_max = (1 << F_bits) - 1;

    int F = 1; // Используем long long для избежания переполнения
    vector<pair<int, int>> FDecomposition; // (простое, степень)

    while (true) {
        int q = primeNumbers[rand() % primeNumbers.size()];
        int alpha = rand() % 10 + 1;

        // Вычисляем q^alpha
        long long q_pow_alpha = 1;
        for (int i = 0; i < alpha; ++i) {
            q_pow_alpha *= q;
        }

        // Проверяем, не превысит ли F * q_pow_alpha F_max
        long long new_F = F * q_pow_alpha;
        if (new_F > F_max) {
            continue; // Пропускаем, если слишком большое
        }

        F = new_F;
        FDecomposition.push_back({q, alpha});

        // Проверяем диапазон F
        if (F >= F_min && F <= F_max) {
            break;
        }
    }

    // Возвращаем F и его разложение
    return make_pair(F, FDecomposition);
}

int nCalculation (int F) {
    int n;

    int R = rand();

    return n;
}

int main() {

    srand(time(NULL));

    cout << "Тест Миллера для генерации и проверки простых чисел\n";
    int bits;
    cout << "Введите требуемый размер числа n в битах: ";
    cin >> bits;
    
    int t;
    cout << "Введите параметр надежности t (количество проверок): ";
    cin >> t;
    
    vector<int> primes = EratosthenesSieve(500); // таблица простых чисел до 500

    return 0;
}