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

    // размер R = размер F, т.к. размер F = размер n + 1, а размер R = размер F - 1
    
    

    return F;
}

int nCalculation (int F) {
    int n;

    int R = rand();

    return n;
}

int main() {

    srand(time(NULL));



    return 0;
}