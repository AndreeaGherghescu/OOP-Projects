#include <iostream>
#include <cstring>
//#include <fstream>
using namespace std;

class Carte
{
    char *titlu;
    char *nume_autor;
    int nr_pagini;
    float pret, rating;

    void set_titlu(char* titlu);
    void set_nume_autor(char* nume);
    void set_nr_pagini(int pagini);
    void set_pret(float pret);
    void set_rating(float rating);

public:
    char* get_titlu() { return titlu; }
    char* get_nume_autor() { return nume_autor; }
    int get_nr_pagini() { return nr_pagini; }
    float get_pret() { return pret; }
    float get_rating() { return rating; }

    //constructori
    Carte()
    {
        titlu = nullptr;
        nume_autor = nullptr;
        nr_pagini = 0;
        pret = 0;
        rating = 0;
    }
    Carte(char* titlu, char* autor, int pagini, float pret, float rating)
    {
        this->titlu = new char[strlen(titlu) + 1];
        strcpy(this->titlu, titlu);
        nume_autor=new char[strlen(autor)+1];
        strcpy(nume_autor,autor);
        nr_pagini=pagini;
        this->pret=pret;
        this->rating=rating;
    }
    Carte (const Carte& ob)
    {
        this->titlu = new char[strlen(ob.titlu) + 1];
        strcpy(this->titlu, ob.titlu);
        nume_autor = new char[strlen(ob.nume_autor) + 1];
        strcpy(nume_autor, ob.nume_autor);
        nr_pagini = ob.nr_pagini;
        this->pret = ob.pret;
        this->rating = ob.rating;
    }

    //cerinte
    static void cea_mai_putin_populara_carte (Carte *v, int n);
    static void cea_mai_scumpa_carte (Carte *v, int n);
    static Carte * invers_alfabetic_titlu(Carte *v, int n);
    static Carte * alfabetic_autor(Carte *v, int n);
    static void carti_diferite(Carte *v, int n);

    //supradefinirea =, >>, !=
    Carte operator=(const Carte& carte);
    friend istream &operator>>(istream &is,Carte &carte);
    friend bool operator!=(const Carte& carte1, const Carte& carte2);

    //destructor
    ~Carte() {
        if (this->titlu != nullptr) {  //trebuie sa eliberez eu memoria
            delete [] this->titlu;
        }
        if (this->nume_autor != nullptr) { //trebuie sa eliberez eu memoria
            delete [] this->nume_autor;
        }
    }

};
void Carte::set_titlu(char* titlu)
{
    this->titlu = new char[strlen(titlu)+1];
    strcpy(this->titlu,titlu);
}
void Carte::set_nume_autor(char* nume){
    this->nume_autor = new char[strlen(nume)+1];
    strcpy(this->nume_autor,nume);
}
void Carte::set_nr_pagini(int pagini){
    nr_pagini = pagini;
}
void Carte::set_pret(float pret){
    this->pret = pret;
}
void Carte::set_rating(float rating){
    this->rating = rating;
}
Carte Carte::operator=(const Carte& carte){
    if (this->titlu != nullptr)
        delete [] this->titlu;
    if (this->nume_autor != nullptr)
        delete [] this->nume_autor;
    this->titlu = new char[strlen(carte.titlu) + 1];
    strcpy(this->titlu, carte.titlu);
    this->nume_autor = new char[strlen(carte.nume_autor) + 1];
    strcpy(this->nume_autor, carte.nume_autor);
    this->nr_pagini = carte.nr_pagini;
    this->pret = carte.pret;
    this->rating = carte.rating;
    return *this;
}
bool operator!=(const Carte& carte1, const Carte& carte2){ //returnez 1 daca sunt diferite
    if (strcmp(carte1.titlu,carte2.titlu) != 0)
        return true;
    if (strcmp(carte1.nume_autor,carte2.nume_autor) != 0)
        return true;
    if (carte1.pret != carte2.pret)
        return true;
    if (carte1.nr_pagini != carte2.nr_pagini)
        return true;
    if (carte1.rating != carte2.rating)
        return true;
    return false;
}
istream &operator>>(istream &is,Carte &carte){
    char titlu[256], autor[256];
    cout << "Titlul cartii: "; is.getline(titlu,256);
    cout << "Numele autorului: "; is.getline(autor,256);

    carte.titlu = new char[strlen(titlu) + 1];
    strcpy(carte.titlu, titlu);
    carte.nume_autor = new char[strlen(autor) + 1];
    strcpy(carte.nume_autor, autor);

    cout << "Numarul de pagini: "; is >> carte.nr_pagini;
    cout << "Pret: "; is >> carte.pret;
    cout << "Rating: "; is >> carte.rating;
}
void Carte::cea_mai_putin_populara_carte(Carte *v, int n)
{
    float rating_minim = v[0].get_rating();
    int indice = 0;
    for (int i = 1; i<n ; i++)
    {
        if (v[i].get_rating() < rating_minim){
            rating_minim = v[i].get_rating();
            indice = i;
        }
    }
    cout << "Cartea cea mai putin populara este: <<" << v[indice].get_titlu() << ">> avand ratingul " << v[indice].get_rating() << '\n';
}
void Carte::cea_mai_scumpa_carte(Carte *v, int n) {
    float pret_maxim = 0;
    int indice = 0;
    for (int i = 0; i<n ; i++)
    {
        if (v[i].get_pret() > pret_maxim){
            pret_maxim = v[i].get_pret();
            indice = i;
        }
    }
    cout << "Cea mai scumpa carte este: <<" << v[indice].get_titlu() << ">> avand pretul " << v[indice].get_pret() << '\n';
}
Carte * Carte::invers_alfabetic_titlu(Carte *v, int n) {
    for (int i = 0; i<n ; i++){
        for (int j = i+1; j<n ; j++){
            if (strcmp(v[j].get_titlu(), v[i].get_titlu()) > 0){
                Carte carte_auxiliar;
                carte_auxiliar = v[i];
                v[i] = v[j];
                v[j] = carte_auxiliar;
            }
        }
    }
    return v;
}
Carte * Carte::alfabetic_autor(Carte *v, int n) {
    for (int i = 0; i<n ; i++){
        for (int j = i+1; j<n ; j++){
            if (strcmp(v[j].get_nume_autor(), v[i].get_nume_autor()) < 0){
                Carte carte_auxiliar;
                carte_auxiliar = v[i];
                v[i] = v[j];
                v[j] = carte_auxiliar;
            }
        }
    }
    return v;
}
void Carte::carti_diferite(Carte *v, int n) {
    for (int i = 0; i<n-1 ; i++){
        for (int j = i+1; j<n ; j++){
            if (v[i]!=v[j]) continue;
            cout<<"Cartile de pe pozitiile "<<i<<" si "<<j<<" din vector sunt duplicate!\n";
        }
    }
}
int main() {
    Carte *carti;
    int n;
    cout << "Numarul de carti este: "; cin >> n;
    cin.get();
    carti = new Carte[n];
    for (int i = 0; i<n ; i++) {
        cin >> carti[i];
        cin.get();
    }


    Carte::carti_diferite(carti,n);
    Carte::cea_mai_putin_populara_carte(carti,n);
    Carte::cea_mai_scumpa_carte(carti,n);

    cout<<'\n';
    carti = Carte::invers_alfabetic_titlu(carti,n);
    cout << "Titlurile ordonate invers alfabetic sunt:\n";
    for( int i = 0; i<n ; i++)
    {
        cout << "<<" << carti[i].get_titlu() << ">>" << '\n';
    }
    cout<<'\n';
    carti = Carte::alfabetic_autor(carti, n);
    cout << "Cartile ordonate alfabetic dupa autor sunt:\n";
    for( int i = 0; i<n ; i++)
    {
        cout << "<<" << carti[i].get_titlu() << ">> de " << carti[i].get_nume_autor() << '\n';
    }

    delete [] carti;
    return 0;
}
