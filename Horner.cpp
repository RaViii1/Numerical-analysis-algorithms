#include <iostream>

using namespace std;

double silnia(int n) {
    double silnia = 1;
    for(int i = 1; i <= n; ++i) {
        silnia *= i;
    }
    return silnia;
}

int main()
{
    int n;
    cout << "Podaj stopien wielomianu: ";
    cin >> n;
    double A[n + 1];
    string wielomian = "";
    for(int i = 0; i <= n; i++) {
        cout << "Podaj wspolczynnik x^" << n - i << ": ";
        cin >> A[i];
    }
    double punkt;
    cout << "Wprowadz punkt w ktorym ma byc wyliczona  wartosc wielomianu: ";
    cin >> punkt;
    double result = A[0];
    for(int i = 1; i <= n; i++) {
        result = result * punkt + A[i];
    }
    cout << "Wartosc w tym punkcie: " << result << endl;

    int counter = n;
    while(counter > 0) {
        for(int i = 1; i <= counter; i++) {
            A[i] = A[i] + A[i-1] * punkt;
        }
        counter--;
    }

    cout << "Pochodne: " << endl;
    for(int i = 1; i <= n; i++) {
        cout << "'(" << i << ") = ";
        cout << A[n-i] * silnia(i) << endl;
    }

    return 0;
}
