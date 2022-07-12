#include "Matrice.h"
#include <exception>

using namespace std;
//Complexitate Theta(1)
Matrice::Matrice(int n, int m) {
    if (n <= 0 || m <= 0) throw exception();
    this->n = n;
    this->m = m;
    capacity = n * m;
    length = 0;
    vector = new TPair[capacity];
}
//Complexitate Theta(1)
Matrice::~Matrice() { delete[] vector; }
//Complexitate Theta(1)
int Matrice::nrLinii() const {
    return n;
}

//Complexitate Theta(1)
int Matrice::nrColoane() const {
    return m;
}

//Complexitate caz favorabil Theta(1) element pe mijloc, caz defavorabil Theta(n) nu exita elementul, Thea(n) caz mediu
TElem Matrice::element(int i, int j) const {
    if (i < 0 || j < 0 || i >= n || j >= m) throw exception();
    int mij, st = 0, dr = length - 1, pi, pj;
    while (st <= dr)
    {
        mij = (st + dr) / 2;
        pi = get<0>(vector[mij]);//iau linia
        pj = get<1>(vector[mij]);//iau coloana
        if (pi == i && pj == j) return get<2>(vector[mij]);//intorc elementul
        if (i < pi || i == pi && j < pj) dr = mij - 1;
        else st = mij + 1;
    }
    return NULL_TELEMENT;
}


//Complexitate caz favorabil Theta(1) element pe mijloc, caz defavorabil Theta(n) nu exita elementul si trebuie inserat, Theta(n) caz mediu
TElem Matrice::modifica(int i, int j, TElem e) {
    if (i < 0 || j < 0 || i >= n || j >= m) throw exception();
    TElem old = element(i, j);
    int mij, st = 0, dr = length, pi, pj, lastst = 0;
    while (st < dr)
    {
        mij = (st + dr) / 2;
        pi = get<0>(vector[mij]);
        pj = get<1>(vector[mij]);
        if (pi == i && pj == j) { get<2>(vector[mij]) = e; return old; }
        if (i < pi || i == pi && j < pj) dr = mij;
        else st = mij + 1, lastst = st;
    }
    // il adaugam
    TPair nou = make_tuple(i, j, e);
    // il inseram la pozitia care trebuie
    int poz = lastst;//unde am ramas cu cautarea
    for (int index = length - 1; index >= poz; --index)
        vector[index + 1] = vector[index];
    vector[poz] = nou;
    length++;
    return NULL_TELEMENT;
}