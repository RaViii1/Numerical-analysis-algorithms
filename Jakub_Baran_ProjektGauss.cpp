#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>

using namespace std;
const double epsilon = 1e-12; // stała przybli¿enia zera
typedef vector <vector <double>> Macierz;
typedef vector <double> Tablica;//Przechowywanie współczynników
int WczytajDane(Macierz&);
int DaneDomyslne(Macierz&, int);
bool Eliminacja(Macierz &,int ,  int );
bool Oblicz(Macierz, Tablica&,int);
bool WyborDanych();
void Wyswietl(Tablica, int );
//Z wyborem elemetu w kolumnie
int IndexMaxKol(Macierz& , int , int );
void ZamianaWierszy(Macierz& ,int , int ,int );
//
int main ()
{   //
    Macierz AB;//Macierz zlozona
    Tablica X;//Współczynniki
    int n;//ilość wierszy
    //
    bool zewnetrzne;
    bool exit = false;
    int menu = 0;
    while (!exit) {
        cout<<"--------------------------------"<<endl;
        cout<<"Metoda eliminacji Gaussa"<<endl;
        cout<<"Wybierz metode:"<<endl;
        cout<<"1. Podstawowa"<<endl;
        cout<<"2. Z wyborem elementu maksymalnego w kolumnie"<<endl;
        cout<<"3. Wyjscie "<<endl;
        cout<<"--------------------------------"<<endl;
        cout<<"Wybor: ";
        cin>>menu;
        cout<<endl;
        switch (menu) {
            case 1:{
                 zewnetrzne = WyborDanych();
                 if(zewnetrzne){    //Dla wartosci true wprowadzane są wartości od użytkownika
                        n = WczytajDane(AB);
                 }else  n = DaneDomyslne(AB,1);//Dla wartosci false wprowadzane są wartości domyslne//1 to numer metody
                 if(Eliminacja(AB,n,1))
                 {
                     cout<<"Wystapil blad w trakcie wykonywania eliminacji."<<endl;break;
                 }
                 if(Oblicz(AB,X,n))
                 {
                     cout<<"Wystapil blad w trakcie wykonywania postepowania odwrotnego."<<endl;break;
                 }
                 Wyswietl(X,n);
                 break;
             }
                 case 2:{
                 zewnetrzne = WyborDanych();
                 if(zewnetrzne){    //Dla wartosci true wprowadzane są wartości od użytkownika
                        n = WczytajDane(AB);
                 }else  n = DaneDomyslne(AB,2);//Dla wartosci false wprowadzane są wartości domyslne//2 to numer metody
                 if(Eliminacja(AB,n,2))
                 {
                     cout<<"Wystapil blad w trakcie wykonywania eliminacji."<<endl;break;
                 }
                 if(Oblicz(AB,X,n))
                 {
                     cout<<"Wystapil blad w trakcie wykonywania postepowania odwrotnego."<<endl;break;
                 }
                 Wyswietl(X,n);
                 break;
             }

         case 3: {
             exit = true;break;
         }
         default: {
             cout<<"Zly wybor!\n"<<endl;break;
            }
        }
    }
    cout<<"Koniec"<<endl;
    cin.ignore();
    cin.get();
    return 0;
}

bool Oblicz(Macierz AB, Tablica &X,int n)// postępowanie odwrotne liczenie wektora wynikowego
{
    if(fabs(AB[n-1][n-1])<=epsilon) //Wartość bezwzględna liczby 𝑎 ≠ 0
    {
        cout<<"Blad w postepowaniu odwrotnym " << n<<" <= epsilon" <<endl;
    return true;
    }
    X.resize(n);//Zmiana wielkosci tablicy współczynników
    X[n-1] = AB[n-1][n] / AB[n-1][n-1];//obliczenie wartosci x koncowego
    for(int k = n-2; k>=0;k--)
    {
            double z = 0.0;//suma wartosci  xów
            for(int j = k+1; j<n; j++)
            {
                z +=(X[j]* AB[k][j]);//Sumowanie wartosci poprzednich x'ów
            }
            X[k] =(AB[k][n]-z)/ AB[k][k];//obliczanie kolejncych x
    }
    return false;
}
////metody do 2 podpunktu
void ZamianaWierszy(Macierz &AB,int index1, int index2,int n)
{
    Tablica temp;//tymczasowa tablica do przechowywania współczynników
    if(index1==index2) return;
    temp = AB[index1];
    AB[index1]=AB[index2];
    AB[index2]=temp;
}

int IndexMaxKol(Macierz &AB, int k, int n)//k to idex poczatkowy
{
    double maximum = fabs(AB[k][k]); //Wartość bezwzględna liczby
    int maxin = k;
    for(int i = k+1; i <n;i++)
    {
        if(fabs(AB[i][k])>maximum)
        {
            maximum = fabs(AB[i][k]); //jezeli wartosc bezwzgledna jest wieksza od maximum to staje sie ona nowym maxiumum
            maxin = i;
        }
    }
    return maxin;
}
////
bool Eliminacja(Macierz &AB,int n, int metoda)
{
    int maxin;
    Tablica t;//tablica współczynników

    for(int k =1;k<n;k++)
    {
        if(metoda ==2)
        {
            maxin = IndexMaxKol(AB,k-1,n);
            ZamianaWierszy(AB,k-1,maxin,n);
        }
        if(fabs(AB[k-1][k-1]) <= epsilon) //a ≠ 0
        {
            cout <<endl<< "Blad  w kroku "<<k<<"a <= epsilon"<<endl<<endl;
            return false;
        }
        t.resize(n-k);
        for(int i =0; i <n-k;i++)
            {
                t[i]=AB[k+i][k-1]/AB[k-1][k-1]; //Obliczanie kolejnych współczynników
            }
        for(int i = k;i<n;i++)
            {
                for(int j =0;j<n+1;j++)
                    {
                        AB[i][j] -= (t[i-k]*AB[k-1][j]);////Obliczanie kolejnych elementów wiersza
                    }
            }
    }
    return false;
}

int WczytajDane(Macierz &AB)
{
    int n = 0;
    while(n<2)
    {
        cout<<"Podaj liczbe wierszy [n]: ";
        cin>>n;
    }
    AB.resize(n);//zmiana wielkości macierzy zależnie od wczytanego n
    for(int i = 0; i<n ;i++)
    {
        AB[i].resize(n+1);
    }
    cout<<"Podaj macierz [A|B]:"<<endl;
    for(int i = 0;i<n;i++)
    {
        cout<<"Wiersz ("<<i+1<<"): "<<endl;
        for(int j = 0; j<n+1;j++)
            {
                cout<<"Kolumna ("<<j+1<<"): ";
                cin>>AB[i][j]; //wczytanie wartosci macierzy, idąc kolejno wierszem
            }
    }
    return n;
}

int DaneDomyslne(Macierz &AB, int metoda)
{
    int stopien;
    if(metoda == 1)
        {
            stopien=4;
            AB.resize(stopien);
            for(int i =0;i<stopien;i++) AB[i].resize(stopien+1);
            AB = {{1,1,0,-3,1},{1,4,-1,-4,-2},{0.5,0.5,-3,-5.5,1.5},{1.5,3,-5,-9,-0.5}}; //przykład z zad 10.1
            //n=3
            //AB = {{1,2,-1,-1},{-1,-1,3,4},{-2,-3,1,-1}};  // T|3,-1,2|
            //n=4
            //AB = {1,2,-1,1,6}{-1,1,2,-1,3}{2,-1,2,2,14}{1,1,-1,2,8} //T|1,2,3,4|
            return stopien;
        }
        if(metoda == 2)
        {
            stopien=4;
            AB.resize(stopien);
            for(int i =0;i<stopien;i++) AB[i].resize(stopien+1);
            AB = {{2.25,-2.5,4,-5.25,-1},{-3,-7.5,6.5,0,17},{-6.25,-12.5,0.25,5.25,24.25},{9,10,7,-21,-33}};//przykład 10.2
            return stopien;
        }
    return 0;
}

bool WyborDanych()
{
    bool exit = false;
    bool zewnetrzne=false;
       while (!exit) {
           cout<<"Wybierz rodzaj danych: "<<endl;
           cout<<"0. Dane z programu"<<endl;
           cout<<"1. Dane od uzytkownika"<<endl;
           cout<<"Wybor: ";
           cin>>zewnetrzne;//Dla wartosci true wprowadzane są wartości od użytkownika
           if(cin.fail())
           {
               cin.clear();
               cin.ignore();
               zewnetrzne = false;
               cout<<"Bledny wybor"<<endl;
           }
           else {
                return zewnetrzne;
           }
    }
    return false;
}

void Wyswietl(Tablica X, int n)
{
    cout<<"Rozwiazaniem ukladu jest wektor = |";
        for(int i=0; i<n;i++)
        {
            cout<<X[i]; //Wyswietlenie tablicy z wynikami
            if(i<n-1){
                cout<<",";
            }
        }
        cout <<"|T"<<endl;
}
