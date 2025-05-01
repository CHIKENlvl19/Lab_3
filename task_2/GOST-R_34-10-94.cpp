#include <iostream>
#include <vector>
#include <bitset>
#include <random>
#include <cstdint>

using namespace std;

typedef uint64_t ll;

vector <ll> EratospeheneSieve (int t) {
    vector <bool> isPrime(t + 1, true);

    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i * i <= t; i++) 
    {
        if (isPrime[i])
        {
            for (int j = i * i; j <= t; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    vector<ll> PrimeNumbers;
    for (int i = 2; i <= t; i++)
    {
        if (isPrime[i])
        {
            PrimeNumbers.push_back(i);
        }
    }

    return PrimeNumbers;
}

ll aXmodP (ll a, ll x, ll p) {
    int degree = x % (p - 1); // применение теоремы Ферма
    
    if(x == 0)
    {
        degree = 1;
    }

    ll result = 1;
    for(int i = 1; i <= degree; i++)
    {
        result = result * a;
        result %= p;
    }

    return result;
}

bool DiemitkoTest (ll p, ll q) {

    if (aXmodP(2, p - 1, p) != 1)
    {
        return false;
    }

    ll exponent = (p - 1)/ q;
    if (aXmodP(2, exponent , p) == 1)
    {
        return false;
    }

    return true;
}

int PrimeGeneratorGOST(int t, int q) {
    mt19937 rng(time(NULL));
    uniform_real_distribution <double> dist(0.0, 1.0);
    double xi = dist(rng);

    while (true)
    {
        ll pow_t_minus_one = 1 << (t - 1);
        ll numerator = pow_t_minus_one - 1;
        ll base_N = numerator / q;

        ll N = static_cast<ll>(ceil(xi * (pow_t_minus_one / static_cast<double>(q)))) + base_N;
        if (N % 2 != 0)
        {
            N++;
        }

        for (ll u = 0; u < 1000; u += 2)
        {
            int p_candidate = (N + u) * q + 1;

            if (p_candidate >= (1ULL << t))
            {
                cerr << "Число вышло за даипазон 2^t." << endl; 
                break;
            }

            if (DiemitkoTest(p_candidate, q))
            {
                return p_candidate;
            }
        }
        cerr << "Не удалось найти подходящее p, пробуем еще раз." << endl;
    }
}

int main() {

    cout << "Введите необходимое количество бит для генерации числа: ";
    ll t;
    cin >> t;

    vector <ll> primes = EratospeheneSieve(500);

    ll q_size = (t + 1) / 2;
    ll q = rand() % primes.size();

    cout << "Выбранное q = " << q << endl;

    ll p = PrimeGeneratorGOST(t, q);

    cout << "Сгенерированное простое число p = " << p << endl;
    cout << "Двоичное представление: " << bitset<32>(p) << endl;

    return 0;
}