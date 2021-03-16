#include <bits/stdc++.h>

using namespace std;

class Ksiazka {
    public:
        int cena;
        string tytul;
        Ksiazka(int cen, string tyt){
            cena=cen;
            tytul=tyt;
        }
        Ksiazka(){
            cena = rand() % 100;
            tytul = "blank title";
        }

        friend ostream& operator<<(ostream &output, Ksiazka * ksi){
            output << "Tytuł książki: " << ksi->tytul << ", cena: " << ksi->cena << endl;
            return output;
        }
};

void sort_ksiazka_vector(vector <Ksiazka *> &v){
    if(v.size() < 2){
        return;
    }
    Ksiazka * temp = nullptr;
    for(int i=0; i<v.size() - 1; i++){
        for(int j=i; j<v.size(); j++){
            if(v[i]->cena > v[j]->cena){
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }
}

void print_vec(vector <Ksiazka *> &v){
    for(int i=0; i<v.size(); i++){
        cout << v[i];
    }
}

int main(){
    // zadanie 1
    vector <Ksiazka *> ksiVec;
    default_random_engine random;
    random.seed(chrono::system_clock::now().time_since_epoch().count());
    uniform_int_distribution <int> dist1(0, 100);
    uniform_int_distribution <int> dist2(0, 10);
    for(int i=0; i<10; i++){
        ksiVec.push_back(new Ksiazka(dist1(random), "random book name" + to_string(i)));
    }
    print_vec(ksiVec);
    sort_ksiazka_vector(ksiVec);
    cout << "Posortowane \n";
    print_vec(ksiVec);
    for(int i=0; i<10; i++){
        delete(ksiVec[i]);
    }
    // zadanie 2
    int number;
    set<int> mySet;
    multiset<int> myMSet;
    for(int i=0; i<10; i++){
        number = dist2(random);
        mySet.insert(number);
        myMSet.insert(number);
    }
    cout << "Rozmiar set: " << mySet.size() << endl;
    cout << "Rozmiar multiset: " << myMSet.size() << endl;
    //zadanie 3
    int step=0;
    cout << "Podaj stopień macierzy: ";
    cin >> step;
    vector<vector <int>> matrix(step, vector<int>(step, 0));
    for(int i=0; i<step; i++){
        for(int j=0; j<step; j++){
            if(i==j){
                matrix[i][j] = 1;
            }
        }
    }
    for(int i=0; i<step; i++){
        for(int j=0; j<step; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}