#include <bits/stdc++.h>
#include "list.h"
#include "funkcja.h"

int main(){

    myList<int> lista;
    for(int i=0; i<100; i++){
        lista.add(i);
    }
    lista.remove(0);
    for(int i=0; i<lista.size_of(); i++){
        std::cout << lista.get(i) << std::endl;
    }

    std::cout << lista.first() << ", " << lista.last() << std::endl;

    int a=10, b=30;
    add_or_inc<int, int>(a, b);
    std::cout << a << std::endl;
    add_or_inc<int>(b);
    std::cout << b << std::endl;

    return 0;
}
