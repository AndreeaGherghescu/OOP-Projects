#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>
#include <iterator>
#include <exception>
#include <vector>
using namespace std;

class Destinatie {
protected:
    string nume_statiune;

    //setter & getter
    void set_nume_statiune(string nume);
    string get_nume_statiune () const { return nume_statiune; }
public:

    //constructori
    Destinatie ():nume_statiune(""){}
    Destinatie(string nume):nume_statiune(nume){}
    Destinatie (const Destinatie &ob){
        this->nume_statiune = ob.nume_statiune;
    }

    //overload
    friend istream &operator>> (istream &is, Destinatie &destinatie){
        return destinatie.citire(is);
    }
    virtual istream &citire (istream &is){
        cout << "Numele statiunii este: ";
        getline(is, nume_statiune);
        return is;
    }
    friend ostream &operator<< (ostream &os, Destinatie &destinatie){
        return destinatie.scriere(os);
    }
    virtual ostream &scriere (ostream &os) {
        os << "Numele statiunii alese este: " << nume_statiune << ".\n";
        return os;
    }
    Destinatie &operator= (const Destinatie &destinatie);

    //metode
    virtual float pret(int zile) = 0;

    //destructor
    virtual ~Destinatie(){
        nume_statiune.clear();
    }
};
void Destinatie::set_nume_statiune(string nume) {
    nume_statiune = nume;
}
Destinatie& Destinatie::operator=(const Destinatie& destinatie){
    if (&destinatie != this) {
        this->nume_statiune = destinatie.nume_statiune;
    }
    return *this;
}

class Destinatie_montana:public Destinatie {
    string nume_monitor;

    static const float inchiriere_ski;
    static float tarif_standard_zi;
public:
    //setter & getter
    void set_nume_monitor (string nume);
    string get_nume_monitor () const {return nume_monitor;}

    //constructori
    Destinatie_montana(): nume_monitor("") {}
    Destinatie_montana(string nume): nume_monitor(nume) {}
    Destinatie_montana(const Destinatie_montana &ob) {
        this->nume_monitor = ob.nume_monitor;
    }

    //overload
    istream& citire (istream &is);
    ostream& scriere (ostream &os);
    Destinatie_montana &operator= (const Destinatie_montana &destinatie);

    //metode
    static void citire_tarif_standard ();
    float pret(int zile);

    ~Destinatie_montana(){
        nume_monitor.clear();
    }

};
const float Destinatie_montana::inchiriere_ski = 37.5 ;
float Destinatie_montana::tarif_standard_zi;
void Destinatie_montana::set_nume_monitor(string nume) {
    nume_monitor = nume;
}
void Destinatie_montana::citire_tarif_standard() {
    cout << "Tariful standard pe o zi la o destinatie montana este: ";
    bool flag = false;
    while(!flag) {
        try {
            cin >> tarif_standard_zi;
            if (tarif_standard_zi < 0)
                throw "Nu se poate introduce o valoare negativa. Incercati din nou: ";
            else {
                flag = true;
            }
        }catch (const char* s) {
            cout << s;
        }
    }
}
istream& Destinatie_montana::citire (istream &is) {
    string nume;
    cout << "Numele monitorului este: ";
    getline(is, nume);
    this->nume_monitor = nume;
    this->Destinatie::citire(is);
    return is;
}
ostream& Destinatie_montana::scriere (ostream &os) {
    cout << "Numele monitorului este: " << this->nume_monitor << ".\n";
    this->Destinatie::scriere(os);
    return os;
}
Destinatie_montana& Destinatie_montana::operator= (const Destinatie_montana &destinatie){
    if (&destinatie != this){
        this->Destinatie::operator=(destinatie);
        this->nume_monitor = destinatie.nume_monitor;
    }
    return *this;
}
float Destinatie_montana::pret(int zile){
    return tarif_standard_zi * zile + inchiriere_ski;
}

class Destinatie_city_break:public Destinatie {
    bool cazare_centrala;

    static vector <string> nume_muzee;
    static float pret_muzeu;
    static float tarif_standard_zi;

public:
    //setter & getter
    void set_cazare_centrala (bool optiune);
    bool get_cazare_centrala () const { return cazare_centrala; }

    //constructori
    Destinatie_city_break(){}
    Destinatie_city_break(bool opt):cazare_centrala(opt){}
    Destinatie_city_break (const Destinatie_city_break &ob){
        this->cazare_centrala = ob.cazare_centrala;
    }

    //overload
    istream& citire (istream &is);
    ostream& scriere (ostream &os);
    Destinatie_city_break &operator= (const Destinatie_city_break& destinatie);

    //metode
    static void citire_pret_muzeu();
    static void citire_muzee();
    static void citire_tarif_standard ();
    float pret(int zile);

    //destructor
    ~Destinatie_city_break(){}
};
vector <string> Destinatie_city_break::nume_muzee;
float Destinatie_city_break::tarif_standard_zi;
float Destinatie_city_break::pret_muzeu;

void Destinatie_city_break::set_cazare_centrala(bool optiune) {
    cazare_centrala = optiune;
}

void Destinatie_city_break::citire_tarif_standard() {
    cout << "Tariful standard pe o zi la o destinatie city break este: ";
    bool flag = false;
    while(!flag) {
        try {
            cin >> tarif_standard_zi;
            if (tarif_standard_zi < 0)
                throw "Nu se poate introduce o valoare negativa. Incercati din nou: ";
            else {
                flag = true;
            }
        }catch (const char* s) {
            cout << s;
        }
    }
    cin.get();
}
void Destinatie_city_break::citire_pret_muzeu (){
    cout << "Pretul unui bilet la muzeu este: ";
    bool flag = false;
    while(!flag) {
        try {
            cin >> pret_muzeu;
            if (pret_muzeu < 0)
                throw "Nu se poate introduce o valoare negativa. Incercati din nou: ";
            else {
                flag = true;
            }
        }catch (const char* s) {
            cout << s;
        }
    }
    cin.get();
}
void Destinatie_city_break::citire_muzee(){
    int n;
    char nume_muzeu[256];
    cout << "Numarul de muzee ce pot fi vizitate este: "; cin >> n;
    cin.get();
    for (int i = 0; i < n; i++) {
        cout << "Numele muzeului este: "; cin.getline(nume_muzeu,256);
        nume_muzee.push_back(nume_muzeu);
    }
}
istream& Destinatie_city_break::citire (istream &is) {
    cout << "Pentru a opta pentru cazare centrala introduceti DA, altfel introduceti NU: ";
    string optiune;
    bool flag = false;
    while (!flag) {
        try {
            getline(is, optiune);
            if (!(optiune == "DA" || optiune == "NU"))
                throw "Nu exista aceasta optiune! Va rugam introduceti o optiune valida: ";
            else {
                flag = true;
            }
        }
        catch (const char* s) {
            cout << s;
        }
    }
    if (optiune == "DA") cazare_centrala = true;
    else cazare_centrala = false;
    this->Destinatie::citire(is);
    return is;
}
ostream& Destinatie_city_break::scriere (ostream &os) {
    if (cazare_centrala) cout << "Ati optat pentru cazare centrala.\n";
    else os << "Nu ati optat pentru cazare centrala.\n";
    this->Destinatie::scriere(os);
    return os;
}
Destinatie_city_break& Destinatie_city_break::operator=(const Destinatie_city_break &destinatie) {
    if (&destinatie != this) {
        this->cazare_centrala = destinatie.cazare_centrala;
        this->Destinatie::operator=(destinatie);
    }
    return *this;
}
float Destinatie_city_break::pret(int zile){
    cout << "Muzeele ce pot fi vizitate sunt: \n";
    for (int i = 0; i < nume_muzee.size(); i++){
        cout << nume_muzee[i] << '\n';
    }
    int n;
    cout << "Numarul de muzee pe care doriti sa le vizitati este: "; cin >> n;
    cin.get();
    return tarif_standard_zi * zile + pret_muzeu * n;
}

class Destinatie_la_mare:public Destinatie {
    bool croaziera;

    static const float taxa_sezlong; //per zi
    static float tarif_standard_zi;
public:
    //setter and getter
    void set_croaziera (bool croaziera);
    bool get_croaziera () const {return croaziera;}

    //constructori
    Destinatie_la_mare():croaziera(false){}
    Destinatie_la_mare(bool croaziera):croaziera(croaziera){}
    Destinatie_la_mare(const Destinatie_la_mare &ob) {
        this->croaziera = ob.croaziera;
    }

    //overload
    istream& citire (istream &is);
    ostream& scriere (ostream &os);
    Destinatie_la_mare &operator= (const Destinatie_la_mare& destinatie);

    //metode
    static void citire_tarif_standard ();
    float pret(int zile);

    //destructor
    ~Destinatie_la_mare(){}
};
const float Destinatie_la_mare::taxa_sezlong = 10;
float Destinatie_la_mare::tarif_standard_zi;

void Destinatie_la_mare::set_croaziera(bool croaziera) {
    this->croaziera = croaziera;
}
void Destinatie_la_mare::citire_tarif_standard() {
    cout << "Tariful standard pentru o zi la mare este: ";
    bool flag = false;
    while(!flag) {
        try {
            cin >> tarif_standard_zi;
            if (tarif_standard_zi < 0)
                throw "Nu se poate introduce o valoare negativa. Incercati din nou: ";
            else {
                flag = true;
            }
        }catch (const char* s) {
            cout << s;
        }
    }
    cin.get();
}
istream& Destinatie_la_mare::citire (istream &is) {
    cout << "Pentru a opta pentru croaziera introduceti DA, altfel introduceti NU: ";
    string opt;
    bool flag = false;
    while (!flag) {
        try {
            getline(is, opt);
            if (!(opt == "DA" || opt == "NU"))
                throw "Nu exista aceasta optiune! Va rugam introduceti o optiune valida: ";
            else {
                if (opt == "DA") croaziera = true;
                else croaziera = false;
                flag = true;
            }
        }
        catch (const char * str){
            cout << str;
        }
    }
    this->Destinatie::citire(is);
    return is;
}
ostream& Destinatie_la_mare::scriere (ostream &os) {
    if (croaziera) os << "Ati optat pentru croaziera.\n";
    else os << "Nu ati optat pentru croaziera.\n";
    this->Destinatie::scriere(os);
    return os;
}
Destinatie_la_mare& Destinatie_la_mare::operator=(const Destinatie_la_mare &destinatie) {
    if (&destinatie != this){
        this->croaziera = destinatie.croaziera;
        this->Destinatie::operator=(destinatie);
    }
    return *this;
}
float Destinatie_la_mare::pret (int zile) {
    return (tarif_standard_zi + taxa_sezlong) * zile;
}
class Fabrica_Destinatii {
public:
    Destinatie* createDestinatie (const string type) {
        if (type == "MUNTE") {
            return new Destinatie_montana;
        }
        else if (type == "CITY BREAK") {
            return new Destinatie_city_break;
        }
        else if (type == "MARE") {
            return new Destinatie_la_mare;
        }
        return new Destinatie_montana;
    }
};
class Rezervare {
    int nr_zile;
    Destinatie *destinatie;
    string nume_destinatie;

public:
    //settere
    void set_nr_zile(int zile);
    void set_destinatie(Destinatie *destinatie);
    void set_nume_destinatie(string destinatie);

    //gettere
    int get_nr_zile () const {return nr_zile;}
    Destinatie* get_destinatie () const {return destinatie;}
    string get_nume_destinatie () const {return nume_destinatie;}

    //constructori
    Rezervare(): nr_zile(0),destinatie(nullptr), nume_destinatie("") {}
    Rezervare(int zile, Destinatie *dest, string destinatie):
            nr_zile(zile), destinatie(dest), nume_destinatie(destinatie) {}
    Rezervare(const Rezervare &ob){
        this->nr_zile = ob.nr_zile;
        this->destinatie = ob.destinatie;
        this->nume_destinatie = ob.nume_destinatie;
    }

    //overload
    friend istream &operator>>(istream &is, Rezervare &rezervare);
    friend ostream &operator<<(ostream &os, Rezervare &rezervare);
    Rezervare &operator= (const Rezervare& rezervare);

    //metode
    float pret();
    template <typename Base>
    inline bool instanceof() {
        const Destinatie *ptr = destinatie;
        return dynamic_cast<const Base*>(ptr) != nullptr;
    }

    ~Rezervare(){
        if (destinatie != nullptr){
            delete destinatie;
        }
        destinatie = nullptr;
        nume_destinatie.clear();
    }

};
void Rezervare::set_nr_zile(int zile) {
    nr_zile = zile;
}
void Rezervare::set_destinatie(Destinatie *destinatie) {
    this->destinatie = destinatie;
}
void Rezervare::set_nume_destinatie(string destinatie){
    nume_destinatie = destinatie;
}
istream &operator>>(istream &is, Rezervare &rezervare){
    cout << "Numarul de zile al sejurului este: ";
    bool flag = false;
    while(!flag) {
        try {
            is >> rezervare.nr_zile;
            if (rezervare.nr_zile < 1)
                throw "Introduceti un numar valid de zile!\n";
            else {
                flag = true;
            }
        } catch (const char *s) {
            cout << s;
        }
    }
    is.get();
    cout << "Tipurile destinatiilor posibile sunt: MUNTE, CITY BREAK, MARE\n";
    cout << "Tipul destinatiei dorite este: ";
    string numee;
    flag = false;
    while (!flag) {
        try {
            getline(is, numee);
            if (!(numee == "MUNTE" || numee == "MARE" || numee == "CITY BREAK"))
                throw "Nu exista acest tip de destinatie! Va rugam introduceti o destinatie valida: ";
            else {
                flag = true;
                rezervare.nume_destinatie = numee;
            }
        }
        catch(const char* str){
            cout << str;
        }
    }
    Fabrica_Destinatii* fabrica = new Fabrica_Destinatii;
    rezervare.destinatie = fabrica->createDestinatie(rezervare.nume_destinatie);
    cin >> *(rezervare.destinatie);
    delete fabrica;
    return is;
}
ostream &operator<<(ostream &os, Rezervare &rezervare){
    os << "Sejurul are " << rezervare.nr_zile;
    if (rezervare.nr_zile == 1) os << " zi.\n";
    else os << " zile.\n";
    os << *(rezervare.destinatie);
    os << "Tipul destinatiei este: " << rezervare.nume_destinatie;
    os << ".\n";
    return os;
}
Rezervare& Rezervare::operator=(const Rezervare &rezervare) {
    if (&rezervare != this) {
        this->destinatie = rezervare.destinatie;
        this->nr_zile = rezervare.nr_zile;
        this->nume_destinatie = rezervare.nume_destinatie;
    }
    return *this;
}
float Rezervare::pret() {
    int zile = this->get_nr_zile();
    return this->destinatie->pret(zile);
}



template <class T>
class BookingVacante {
    static BookingVacante<T> *b_instance;

    int nr_rezervari;
    T** rezervari;

    //constructori privati
    BookingVacante():nr_rezervari(0),rezervari(nullptr){}
    BookingVacante(int nr): nr_rezervari(nr), rezervari(nullptr){}

    //operator= & copy-constructor  = delete
    BookingVacante(const BookingVacante<T>&ob) = delete;
    BookingVacante<T> &operator= (const BookingVacante<T>&ob) = delete;
public:
    ~BookingVacante() {
        nr_rezervari = 0;
        delete [] rezervari;
        if (b_instance != nullptr) {
            delete b_instance;
        }
        b_instance = nullptr;
    }

    void set_nr_rezervari () {nr_rezervari+=1;}
    void set_rezervari(T** vect) {rezervari = vect;}
    int get_nr_rezervari () const {return nr_rezervari;}
    T** get_rezervari() const {return rezervari;}

    //metode
    friend void operator+=(BookingVacante<T>& ob1, T& ob2);
    template <class S>friend istream& operator>>(istream &is, BookingVacante<S> &ob);
    template <class S>friend ostream& operator<<(ostream &os, BookingVacante<S> &ob);

    static BookingVacante<T>* getInstance() {
        if (b_instance == nullptr) {
            b_instance = new BookingVacante<T>;
        }
        return b_instance;
    }
};
template<class T> BookingVacante<T>* BookingVacante<T>::b_instance = nullptr;
template <class T>istream &operator>> (istream &is, BookingVacante<T> &ob) {
    cout << "Numarul de rezervari este: "; is >> ob.nr_rezervari;
    is.get();
    ob.rezervari = new T*[ob.nr_rezervari];
    for (int i = 0; i < ob.nr_rezervari; i++) {
        ob.rezervari[i] = new T;
        is >> *ob.rezervari[i];
    }
    return is;
}
template <class T>ostream &operator<<(ostream &os, BookingVacante<T> &ob){
    cout << "Numarul de rezervari este: " << ob.nr_rezervari << '\n';
    cout <<"Rezervarile contin: \n";
    for (int i = 0; i < ob.nr_rezervari; i++) {
        os << *ob.rezervari[i] << '\n';
    }
    return os;
}
template <class T>void operator+=(BookingVacante<T>* ob1, T& ob2){
    (*ob1).set_nr_rezervari();
    T** vacanta_noua;
    T** vacanta_veche = (*ob1).get_rezervari();
    int n = (*ob1).get_nr_rezervari();
    vacanta_noua = new T*[n];
    for (int i = 0; i < n-1 ; i++){
        vacanta_noua[i] = vacanta_veche[i];
    }
    T *x = new T;
    x = &ob2;
    vacanta_noua[n-1] = x;
    T** de_sters = vacanta_veche;
    (*ob1).set_rezervari(vacanta_noua);
    delete [] de_sters;
}

template<>
class BookingVacante<Destinatie_la_mare> {
    vector <Destinatie_la_mare*> destinatii_mare;

    static BookingVacante<Destinatie_la_mare>* m_instance;

    static int nr_destinatii;
    const int discount = 20;
    static int nr_beneficiari_discount;

    //constructori privati
    BookingVacante(){}
    BookingVacante(vector <Destinatie_la_mare*> v){
        for (int i =0; i < v.size(); i++){
            destinatii_mare.push_back(v[i]);
        }
    }

    BookingVacante(const BookingVacante<Destinatie_la_mare> &ob) = delete;
    BookingVacante<Destinatie_la_mare> &operator= (const BookingVacante<Destinatie_la_mare>&ob) = delete;
public:
    ~BookingVacante(){
        destinatii_mare.clear();
        if (m_instance != nullptr) {
            delete m_instance;
        }
        m_instance = nullptr;
    }


    //overload
    friend void operator+=(BookingVacante<Destinatie_la_mare>* ob1, Destinatie_la_mare& ob2);
    friend istream& operator>>(istream &is, BookingVacante<Destinatie_la_mare> &ob);
    friend ostream& operator<<(ostream &os, BookingVacante<Destinatie_la_mare> &ob);

    //metode
    static int afisareNrDestinatii();
    static void citireNrBeneficiari ();
    float calculPret ();

    static BookingVacante<Destinatie_la_mare>* getInstance() {
        if (m_instance == nullptr) {
            m_instance = new BookingVacante<Destinatie_la_mare>;
        }
        return m_instance;
    }
};
BookingVacante<Destinatie_la_mare>* BookingVacante<Destinatie_la_mare>::m_instance = nullptr;
int BookingVacante<Destinatie_la_mare>::nr_destinatii = 0;
int BookingVacante<Destinatie_la_mare>::nr_beneficiari_discount;
void BookingVacante<Destinatie_la_mare>::citireNrBeneficiari() {
    cout << "Se va acorda un discount de 20% primelor N rezervari la mare.\n";
    cout << "Introduceti N: ";
    bool flag = false;
    while(!flag) {
        try {
            cin >> nr_beneficiari_discount;
            if (nr_beneficiari_discount < 0)
                throw "Nu se poate introduce o valoare negativa. Incercati din nou: ";
            else {
                flag = true;
            }
        }catch (const char* s) {
            cout << s;
        }
    }
    cin.get();
}
int BookingVacante<Destinatie_la_mare>::afisareNrDestinatii() {
    return nr_destinatii;
}
void operator+=(BookingVacante<Destinatie_la_mare>* ob1, Destinatie_la_mare &ob2){
    BookingVacante<Destinatie_la_mare>::nr_destinatii+=1;
    Destinatie_la_mare *x = new Destinatie_la_mare;
    x = &ob2;
    (*ob1).destinatii_mare.push_back(x);
}
istream &operator>>(istream &is, BookingVacante<Destinatie_la_mare> &ob) {
    int nr;
    cout << "Numarul de rezervari este: "; is >> nr;
    for (int i = 0; i < nr; i++) {
        Destinatie_la_mare* x = new Destinatie_la_mare;
        cin >> *x;
        ob.destinatii_mare.push_back(x);
    }
    BookingVacante<Destinatie_la_mare>::nr_destinatii += nr;
    return is;
}
ostream &operator<<(ostream &os, BookingVacante<Destinatie_la_mare> &ob) {
    cout << "Vacantele rezervate la mare sunt: \n";
    for (int i =0; i < ob.destinatii_mare.size(); i++) {
        cout << *(ob.destinatii_mare[i]) << '\n';
    }
    return os;
}
float BookingVacante<Destinatie_la_mare>::calculPret() {
    cout << "Pretul total al excursiilor la mare este: ";
    float pret = 0;
    for (int i =0; i < destinatii_mare.size();i ++) {
        float lei = destinatii_mare[i]->pret(5);
        if (i < nr_beneficiari_discount) {
            lei = lei - 20/100 * lei;
        }
        pret += destinatii_mare[i]->pret(5);
    }
    return pret;
}
void afisare_meniu(){
    cout << "Pentru a afisa rezervarile introduceti: WRITE\n";
    cout << "Pentru a adauga n rezervari introduceti: INSERT\n";
    cout << "Pentru a elimina rezervarea cu ID-ul i introduceti: REMOVE\n";
    cout << "Pentru a afisa pretul rezervarii cu ID-ul i introduceti: SOLVE\n";
    cout << "Pentru a modifica rezervarea cu ID-ul i introduceti: MODIFY\n";
    cout << "Pentru afisarea gestiunii rezervarilor la mare introduceti: MARE\n";
    cout << "Pentru afisarea gestiunii rezervarilor la munte introduceti: MUNTE\n";
    cout << "Pentru afisarea gestiunii rezervarilor de tip city-break introduceti: CITY-BREAK\n";
    cout << "Pentru a reafisa meniul introduceti: MENU\n";
    cout << "Pentru a incheia programul introduceti: EXIT\n";
}
void write (int &n, unordered_map<int, Rezervare*>& m) {
    unordered_map <int, Rezervare*> :: iterator i;
    for (i = m.begin(); i != m.end() ; i++){
        Rezervare *p = i->second;
        cout << "Rezervarea cu ID-ul " << i->first << " este:\n";
        cout << *p <<'\n';
    }
}
void meniu (unordered_map<int, Rezervare*>& m, int n){
    BookingVacante<Destinatie_montana> *munte;
    BookingVacante<Destinatie_city_break> *city;
    BookingVacante<Destinatie_la_mare> *mare;
    munte = BookingVacante<Destinatie_montana>::getInstance();
    city = BookingVacante<Destinatie_city_break>::getInstance();
    mare = BookingVacante<Destinatie_la_mare>::getInstance();

    cout << "Pentru a vedea optiunile introduceti: MENU\n";
    while (true){
        string opt;
        try {
            getline(cin,opt);
            if (!(opt == "MENU" || opt == "EXIT" || opt == "WRITE" || opt == "INSERT" || opt == "MODIFY" ||
                    opt == "REMOVE" || opt == "SOLVE" || opt == "MARE" || opt == "MUNTE" || opt == "CITY-BREAK"))
                throw "Comanda nu exista!";

            if (opt == "MENU") {
                afisare_meniu();
            }
            else if (opt == "WRITE"){
                write(n,m);
            }
            else if (opt == "INSERT") {
                int nr;
                cout << "Introduceti numarul de rezervari pe care doriti sa le efectuati: ";
                bool flag = false;
                while (!flag) {
                    try {
                        cin >> nr;
                        if (nr < 1)
                            throw "Numarul de rezervari trebuie sa fie strict pozitiv. Introduceti din nou: ";
                        else {
                            flag = true;
                        }
                    }catch (const char* s) {
                        cout << s;
                    }
                }
                cin.get();
                for (int i = 0; i < nr ;i++){
                    Rezervare* p = new Rezervare;
                    cin >> *p;
                    int id = n + i;
                    m.insert( pair <int, Rezervare*> (id,p));
                    if ((*p).instanceof<Destinatie_montana>() ){
                        Destinatie_montana *x = dynamic_cast<Destinatie_montana*>((*p).get_destinatie());
                        munte += (*x);
                    }
                    else if ((*p).instanceof<Destinatie_city_break>()) {
                        Destinatie_city_break *x = dynamic_cast<Destinatie_city_break*>((*p).get_destinatie());
                        city += (*x);
                    }
                    else if ((*p).instanceof<Destinatie_la_mare>()) {
                        Destinatie_la_mare *x = dynamic_cast<Destinatie_la_mare*>((*p).get_destinatie());
                        mare += (*x);
                    }
                    //delete p;
                }
                n += nr;
            }
            else if (opt == "REMOVE"){
                cout << "Introduceti ID-ul rezervarii pe care doriti sa o stergeti: ";
                int id;
                unsigned long cnt;
                unordered_map<int, Rezervare> :: iterator i;
                cin >> id; cin.get();
                try {
                    cnt = m.erase(id);
                    if (!cnt)
                        throw (range_error) "";
                    cout << "Rezervare eliminata cu succes!\n";
                }catch(range_error){
                    cout << "Nu exista aceasta rezervare.\n";
                }
            }
            else if (opt == "SOLVE") { //pretul rez cu id ul i
                cout << "Introduceti ID-ul rezervarii dorite: ";
                int id;
                unordered_map<int, Rezervare*>::iterator it;
                cin >> id; cin.get();
                it = m.find(id);
                if (it == m.end()) {
                    throw "Nu exista aceasta rezervare.";
                }
                Rezervare* d;
                d = (it->second);
                if ((*d).instanceof<Destinatie_montana>() || (*d).instanceof<Destinatie_la_mare>() ) {
                    cout << "Pretul rezervarii cu ID-ul " << id << " este: " << (*d).pret() << ".\n";
                }
                else {
                    cout << "Pretul se calculeaza in functie de numarul de muzee pe care doriti sa le vizitati.\n" << (*d).pret() << '\n';
                }
            }
            else if (opt == "MODIFY"){
                int id;
                cout << "Introduceti ID-ul rezervarii pe care doriti sa o modificati: ";
                cin >> id; cin.get();
                unordered_map<int, Rezervare*>::iterator i;
                if (m.find(id) == m.end()) {
                    throw "Nu exista aceasta rezervare.";
                }
                i = m.find(id);
                Rezervare* d = (i->second);
                cout << "Rezervarea cu ID-ul " << i->first << " este:\n";
                cout << *d << '\n';
                if ((*d).instanceof<Destinatie_montana>() ) {       //modific numele monitorului
                    cout << "Introduceti numele noului monitor: ";
                    Destinatie_montana*x = dynamic_cast<Destinatie_montana*> ((*d).get_destinatie());
                    string h;
                    getline(cin, h);
                    (*x).set_nume_monitor(h);
                }
                if ((*d).instanceof<Destinatie_city_break>() ) {     //schimb optiunea pt cazare centrala
                    Destinatie_city_break *x = dynamic_cast<Destinatie_city_break*> ((*d).get_destinatie());
                    string opt;
                    bool flag = false;
                    cout << "Introduceti noua optiune pentru cazarea centrala: ";
                    while (!flag) {
                        try {
                            getline(cin, opt);
                            if (!(opt == "DA" || opt == "NU"))
                                throw "Optiunile sunt DA sau NU. Va rugam introduceti o optiune valida: ";
                            else {
                                if (opt == "DA") (*x).set_cazare_centrala(true);
                                else (*x).set_cazare_centrala(false);
                                flag = true;
                            }
                        }
                        catch (const char * str){
                            cout << str;
                        }
                    }

                }
                if ((*d).instanceof<Destinatie_la_mare>() ) { //schimb optiunea pt croaziera
                    Destinatie_la_mare *x = dynamic_cast<Destinatie_la_mare*> ((*d).get_destinatie());
                    cout << "Introduceti noua optiune pentru croaziera: ";
                    string opt;
                    bool flag = false;
                    while (!flag) {
                        try {
                            getline(cin, opt);
                            if (!(opt == "DA" || opt == "NU"))
                                throw "Optiunile sunt DA sau NU. Va rugam introduceti o optiune valida: ";
                            else {
                                if (opt == "DA") (*x).set_croaziera(true);
                                else (*x).set_croaziera(false);
                                flag = true;
                            }
                        }
                        catch (const char * str){
                            cout << str;
                        }
                    }

                }

            }
            else if (opt == "EXIT"){
                n = 0;
                break;
            }
            else if (opt == "MARE") {
                cout << "Numarul de rezervari la mare efectuate pana acum este: " << BookingVacante<Destinatie_la_mare>::afisareNrDestinatii() << ".\n";
                cout << (*mare).calculPret() << ".\n";
                cout << (*mare) << '\n';
            }
            else if (opt == "MUNTE") {
                cout << *munte << '\n';
            }
            else if (opt == "CITY-BREAK") {
                cout << *city << '\n';
            }
        } catch (const char* msg){
            cout << msg <<'\n';
        }
    }
}

int main() {
    Destinatie_montana::citire_tarif_standard();
    Destinatie_city_break::citire_pret_muzeu();
    Destinatie_city_break::citire_muzee();
    Destinatie_city_break::citire_tarif_standard();
    Destinatie_la_mare::citire_tarif_standard();
    BookingVacante<Destinatie_la_mare>::citireNrBeneficiari();

    int n = 0; //numarul de rezervari din m
    unordered_map <int, Rezervare*> m;
    meniu (m,n);
    unordered_map<int, Rezervare*> :: iterator i;
    for (i = m.begin(); i!= m.end(); i++) {
        delete i->second;
    }
    m.clear();
    return 0;
}
