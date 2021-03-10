/*
** Napisz rodzinę funkcji zwiększających wartość pierwszego argumentu o drugi argument,
** lub o 1, gdy nie podano drugiego argumentu.
** Ma ona działać dla wszystkich typów liczbowych i używać mechanizmów szablonów.
*/

template <class T, class D>
void add_or_inc(T &first, const T &second){
    first += (T)second;
}

template <class T>
void add_or_inc(T &first){
    first+=1;
}
