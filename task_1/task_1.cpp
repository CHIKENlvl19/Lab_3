#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void line(){
    cout << "-------------------" << endl;
}

void value_print(float x, float y){
    cout << "|" << setw(6) << fixed << setprecision(1) << x << " |"
         << setw(8) << fixed << setprecision(2) << y << " |" << endl; 
}

int main() {
    float x = -6;
    float y = 0;

    cout << "Таблица значений функции:" << endl;
    line();
    cout << "|   x   |    y    |" << endl;
    line();

    for(x; x <= -2; x++){
        y = -0.992 * pow(( x + 3.5), 2) + 2.2;
        value_print(x, y);
    }

    for(x; x <= 2; x++){
        y = -sqrt(4 - x*x);
        value_print(x, y);
    }

    for(x; x <= 8; x++){
        y = ( log(x) / log(2) ) - 1;
        value_print(x, y);
    }

    for(x; x <= 10; x++){
        y = -x + 9;
        value_print(x, y);
    }
    line();

    return 0;
}