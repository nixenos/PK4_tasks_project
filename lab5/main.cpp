#include <bits/stdc++.h>

// zadanie 1
template <class T>
void printContainer(std::vector<T> container){
    for (auto it : container){
        std::cout << it << std::endl;
    }
    std::cout << std::endl;
}

// zadanie 4
class Complex {
    public:
        double Re;
        double Im;

        Complex(){
            Re=0;
            Im=0;
        }

        Complex(double r, double i){
            Re=r;
            Im=i;
        }

        // operator porównania modułów obu liczb
        bool operator<(const Complex &next){
            return sqrt(Re*Re + Im*Im) < sqrt(next.Re*next.Re + next.Im * next.Im);
        }

        // operator wypisania do strumienia, dla ułatwienia wypisania
        friend std::ostream &operator<< (std::ostream &stream, const Complex &cplx){
            stream << "Realis: " << cplx.Re << ", imaginaris: " << cplx.Im << std::endl;
            return stream;
        }
};


int main(){
    // zadanie 2 + 1 cd
    std::vector <int> vec(10);
    std::default_random_engine random;
    random.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution <int> dist1(0, 100);
    std::uniform_int_distribution <int> dist2(0, 10);

    for(int i=0; i<10; i++){
        vec[i] = dist1(random);
    }

    printContainer(vec);

    std::vector<int> vec2;

    std::cout << std::endl;
    std::copy(vec.begin(), vec.end(), std::back_inserter(vec2));
    printContainer(vec);
    std::cout << std::endl;
    printContainer(vec2);
    std::cout << std::endl;
    std::reverse(vec2.begin(), vec2.end());
    printContainer(vec);
    std::cout << std::endl;
    printContainer(vec2);
    std::cout << std::endl;
    std::sort(vec2.begin(), vec2.end());
    printContainer(vec);
    std::cout << std::endl;
    printContainer(vec2);
    std::cout << std::endl;
    std::iter_swap(vec2.begin()+3, vec2.end());
    printContainer(vec);
    std::cout << std::endl;
    printContainer(vec2);
    std::cout << std::endl;
    std::reverse(vec2.begin(), vec2.begin()+10);
    printContainer(vec);
    std::cout << std::endl;
    printContainer(vec2);
    std::cout << std::endl;
    std::cout << "Ile razy jest 10: " << std::count(vec2.begin(), vec2.end(), 10) << std::endl;
    std::cout << std::endl;
    std::fill(vec2.begin(), vec2.end(), 333);
    printContainer(vec);
    std::cout << std::endl;
    printContainer(vec2);
    std::cout << std::endl;
    // zadanie 3

    std::vector<char> charvec = {'a', 'g', 'f', 'e', 'r', 'q', 'o'};
    std::vector<std::string> stringvec = {"aaaaa", "bb", "aa", "bbbb", "c"};
    printContainer(charvec);
    printContainer(stringvec);
    std::sort(charvec.begin(), charvec.end());
    std::sort(stringvec.begin(), stringvec.end());
    printContainer(charvec);
    printContainer(stringvec);

    //zadanie 4 cd


    std::vector<Complex> complexvec(10);
    for(int i=0; i<10; i++){
        complexvec[i] = Complex(dist2(random), dist2(random));
    }
    printContainer(complexvec);
    std::sort(complexvec.begin(), complexvec.end());
    printContainer(complexvec);

    return 0;
}