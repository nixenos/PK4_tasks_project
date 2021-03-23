#include <bits/stdc++.h>

using namespace std;
// zadanie 1
class Centrum_handlowe{
    public:
    int sklepy;
    Centrum_handlowe(){
        cout << "Konstruktor bezargumentowy\n";
        this->sklepy = 0;
    }
    Centrum_handlowe(int ile){
        cout << "Konstruktor jednoargumentowy\n";
        this->sklepy = ile;
    }
    ~Centrum_handlowe(){
        cout << "Destruktor\n";
    }
    void increment(){
        cout << "Metoda increment\n";
        this->sklepy++;
    }
};

void printptr(const unique_ptr<Centrum_handlowe> &ptr){
    if(ptr){
        cout << "Adress: " << ptr.get() << ", value: " << ptr->sklepy << "\n";
    }
    else{
        cout << "nullptr\n";
    }
}

void printval(vector <shared_ptr<int>> vec){
    for(int i=0; i<vec.size(); i++){
        if(*vec[i])    
            cout << "Value: " << *vec[i] << endl;
    }
}

void printaddr(vector <shared_ptr<int>> vec){
    for(int i=0; i<vec.size(); i++){
        cout << "Adress: " << vec[i].get() << endl;
    }
}

int main(){
    // zadanie 2
    unique_ptr<Centrum_handlowe> p1 = make_unique<Centrum_handlowe>(10);
    unique_ptr<Centrum_handlowe> p2(new Centrum_handlowe(15));
    unique_ptr<Centrum_handlowe> p3 = make_unique<Centrum_handlowe>();

    printptr(p1);
    printptr(p2);
    printptr(p3);


    // reset
    cout << "BEFORE RESET\n";
    printptr(p1);
    cout << "RESET\n";
    p1.reset();
    printptr(p1);

    // release
    cout << "BEFORE RELEASE\n";
    printptr(p1);
    cout << "RELEASE\n";
    p1.release();
    printptr(p1);

    // zadanie 3
    cout << "BEFORE SWAP\n";
    printptr(p2);
    printptr(p3);
    cout << "SWAP\n";
    p2.swap(p3);
    printptr(p2);
    printptr(p3);

    cout << "BEFORE MOVE\n";
    printptr(p2);
    unique_ptr<Centrum_handlowe> p4(move(p2));
    cout << "MOVE\n";
    printptr(p2);
    printptr(p4);

    // zadanie 5
    srand(time(NULL));
    vector <shared_ptr<int>> vec;
    for(int i=0; i<10; i++){
        vec.push_back(make_shared<int>(rand()%10));
    }
    printval(vec);
    printaddr(vec);
    vec[5] = vec[8];
    weak_ptr<int> w = vec[8];    
    cout << "Weak ptr usecount: " << w.use_count() << ", adress: " << w.lock() << endl;
    vec[8].reset();
    cout << "Weak ptr usecount: " << w.use_count() << ", adress: " << w.lock() << endl;
    vec[5].reset();
    cout << "Weak ptr usecount: " << w.use_count() << ", adress: " << w.lock() << endl;
    return 0;
}