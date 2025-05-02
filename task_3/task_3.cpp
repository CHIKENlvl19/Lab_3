#include <iostream>
#include <cmath>
using namespace std;

long long gcd(long long a, long long b) {
    while( b!= 0)
    {
        long long r = b;
        b = a % b;
        a = r;
    }

    return a;
}

pair<long long, long long> simplify(long long num, long long den) {
    long long g = gcd(abs(num), abs(den));
    
    num /= g; 
    den /= g;

    if (den < 0) 
    {
        num *= -1; 
        den *= -1; 
    }

    return {num, den};
}

long long compute_numerator(int a, int b) {
    switch(a) 
    {
        case 1: return b;
        case 2: return b * (b + 1);
        case 3: return b * (b*b + 4*b + 1);
        case 4: return b * (b*b*b + 11*b*b + 11*b + 1);
        case 5: return b * (b*b*b*b + 26*b*b*b + 66*b*b + 26*b + 1);
        case 6: return b * (pow(b,5) + 57*pow(b,4) + 302*pow(b,3) + 302*pow(b,2) + 57*b + 1);
        case 7: return b * (pow(b,6) + 120*pow(b,5) + 1191*pow(b,4) + 2416*pow(b,3) + 1191*pow(b,2) + 120*b + 1);
        case 8: return b * (pow(b,7) + 247*pow(b,6) + 4293*pow(b,5) + 15619*pow(b,4) + 15619*pow(b,3) + 4293*pow(b,2) + 247*b + 1);
        case 9: return b * (pow(b,8) + 502*pow(b,7) + 14608*pow(b,6) + 88234*pow(b,5) + 156190*pow(b,4) + 88234*pow(b,3) + 14608*pow(b,2) + 502*b + 1);
        case 10: return b * (pow(b,9) + 1013*pow(b,8) + 47840*pow(b,7) + 455192*pow(b,6) + 1310354*pow(b,5) + 1310354*pow(b,4) + 455192*pow(b,3) + 47840*pow(b,2) + 1013*b + 1);
        default: return 0;
    }
}

int main() {
    int a, b;
    cout << "Введите два целых числа для вычисления суммы ряда: ";
    cin >> a >> b;

    if (b == 1) {
        cout << "infinity\n";
        return 0;
    }

    long long numerator = compute_numerator(a, b);
    long long denominator = pow(b - 1, a + 1);

    auto [sim_num, sim_den] = simplify(numerator, denominator);
    cout << "Сумма ряда равна " << sim_num << "/" << sim_den << endl;

    return 0;
}