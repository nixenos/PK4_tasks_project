/*
** Szablon prostej tablicy dynamicznej (pseudo vector)
*/
#define START_SIZE 10

template <class T>
class myList{
    private:
        T * internalList;
        long cSize;
        long realSize;

    public:
        /*
        ** konstruktor bezargumentowy
         */
        myList();

        /*
        ** konstruktor jednoargumentowy, przyjmujący początkowy rozmiar kontenera
         */
        myList(long length);

        /*
        ** destruktor
         */
        ~myList();

        /*
        ** funkcja zwracająca pierwszy element z listy
        */
        T first();

        /*
        ** funkcja zwracająca ostatni element z listy
        */
        T last();

        /*
        ** funkcja zwracająca wielkość kontenera
        */
        long size_of() const noexcept;

        /*
        ** funkcja dodająca element na koniec listy
        */
        void add(const T &item);

        /*
        ** funkcja usuwająca element pod podanym indeksem
        */
        void remove(long index);

        /**
         * funkcja zwracająca element pod podanym indeksem
         */
        T get(long index);
};


template <class T>
myList<T>::myList(){
    this->internalList = new T[START_SIZE];
    this->cSize = 0;
    this->realSize = START_SIZE;
}

template <class T>
myList<T>::myList(long length){
    this->internalList = new T[length];
    this->cSize = 0;
    this->realSize = length;
}

template <class T>
myList<T>::~myList(){
    delete[] this->internalList;
}

template <class T>
T myList<T>::first(){
    return this->internalList[0];
}

template <class T>
T myList<T>::last(){
    return this->internalList[this->cSize - 1];
}

template <class T>
long myList<T>::size_of() const noexcept{
    return this->cSize;
}

template <class T>
void myList<T>::add(const T &item){
    if(this->realSize <= this->cSize + 1){
        T * temp = new T[this->realSize + START_SIZE];
        for(int i=0; i<this->cSize; i++){
            temp[i] = this->internalList[i];
        }
        delete[] this->internalList;
        this->internalList = temp;
        this->realSize += START_SIZE;
    }
    this->internalList[this->cSize] = item;
    this->cSize++;
}

template <class T>
void myList<T>::remove(long index){
    for(int i=index; i<this->cSize - 1; i++){
        this->internalList[i] = this->internalList[i+1];
    }
    this->cSize--;
}

template <class T>
T myList<T>::get(long index){
    if(index<this->cSize && index >= 0)
        return this->internalList[index];
    else
        return -1;
}
