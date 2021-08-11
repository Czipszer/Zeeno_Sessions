#include <iostream>                         //knihovna pro vztupy a výstupy

#include "main.hpp"


using namespace std;                        //umoznuje vynechat std na začátku čádku  


int main(int argc, char * argv[]) {

    std::cout << "Hell" << "o world!";      //priklad vypisu s std na zacatku radku

    cout << endl;
    cout << endl;
    cout << endl;

    //TODO: kalkulačka
    double a, b, x; 
    int operat;                         //deklarace
    char rozhodnuti;                    //deklarace

    cout << "Vytej v Chipove bozi kalkulacce pro blbce." << endl;
    cout << "!!!Kazde cislo musi byt v rozsahu 0 az 9!!!" << endl;
    cout << "Pokud chcete vetsi rozsah zaplatte si nejaky nas vyhodny balicek." << endl;
    cout << "Chcete pokracovat? (y/n)" << endl;
    cin >> rozhodnuti;

    if (rozhodnuti == 'y')
    {
        cout << "Dobre tak jdeme na to." << endl;
        cout << "Zadejte prvni cislo: " << endl;
        cin >> a;

        if (a > 9 || a < 0) {
            cout << "Jaj. Jake mas zadat cislo? Poradim od 0 do 9." << endl;
            cout << "Zkus to znovu. Zadej prvni cislo:" << endl;
            cin >> a;

            if (a > 9 || a < 0){
                cout << "Tak nic." << endl;
                return 0;
            }
        }
        
        cout << "Zadej druhe cislo: " << endl;
        cin >> b;

        if (b > 9 || b < 0) {
            cout << "Jaj. Jake mas zadat cislo? Poradim od 0 do 9." << endl;
            cout << "Zkus to znovu. Zadej druhe cislo:" << endl;
            cin >> b;

            if (b > 9 || b < 0){
                cout << "Tak nic." << endl;
                return 0;
            }
        } 
         
        cout << "Jakou operaci s cisli " << a << " a " << b << " chces provest:" << endl;
        cout << "1 -> scitani" << endl;
        cout << "2 -> odcitani" << endl;
        cout << "3 -> nasobeni" << endl;
        cout << "4 -> deleni" << endl;
        cin >> operat;

        if (operat > 4 || operat < 1) {
            cout << "Jaj. Jake mas zadat cislo?" << endl;
            cout << "Zkus to znovu. Jakou operaci chces provest:" << endl;
            cin >> operat;

            if (operat > 4 || operat < 1){
                cout << "Tak nic." << endl;
                return 0;
            }
        } 

        if (operat == 1)
        {
                x = a + b;
                cout << "Vysledek je: " << x << endl;
        }
        if (operat == 2)
        {
                x = a - b;
                cout << "Vysledek je: " << x << endl;
        }
        if (operat == 3)
        {
                x = a * b;
                cout << "Vysledek je: " << x << endl;
        }
        if (operat == 4)
        {
            if(b == 0){
                cout << "Bohuzel ale delit nulou nemuzu." << endl;
            }
            else {
                x = a / b;
                cout << "Vysledek je: " << x << endl;
            }
        }
           
    }
    else if (rozhodnuti == 'n') {
        cout << "Jak chces. Papa" << endl;
    }
    else {
        cout << "Ses opravdu debil" << endl;
    }
    return 0;
}

