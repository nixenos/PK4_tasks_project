#include <bits/stdc++.h>

using namespace std;

mutex mtx;
condition_variable cond_var;

// zadanie 2

void functionCopyVector(const vector<int> &v1, vector<int> &v2){
    lock_guard<mutex> lock(mtx);
    for(auto it : v1){
        cout << "Function thread id: " << this_thread::get_id() << endl;
        v2.push_back(it);
    }
}

class CopyVector{
    public:
        void operator()(const vector<int> &v1, vector<int> &v2){
            lock_guard<mutex> lock(mtx);
            for(auto it : v1){
                cout << "Class thread id: " << this_thread::get_id() << endl;
                v2.push_back(it);
            }
        }
};

// zadanie 3
class ZapiszDoPliku{
    vector<string> slowa;
    string sciezka;
    public:
        ZapiszDoPliku(const string &sciezka) : sciezka(sciezka) {}

        void Wypelnij(){
            int i=0;
            for(i=0; i<5; i++){
                string temp;
                cin >> temp;
                this->slowa.push_back(move(temp));
                cond_var.notify_all();
            }
        }

        void Zapisz(){
            ofstream fS(this->sciezka);
            int i=0;
            for(i=0; i<5; i++){
                unique_lock<mutex> lck(mtx);
                cond_var.wait(lck, [=]{return i +1 <= slowa.size();});
                fS << slowa[i] << '\n';
            }
            fS.close();
        }
};

int main(){

    // zadanie 1
    cout << "Wątki CPU: " << thread::hardware_concurrency() << endl;

    //zadanie 2
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    for(int i=0; i<10; i++){
        v1.push_back(i);
        v2.push_back(i*9+11);
    }

    CopyVector cpv;

    thread thread1(functionCopyVector, cref(v1), ref(v3));
    thread thread2(ref(cpv), cref(v2), ref(v3));

    thread1.join();
    thread2.join();

    for (auto obj : v3){
        cout << "V3: " << obj << endl;
    }

    // zadanie 3
    cout << "--------------\n";
    ZapiszDoPliku plik("tempfile");
    thread thread3(&ZapiszDoPliku::Wypelnij, &plik);
    thread thread4(&ZapiszDoPliku::Zapisz, &plik);

    cout << "Podaj 5 słów: \n";
    thread3.join();
    thread4.join();

    return 0;
}