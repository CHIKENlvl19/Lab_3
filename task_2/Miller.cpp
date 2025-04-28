#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <algorithm>
#include <iomanip>

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

int gcd(int a, int b) { // алгоритм Евклида для эффективного нахождения НОД
    while( b!= 0)
    {
        int r = b;
        b = a % b;
        a = r;
    }

    return a;
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

int mGenerator(int bits, vector<int> primeNumbers) {
    int target_min = 1 << (bits - 2);
    int target_max = ( 1 << (bits - 1) ) - 1;

    int m = 1;
    vector<int> mDecomposition;

    while(true)
    {
        int q = primeNumbers[ rand() % primeNumbers.size() ];
        int alpha = rand() % 10 + 1;

        if(static_cast<long long>(m) * pow(q, alpha) > target_max) 
        {
            continue;
        }

        m *= pow(q, alpha);
        mDecomposition.push_back(q);


        if(m >= target_min && m <= target_max)
        {
            break;
        }
    }

    return m;
}

int nCalculation(int m) {
    return 2 * m + 1;
}

vector<int> nMinusOneDecomposition(int n) {
    vector<int> nDecomposition;

    int n_minus_one = n - 1;

    while (n_minus_one % 2 == 0) // уберем все двойки из делителей, они нам не нужжна
    {
        n_minus_one /= 2;
    }

    for(int i = 3; i <= sqrt(n_minus_one); i += 2)
    {
        while(n_minus_one % i == 0){
            nDecomposition.push_back(i);
        n_minus_one /= i;
        }
    }

    if(n_minus_one > 1)
    {
        nDecomposition.push_back(n_minus_one);
    }

    sort(nDecomposition.begin(), nDecomposition.end()); //сортировка для unique, он работает только с отсортированными
    auto last = unique(nDecomposition.begin(), nDecomposition.end());
    nDecomposition.erase(last, nDecomposition.end());

    return nDecomposition;
}

bool MillerTest(int n, vector<int>& nDecomposition, int t) {
    vector<int> random_aj;
    for (int i = 0; i < t; ++i) 
    {
        random_aj.push_back(2 + rand() % (n - 2)); // Генерация a_j в диапазоне [2, n-1]
    }

    // Шаг 2: Проверка a_j^(n-1) ≡ 1 mod n
    for (int a_j : random_aj) 
    {
        if (aXmodPviaLog(a_j, n - 1, n) != 1) 
        {
            return false; // n составное
        }
    }

    // Шаг 3: Проверка для каждого q_i
    for (int q_i : nDecomposition) 
    {
        bool all_fail = true;
        for (int a_j : random_aj) 
        {
            if (aXmodPviaLog(a_j, (n - 1) / q_i, n) != 1) 
            {
                all_fail = false;
                break;
            }
        }
        if (all_fail) 
        { // Все a_j вернули 1 для этого q_i → n составное
            return false;
        }
    }

    return true; // n вероятно простое
}

double EulersFunction(int n) {
    if (n == 1) 
    {
        return 1;
    }

    double result = n;
    for (int i = 2; i <= sqrt(n); ++i) 
    {
        if (n % i == 0) 
        {
            while (n % i == 0) n /= i;
            result -= result / i;
        }
    }

    if (n > 1)
    {
        result -= result / n;
    }

    return result;
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
        
    int m = mGenerator(bits, primes);
    int n = nCalculation(m);
    
    vector<int> decomposition = nMinusOneDecomposition(n); // разложение n-1 = 2^k * q
    bool isPrime = MillerTest(n, decomposition, t); // сам тест Миллера
        
    cout << "Сгенерированное число n = " << n << endl;
    cout << "Разложение n-1 = " << n - 1 << ": ";
    for (int q : decomposition) 
    {
        cout << q << " ";
    }
    cout << endl;

    double phi_n_minus_1 = EulersFunction(n - 1);
    double probability_error = (pow((phi_n_minus_1 / (n - 1)), t)) * 100.0;
    
    if (isPrime) 
    {
        cout << "Число " << n << " простое" << endl;
    } else {
        cout << "Число " << n << " составное с вероятностью " << setprecision(2) << 1 - probability_error << "%" << endl;
        cout << "Вероятность ошибки: " << setprecision(2) << probability_error << "%" << endl;
    }
    
    return 0;
}