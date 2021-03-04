#include <bits/stdc++.h>

using namespace std;

class Firma{
    public:
        long long doUregulowania = 0;

        void uregulowane(){
            this->doUregulowania = 0;
        }

        virtual ~Firma() = default;
};

class Dostawca : public Firma{
    public:
        virtual void dostawa(){}
};

class Nabywca : public Firma{
    public:
        virtual void sprzedaz(){}
};

class Detal : public Nabywca{
    public:
        virtual void sprzedaz(){
            this->doUregulowania += 5000;
        }
};

class Hurt : public Nabywca{
    public:
        virtual void sprzedaz(){
            this->doUregulowania += 25000;
        }
};

class Komputery : public Dostawca{
    public:
        virtual void dostawa(){
            this->doUregulowania -= 30000;
        }
};

class Monitory : public Dostawca{
    public:
        virtual void dostawa(){
            this->doUregulowania -= 12000;
        }
};


int main(){
    Detal detal1, detal2;
    Hurt hurt1, hurt2;
    Komputery komputery1, komputery2;
    Monitory monitory1, monitory2;

    Firma * firmy[] = {
    &detal1, &detal2,
    &hurt1, &hurt2,
    &komputery1, &komputery2,
    &monitory1, &monitory2
    };

    long long balans = 0;

    for(int i=0; i<1000; i++){
        if(i%2){
            detal1.sprzedaz();
            hurt2.sprzedaz();
        }
        if(i%3){
            detal2.sprzedaz();
            hurt1.sprzedaz();
        }
        if(i%17){
            detal1.sprzedaz();
            hurt2.sprzedaz();
            komputery1.dostawa();
            monitory2.dostawa();
        }
        if(i%37){
            detal2.sprzedaz();
            hurt1.sprzedaz();
            komputery2.dostawa();
            monitory1.dostawa();
        }
    }

    Nabywca * tempNabywca;
    Dostawca * tempDostawca;

    for(auto firma : firmy){
        cout << typeid(*firma).name();
        tempDostawca = dynamic_cast<Dostawca *>(firma);
        tempNabywca = dynamic_cast<Nabywca *>(firma);
        if( tempDostawca ) cout << ", dziedziczy po Dostawca";
        if( tempNabywca ) cout << ", dziedziczy po Nabywca";
        cout << ", saldo konta firmy: " << firma->doUregulowania << endl;
        balans += firma->doUregulowania;
    }
    cout << "Saldo centrum logistycznego: " << balans << endl;
    return 0;
}
