#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <time.h>
#include <utility>
#include <algorithm>

using namespace std;

int gcd(int a, int b) { // алгоритм Евклида для эффективного нахождения НОД
    while( b!= 0)
    {
        int r = b;
        b = a % b;
        a = r;
    }

    return a;
}

bool isPrime(int p){
    if (p % 2 == 0 || p % 3 == 0 || p <= 1)
    {
        return false;
    }

    int squareRootN = static_cast<int>(sqrt(p)) + 1;
    int maxI = (squareRootN + 1) / 6;

    for(int i = 1; i < maxI; i++)
    {
        int dividerMinusOne = 6 * i - 1;
        int dividerPlusOne = 6 * i + 1;
            
        if (dividerMinusOne <= squareRootN) 
        {
            if (p % dividerMinusOne == 0) return false;
        }
        if (dividerPlusOne <= squareRootN) 
        {
            if (p % dividerPlusOne == 0) return false;
        }
    }

    return true;
}

int aXmodP (int a, int x, int p){ // быстрое возведение в степень по модулю
    int degree = x % (p - 1); // применение теоремы Ферма
    if(x == 0)
    {
        degree = 1;
    }

    int result = 1;
    for(int i = 1; i <= degree; i++)
    {
        result = result * a;
        result %= p;
    }

    return result;
}

vector<short> DecToBin(int number) {
    vector<short> BinNumbers;
    while (number != 0) 
    {
        BinNumbers.push_back(number % 2);
        number /= 2;
    }
    return BinNumbers;
}

int aXmodPviaLog(int a, int x, int p) {
    if (x == 0) return 1 % p;
    if (p == 1) return 0;

    int maxPowerOfTwo = static_cast<int>(ceil(log2(x)));
    if (pow(2, maxPowerOfTwo) < x) maxPowerOfTwo++;

    vector<int> rowOfAs;
    for (int i = 0; i <= maxPowerOfTwo; ++i) 
    {
        int exponent = 1 << i;
        rowOfAs.push_back(aXmodP(a, exponent, p));
    }

    vector<short> BinX = DecToBin(x);

    int result = 1;
    for (int i = 0; i < static_cast<int>(BinX.size()); ++i)
    {
        if (i < static_cast<int>(rowOfAs.size()) && BinX[i] == 1) 
        {
            result = (result * rowOfAs[i]) % p;
        }
    }

    return result;
}

template<typename T>
bool FermatsCondition(T p, T& k) {
    if(p <= 1 || (p % 2 == 0 && p != 2))
    {
        return false;
    }

    vector<int> aValues = {2, 3, 5, 7, 11, 13, 17, 19, 23};
    if(k > static_cast<int>(aValues.size()))
    {
        k = aValues.size();
    }

    for(int i = 0; i < k; i++) {
        T a = aValues[i];

        if(a >= p) continue;

        if(gcd(p, a) != 1)
        {
            return false;
        }

        if(aXmodP(a, p-1, p) != 1)
        {
            return false;
        }
    }

    return true;
}

bool modValidation(int p, int k) {
    if(!isPrime(p)){
        cerr << endl << "Модуль не является простым числом, попробуйте другой. Модуль обязательно должен быть > 0!" << endl;
        exit(1);
    }
    
    if(!FermatsCondition(p, k)){
        cerr << endl << "Модуль не удовлетворяет условию Ферма, попробуйте другой." << endl;
        exit(1);
    }

    return 1;
}

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


pair< int, vector<int> > FGenerator(int bits, const vector<int>& primeNumbers) {
    int F_bits = (bits / 2) + 1;
    int F_min = 1 << (F_bits - 1);
    int F_max = (1 << F_bits) - 1;

    int F = 1;
    vector<int> FDecomposition; 

    while (true) {
        int q = primeNumbers[rand() % primeNumbers.size()];
        int alpha = rand() % 10 + 1;

        long long q_pow_alpha = 1;
        for (int i = 0; i < alpha; ++i) {
            q_pow_alpha *= q;
        }

        long long new_F = F * q_pow_alpha;
        if (new_F > F_max) {
            continue;
        }

        F = new_F;
        FDecomposition.push_back(q);

        if (F >= F_min && F <= F_max) {
            break;
        }
    }

    sort(FDecomposition.begin(), FDecomposition.end());
    auto last = unique(FDecomposition.begin(), FDecomposition.end());
    FDecomposition.erase(last, FDecomposition.end());

    return make_pair(F, FDecomposition);
}

int RGenerator(int F_bits, int F) {
    int R_bits = F_bits - 1;
    int R_min = 1 << (R_bits - 1);
    int R_max = (1 << R_bits) - 1;

    int R;
    do {
        R = (rand() % (R_max - R_min + 1)) + R_min;

        if (R % 2 != 0)
        {
            R++;
        }
    } while (gcd(R, F) != 1 || R >= F);

    return R;
}

int nCalculation (int F, int R) {
    return R * F + 1;
}

bool PoklingtonTest(int n, int F, vector<int> F_factors, int R, int t) {
    
    if (F <= R || gcd(R, F) != 1) 
    {
        return false;
    }

    vector<int> random_aj;
    set<int> seen;

    while (random_aj.size() < t) 
    {
        int a = 2 + rand() % (n - 2);
        if (seen.find(a) == seen.end()) 
        {
            random_aj.push_back(a);
            seen.insert(a);
        }
    }

    for (int a_j : random_aj)
    {
        if (aXmodPviaLog(a_j, n - 1, n) != 1) 
        {
            return false;
        }
    }

    for (int q_i : F_factors) 
    {
        bool all_one = true;
        for (int a_j : random_aj) 
        {
            if (aXmodPviaLog(a_j, (n - 1) / q_i, n) != 1) 
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
    
    vector<int> primes = EratosthenesSieve(500); // таблица простых чисел до 500
    primes.erase(primes.begin());

    auto F_result = FGenerator(bits, primes);
    int F = F_result.first;
    vector<int> F_factors = F_result.second;

    int F_bits = (bits / 2) + 1;
    int R = RGenerator(F_bits, F);
    int n = nCalculation(F, R);

    bool isPrime = PoklingtonTest(n, F, F_factors, R, t);

    cout << "Сгенерированное число n = " << n << endl;
    cout << "Разложение F = " << F << " (множители: ";
    for (int q : F_factors) {
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