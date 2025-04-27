#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>

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