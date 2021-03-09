#include <bits/stdc++.h>

using namespace std;

class Abonent{
    public:
        float CenaAbonamentu;
        float CentaTelefonu;
        float DoZaplany;
        string Numer;
};

class numer_error{
    public:
        string nazwa;
};

class za_krotki : public numer_error{
    public:
        za_krotki(){ nazwa = "Za krótki"; }
};

class za_dlugi : public numer_error{
    public:
        za_dlugi(){ nazwa = "Za długi"; }
};

class bledne_znaki : public numer_error{
    public:
        bledne_znaki(){ nazwa = "Niepoprawne znaki"; }
};

void DodajAbonenta(Abonent * tab[], int count){
    string numer;
    float cenaA, cenaT, zaplata;
    za_krotki zk;
    za_dlugi zd;
    bledne_znaki bz;
    for(int i=0; i<count; i++){
        cout << "numer telefonu: ";
        cin >> numer;
        if(numer.length() < 9){
            throw zk;
        }
        if(numer.length() > 9){
            throw zd;
        }
        for(auto ch : numer){
            if ('0' > ch || '9' < ch ){
                throw bz;
            }
        }
        cout << "\n cena abonamentu: ";
        cin >> cenaA;
        if(cenaA < 0){
            throw logic_error("Ujemna cena");
        }
        cout << "\n cena telefonu: ";
        cin >> cenaT;
        if(cenaT < 0){
            throw logic_error("Ujemna cena");
        }
        cout << "\n do zapłaty: ";
        cin >> zaplata;
        if(zaplata < 0){
            throw logic_error("Ujemna cena");
        }

        tab[i]->Numer = numer;
        tab[i]->CenaAbonamentu = cenaA;
        tab[i]->CentaTelefonu = cenaT;
        tab[i]->DoZaplany = zaplata;

    }
}

int main(){
    Abonent adam, ewa, marcin;
    Abonent * klienci[3] = {&adam, &ewa, &marcin};
   int error=0;
   do{
       try{
            DodajAbonenta(klienci, 3);
       }
       catch(numer_error &erro){
           cout << "Błędny numer: " << erro.nazwa << endl;
           error=1;
       }
       catch(logic_error &err){
           cout << "Błąd logiczny: " << err.what() << endl;
           error=1;
       }
       catch(...){
           cout << "Nieznany błąd!\n";
           error=1;
       }
   } while(error);
   return 0; 
}
