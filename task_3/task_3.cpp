#include <iostream>
#include <numeric> // для gcd

using namespace std;

int main() {
    int a, b;
    cin >> a >> b;

    // Проверка сходимости
    if (b >= a) {
        cout << "infinity" << endl;
        return 0;
    }

    // Вычисление суммы
    int numerator = b;
    int denominator = a - b;

    // Сокращение дроби
    int g = gcd(numerator, denominator);
    numerator /= g;
    denominator /= g;

    // Формат вывода
    if (denominator == 1) {
        cout << numerator << "/1" << endl;
    } else {
        cout << numerator << "/" << denominator << endl;
    }

    return 0;
}