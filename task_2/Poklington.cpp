#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <time.h>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long ll;

ll gcd(ll a, ll b) {
    while (b != 0) 
    {
        ll r = b;
        b = a % b;
        a = r;
    }

    return a;
}

ll aXmodP(ll a, ll x, ll p) {
    ll result = 1;
    a %= p;
    while (x > 0) 
    {
        if (x % 2 == 1)
        {
            result = (result * a) % p;
        }
        a = (a * a) % p;
        x /= 2;
    }

    return result;
}

vector<ll> EratosthenesSieve(int n) {
    vector<bool> isPrime(n + 1, true);

    isPrime[0] = isPrime[1] = false;

    for(int i = 2; i * i <= n; i++)
    {
        if(isPrime[i])
        {
            for(int j = i * i; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }

    vector<ll> primeNumbers;
    for(int i = 2; i <= n; i++)
    {
        if(isPrime[i])
        {
            primeNumbers.push_back(i);
        }
    }

    return primeNumbers;
}


pair< ll, vector<ll> > FGenerator(int bits, const vector<ll>& primeNumbers) {
    int F_bits = (bits + 1) / 2; 
    ll F_min = 1LL << (F_bits - 1);
    ll F_max = (1LL << F_bits) - 1;

    ll F = 1;
    vector<ll> FDecomposition;

    ll q_initial = primeNumbers[rand() % primeNumbers.size()];
    int alpha_initial = rand() % 5 + 2;
    ll q_initial_pow = 1;

    for (int i = 0; i < alpha_initial; i++)
    {
        q_initial_pow *= q_initial;
    }
    F = q_initial_pow;
    FDecomposition.push_back(q_initial);

    int attempts = 0;
    const int MAX_ATTEMPTS = 1000;

    while (attempts++ < MAX_ATTEMPTS && F < F_min) 
    {
        ll q = primeNumbers[rand() % primeNumbers.size()];
        int alpha = rand() % 5 + 2;

        ll q_pow_alpha = 1;
        for (int i = 0; i < alpha; ++i) 
        {
            q_pow_alpha *= q;
        }

        if (F * q_pow_alpha > F_max) 
        {
            continue;
        }

        F *= q_pow_alpha;
        FDecomposition.push_back(q);
    }

    set<ll> unique_factors(FDecomposition.begin(), FDecomposition.end());
    return {F, vector<ll>(unique_factors.begin(), unique_factors.end())};
}

ll RGenerator(int F_bits, ll F) {
    int R_bits = F_bits - 1;
    ll R_min = 1LL << (R_bits - 1);
    ll R_max = (1LL << R_bits) - 1;

    for (int attempt = 0; attempt < 1000; attempt++)
    {
        ll R = ( rand() % (R_max - R_min + 1) ) + R_min;

        if (R % 2 != 0)
        {
            R++;
        }

        if (gcd(R, F) == 1 && R < F)
        {
            return R;
        }
    }

    cerr << "Не удалось сгенерировать подходящее R." << endl;
    exit(1);
}

bool PoklingtonTest(ll n, ll F, vector<ll> F_factors, int R, int t) {

    if (F <= sqrt(n) - 1)
    {
        cerr << "Ошибка, F должно быть > sqrt(" << n <<  ") - 1" << endl;
        return false; 
    }

    vector<ll> random_aj;
    set<ll> seen;

    while (random_aj.size() < t) 
    {
        ll a = 2 + rand() % (n - 2);
        if (seen.find(a) == seen.end()) 
        {
            random_aj.push_back(a);
            seen.insert(a);
        }
    }

    for (ll a_j : random_aj)
    {
        if (aXmodP(a_j, n - 1, n) != 1) 
        {
            return false;
        }
    }

    for (ll q_i : F_factors) 
    {
        bool all_one = true;
        for (ll a_j : random_aj) 
        {
            ll x = (n - 1) / q_i;
            if (aXmodP(a_j, x ,n) != 1) 
            {
                all_one = false;
                break;
            }
        }
        if (all_one) 
        {
            return false;
        }
    }

    return true;
}

int main() {

    srand(time(NULL));

    cout << "Тест Поклингтона для генерации и проверки простых чисел\n";
    int bits;
    cout << "Введите требуемый размер числа n в битах: ";
    cin >> bits;
    
    int t;
    cout << "Введите параметр надежности t (количество проверок): ";
    cin >> t;
    
    vector<ll> primes = EratosthenesSieve(1 << (bits / 2)); // таблица простых чисел до 500
 

    int F_bits = (bits + 1) / 2;

    auto [F, F_factors] = FGenerator(F_bits, primes);

    ll R = RGenerator(F_bits, F);
    ll n = R * F + 1;

    bool isPrime = PoklingtonTest(n, F, F_factors, R, t);

    cout << "Сгенерированное число n = " << n << endl;
    cout << "Разложение F = " << F << " (множители: ";
    for (ll q : F_factors) {
        cout << q << " ";
    }
    cout << ")\nR = " << R << endl;

    if(isPrime)
    {
        cout << "Число " << n << " , вероятно, простое." << endl;
    } else {
        cout << "Число " << n << " составное." << endl;
    }

    return 0;
}