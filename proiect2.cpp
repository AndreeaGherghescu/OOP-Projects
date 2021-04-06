#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

class Sportiv {
protected:
    char* nume;
    char* prenume;
    char* nume_sport_practicat;
    static int salariu_lunar_de_baza;

    //setteri
    void set_nume(char nume[256]);
    void set_prenume(char prenume[256]);
public:
    void set_nume_sport_practicat(char sport[256]);

    //getteri
    char* get_nume() const{return nume;}
    char* get_prenume() const{return prenume;}
    char* get_nume_sport_practicat() const{return nume_sport_practicat;}

    //constructor implicit
    Sportiv(){
        nume = nullptr;
        prenume = nullptr;
        nume_sport_practicat = nullptr;
    }
    //constructor cu parametri
    Sportiv(char nume[256], char prenume[256], char sport[256]){
        this->nume = new char[strlen(nume)+1];
        strcpy(this->nume, nume);
        this->prenume = new char[strlen(prenume)+1];
        strcpy(this->prenume, prenume);
        this->nume_sport_practicat = new char[strlen(sport)+1];
        strcpy(this->nume_sport_practicat, sport);
        cout<<"baza::constr cu param\n";
    }
    //constructor de copiere
    Sportiv (const Sportiv &ob){
        this->nume = new char[strlen(ob.nume)+1];
        strcpy(this->nume, ob.nume);
        this->prenume = new char[strlen(ob.prenume)+1];
        strcpy(this->prenume, ob.prenume);
        this->nume_sport_practicat = new char[strlen(ob.nume_sport_practicat)+1];
        strcpy(this->nume_sport_practicat, ob.nume_sport_practicat);
        cout<<"baza::constr copiere\n";
    }

    //metode
    static void citireSalariu();
    virtual float calculareSalariu(){
        return (float)12*salariu_lunar_de_baza;
    }

    //destructor
    virtual ~Sportiv ()
    {
        cout<<"baza::destr\n";
        if (this->nume != nullptr)
            delete [] this->nume;
        this->nume = nullptr;
        if (this->prenume != nullptr)
            delete [] this->prenume;
        this->prenume = nullptr;
        if (this->nume_sport_practicat != nullptr)
            delete [] this->nume_sport_practicat;
        this->nume_sport_practicat = nullptr;
    }

    //supradefiniri
    Sportiv &operator= (const Sportiv& sportiv);
    friend istream &operator>>(istream &is, Sportiv &sportiv){
        return sportiv.citire(is);
    }
    virtual istream &citire(istream &is){
        if (nume == nullptr)
            nume = new char[256];
        cout << "Numele sportivului este: "; is.getline(nume, 256);
        if (prenume == nullptr)
            prenume = new char[256];
        cout << "Prenumele sportivului este: "; is.getline(prenume,256);
        if (nume_sport_practicat == nullptr)
            nume_sport_practicat = new char[256];
        cout << "Sportul practicat de sportiv este: "; is.getline(nume_sport_practicat,256);
        return is;
    }
    friend ostream &operator<<(ostream &os, Sportiv &sportiv){
        return sportiv.afisare(os);
    }
    virtual ostream &afisare(ostream &os){
        os << "Nume sportiv: " << nume <<'\n';
        os << "Prenume sportiv: " << prenume <<'\n';
        os << "Sport practicat: " << nume_sport_practicat <<'\n';
        return os;
    };
    friend bool operator==(const Sportiv& sportiv1, const Sportiv& sportiv2);
};
int n;
Sportiv **sportivi;

int Sportiv::salariu_lunar_de_baza;
void Sportiv::citireSalariu(){
    cout << "Salariul lunar al unui sportiv este: "; cin >> salariu_lunar_de_baza;
}
void Sportiv::set_nume(char nume[256]) {
    this->nume = new char[strlen(nume)+1];
    strcpy(this->nume, nume);
}
void Sportiv::set_prenume(char prenume[256]) {
    this->prenume = new char[strlen(prenume)+1];
    strcpy(this->prenume, prenume);
}
void Sportiv::set_nume_sport_practicat(char sport[256]) {
    nume_sport_practicat = new char[strlen(sport)+1];
    strcpy(nume_sport_practicat, sport);
}
bool operator==(const Sportiv& sportiv1, const Sportiv& sportiv2){ //returnez 1 daca sunt la fel
    if (sportiv1.nume == nullptr || sportiv2.nume == nullptr)
        if ((sportiv1.nume == nullptr && sportiv2.nume != nullptr) ||
            (sportiv2.nume == nullptr && sportiv1.nume != nullptr) ||
                strcmp(sportiv1.nume,sportiv2.nume) != 0)
            return false;
    if (sportiv1.prenume == nullptr || sportiv2.prenume == nullptr)
        if ((sportiv1.prenume == nullptr && sportiv2.prenume != nullptr) ||
            (sportiv2.prenume == nullptr && sportiv1.prenume != nullptr) ||
            strcmp(sportiv1.prenume,sportiv2.prenume) != 0)
            return false;
    if (sportiv1.nume_sport_practicat == nullptr || sportiv2.nume_sport_practicat == nullptr)
        if ((sportiv1.nume_sport_practicat == nullptr && sportiv2.nume_sport_practicat != nullptr) ||
            (sportiv2.nume_sport_practicat == nullptr && sportiv1.nume_sport_practicat != nullptr) ||
            strcmp(sportiv1.nume_sport_practicat,sportiv2.nume_sport_practicat) != 0)
            return false;
    return true;
}
Sportiv& Sportiv::operator=(const Sportiv& sportiv){
    if (&sportiv == this) {
        return *this;
    }

    if (this->nume!=nullptr)
        delete [] this->nume;
    if (this->prenume != nullptr)
        delete [] this->prenume;
    if (this->nume_sport_practicat != nullptr)
        delete [] this->nume_sport_practicat;

    this->nume = new char[strlen(sportiv.nume)+1];
    strcpy(this->nume, sportiv.nume);
    this->prenume = new char[strlen(sportiv.prenume)+1];
    strcpy(this->prenume, sportiv.prenume);
    this->nume_sport_practicat = new char[strlen(sportiv.nume_sport_practicat)+1];
    strcpy(this->nume_sport_practicat, sportiv.nume_sport_practicat);

    return *this;
}

class Sportiv_Amator:public Sportiv {
    int ani_la_amatori;
public:
    //setter
    void set_ani_la_amatori(int ani);
    //getter
    int get_ani_la_amatori() const{return ani_la_amatori;}

    //constructori
    Sportiv_Amator ():Sportiv(), ani_la_amatori(0){}
    Sportiv_Amator (char nume[256], char prenume[256], char sport[256], int ani):Sportiv(nume, prenume, sport),ani_la_amatori(ani){
        //cout<<"am ajuns la derivata\n";
    }
    Sportiv_Amator (const Sportiv_Amator& ob):Sportiv(ob){
        this->ani_la_amatori = ob.ani_la_amatori;
        //cout<<"derivata::constr copiere\n";
    }

    //destructor
    ~Sportiv_Amator() override{
        //cout<<"derivata::destr\n";
        if (this->nume != nullptr)
            delete [] this->nume;
        this->nume = nullptr;
        if (this->prenume != nullptr)
            delete [] this->prenume;
        this->prenume = nullptr;
        if (this->nume_sport_practicat != nullptr)
            delete [] this->nume_sport_practicat;
        this->nume_sport_practicat = nullptr;
    }

    //supradefiniri
    Sportiv_Amator &operator= (const Sportiv_Amator& sportiv);
    virtual istream& citire(istream &is){
        if (nume == nullptr)
            nume = new char[256];
        cout << "Numele sportivului este: "; is.getline(nume, 256);
        if (prenume == nullptr)
            prenume = new char[256];
        cout << "Prenumele sportivului este: "; is.getline(prenume,256);
        if (nume_sport_practicat == nullptr)
            nume_sport_practicat = new char[256];
        cout << "Sportul practicat de sportiv este: "; is.getline(nume_sport_practicat,256);
        cout << "Numarul de ani la amatori este: "; is >> ani_la_amatori;
        is.get();
        return is;
    }
    virtual ostream &afisare(ostream &os){
        os << "Nume sportiv: " << nume <<'\n';
        os << "Prenume sportiv: " << prenume <<'\n';
        os << "Sport practicat: " << nume_sport_practicat <<'\n';
        os << "Numarul de ani la amatori: " << ani_la_amatori << '\n';
        return os;
    }
};

void Sportiv_Amator::set_ani_la_amatori(int ani){
    ani_la_amatori = ani;
}
Sportiv_Amator& Sportiv_Amator::operator=(const Sportiv_Amator& sportiv){
    if (&sportiv != this){
        this->Sportiv::operator=(sportiv);
        this->ani_la_amatori = sportiv.ani_la_amatori;
    }
    return *this;
}

class Sportiv_de_performanta:public Sportiv{
protected:
    int nr_ore_antrenament_pe_saptamana;
    int salariu;

    static const int nr_obligatoriu_ore_antrenament;
    static int prima_de_baza;

    //setteri
    void set_nr_ore_antrenament_pe_saptamana(int ore);
public:
    void set_salariu(int salariu);

    //getteri
    int get_nr_ore_antrenament_pe_saptamana() const{return nr_ore_antrenament_pe_saptamana;}
    int get_salariu() const{return salariu;}

    //constructori
    Sportiv_de_performanta():Sportiv(),nr_ore_antrenament_pe_saptamana(0),salariu(0){}
    Sportiv_de_performanta(int ore, int salariu, char nume[256], char prenume[256], char sport[256]):Sportiv(nume, prenume, sport),nr_ore_antrenament_pe_saptamana(ore),
                            salariu(salariu){}
    Sportiv_de_performanta(const Sportiv_de_performanta& ob):Sportiv(ob){
        this->nr_ore_antrenament_pe_saptamana = ob.nr_ore_antrenament_pe_saptamana;
        this->salariu = ob.salariu;
    }

    //destructor
    virtual ~Sportiv_de_performanta() override{
        if (this->nume != nullptr)
            delete [] this->nume;
        this->nume = nullptr;
        if (this->prenume != nullptr)
            delete [] this->prenume;
        this->prenume = nullptr;
        if (this->nume_sport_practicat != nullptr)
            delete [] this->nume_sport_practicat;
        this->nume_sport_practicat = nullptr;
    }

    //metoda prin care se citeste de la tastatura prima de baza
    static void citire_prima_de_baza();

    //supradefiniri
    Sportiv_de_performanta &operator= (const Sportiv_de_performanta& sportiv);
    virtual istream& citire(istream &is){
        if (nume == nullptr)
            nume = new char[256];
        cout << "Numele sportivului este: "; is.getline(nume, 256);
        if (prenume == nullptr)
            prenume = new char[256];
        cout << "Prenumele sportivului este: "; is.getline(prenume,256);
        if (nume_sport_practicat == nullptr)
            nume_sport_practicat = new char[256];
        cout << "Sportul practicat de sportiv este: "; is.getline(nume_sport_practicat,256);
        cout << "Numarul de ore de antrenament efectuate pe saptamana este: "; is >> nr_ore_antrenament_pe_saptamana;
        cout << "Salariul este: "; is >> salariu;
        is.get();
        return is;
    }
    virtual ostream &afisare(ostream &os){
        os << "Nume sportiv: " << nume <<'\n';
        os << "Prenume sportiv: " << prenume <<'\n';
        os << "Sport practicat: " << nume_sport_practicat <<'\n';
        os << "Numarul de ore de antrenament efectuate pe saptamana este: " << nr_ore_antrenament_pe_saptamana << '\n';
        os << "Salariul este: " << salariu << '\n';
        return os;
    }

    //calculare salariu anual pt sportivul de performanta
    virtual float calculareSalariu(){
        int ore_lipsa;
        if (nr_ore_antrenament_pe_saptamana >= nr_obligatoriu_ore_antrenament)
            ore_lipsa = 0;
        else
            ore_lipsa = nr_obligatoriu_ore_antrenament - nr_ore_antrenament_pe_saptamana;
        float procent;
        procent = (float)5/100*(float)salariu*4;
        if (salariu < procent*ore_lipsa)
            return 0;
        else
            return ((float)salariu - procent*ore_lipsa)*12;
    }
};
const int Sportiv_de_performanta::nr_obligatoriu_ore_antrenament = 12;
int Sportiv_de_performanta::prima_de_baza;
void Sportiv_de_performanta::citire_prima_de_baza(){
    cout << "Prima de baza a unui sportiv este: "; cin >> prima_de_baza;
}
void Sportiv_de_performanta::set_nr_ore_antrenament_pe_saptamana(int ore) {
    this->nr_ore_antrenament_pe_saptamana = ore;
}
void Sportiv_de_performanta::set_salariu(int salariu) {
    this->salariu = salariu;
}
Sportiv_de_performanta& Sportiv_de_performanta::operator=(const Sportiv_de_performanta& sportiv){
    if (&sportiv != this){
        this->Sportiv::operator=(sportiv);
        this->nr_ore_antrenament_pe_saptamana = sportiv.nr_ore_antrenament_pe_saptamana;
        this->salariu = sportiv.salariu;
    }
    return *this;
}
class Sportiv_lot_national:public Sportiv_de_performanta{
    int nr_trofee;
    float prima_performanta_anuala;

    //setteri
    void set_nr_trofee(int trofee);
public:
    void set_prima_performanta_anuala(float performanta);

    //getteri
    int get_nr_trofee() const{return nr_trofee;}
    float get_prima_performanta_anuala() const{return prima_performanta_anuala;}

    //constructori
    Sportiv_lot_national():Sportiv_de_performanta(),nr_trofee(0),prima_performanta_anuala(0){}
    Sportiv_lot_national(int trofee, float performanta, int ore, int salariu, char nume[256], char prenume[256], char sport[256]):
                    Sportiv_de_performanta(ore, salariu, nume, prenume, sport),nr_trofee(trofee),prima_performanta_anuala(performanta){}
    Sportiv_lot_national(const Sportiv_lot_national& ob):Sportiv_de_performanta(ob){
        this->nr_trofee = ob.nr_trofee;
        this->prima_performanta_anuala = ob.prima_performanta_anuala;
    }

    //destructor
    ~Sportiv_lot_national(){
        if (this->nume != nullptr)
            delete [] this->nume;
        this->nume = nullptr;
        if (this->prenume != nullptr)
            delete [] this->prenume;
        this->prenume = nullptr;
        if (this->nume_sport_practicat != nullptr)
            delete [] this->nume_sport_practicat;
        this->nume_sport_practicat = nullptr;
    }

    //overloading
    Sportiv_lot_national &operator= (const Sportiv_lot_national& sportiv);
    virtual istream& citire(istream &is){
        if (nume == nullptr)
            nume = new char[256];
        cout << "Numele sportivului este: "; is.getline(nume, 256);
        if (prenume == nullptr)
            prenume = new char[256];
        cout << "Prenumele sportivului este: "; is.getline(prenume,256);
        if (nume_sport_practicat == nullptr)
            nume_sport_practicat = new char[256];
        cout << "Sportul practicat de sportiv este: "; is.getline(nume_sport_practicat,256);
        cout << "Numarul de ore de antrenament efectuate pe saptamana este: "; is >> nr_ore_antrenament_pe_saptamana;
        cout << "Salariul este: "; is >> salariu;
        cout << "Numarul de trofee castigate este: "; is >> nr_trofee;
        cout << "Prima performanta anuala este: "; is >> prima_performanta_anuala;
        is.get();
        return is;
    }
    virtual ostream &afisare(ostream &os){
        os << "Nume sportiv: " << nume <<'\n';
        os << "Prenume sportiv: " << prenume <<'\n';
        os << "Sport practicat: " << nume_sport_practicat <<'\n';
        os << "Numarul de ore de antrenament efectuate pe saptamana este: " << nr_ore_antrenament_pe_saptamana << '\n';
        os << "Salariul este: " << salariu << '\n';
        os << "Numarul de trofee castigate este: " << nr_trofee << '\n';
        os << "Prima performanta anuala este: " << prima_performanta_anuala << '\n';
        return os;
    }

    //metoda prin care se calculeaza salariul anual al sportivului din lotul national
    float calculareSalariu();
};
void Sportiv_lot_national::set_nr_trofee(int trofee){
    this->nr_trofee = trofee;
}
void Sportiv_lot_national::set_prima_performanta_anuala(float performanta){
    prima_performanta_anuala = performanta;
}
Sportiv_lot_national& Sportiv_lot_national::operator=(const Sportiv_lot_national& sportiv){
    if (&sportiv != this){
        this->Sportiv_de_performanta::operator=(sportiv);
        this->nr_trofee = sportiv.nr_trofee;
        this->prima_performanta_anuala = sportiv.prima_performanta_anuala;
    }
    return *this;
}
float Sportiv_lot_national::calculareSalariu() {
    //cout<<"saalriu pt lot";
    int copie_trofee = nr_trofee;
    float copie_perf = prima_performanta_anuala;
    while (copie_trofee){
        copie_perf *=10;
        copie_trofee--;
    }
    return (float)salariu*12 + copie_perf;
}

void afisare_meniu(){
    cout << "Pentru a citi un vector de N sportivi introduceti: READ\n";
    cout << "Pentru a afisa vectorul de sportivi introduceti: WRITE\n";
    cout << "Pentru a adauga un sportiv introduceti: INSERT\n";
    cout << "Pentru a elimina sportivul de pozitia i introduceti: REMOVE\n";
    cout << "Pentru a afisa cel mai bogat sportiv la sfarsitul anului introduceti: SOLVE\n";
    cout << "Pentru a modifica sportivul de pe pozitia i introduceti: MODIFY\n";
    cout << "Pentru a reafisa meniul introduceti: MENU\n";
    cout << "Pentru a incheia programul introduceti: EXIT\n";
}

void read(){
    cout << "Numarul de sportivi este: "; cin >> n;
    cin.get();
    sportivi = new Sportiv*[n];
    for (int i = 0; i < n; i++){
        Sportiv sportiv1;
        cin >> sportiv1;
        sportivi[i]= new Sportiv ((Sportiv&) sportiv1);
    }
}
void write(){
    for (int i = 0; i < n; i++){
        cout << *sportivi[i];
    }
}
void insert1(){
    Sportiv* sportiv_nou;
    sportiv_nou = new Sportiv;
    cin >> *sportiv_nou;
    //insert(sportiv_nou);
    Sportiv **alta_grupa;
    n++;
    alta_grupa = new Sportiv*[n];
    for (int i = 0; i < n-1 ; i++){
        alta_grupa[i] = sportivi[i];
    }
    Sportiv** de_sters = sportivi;
    sportivi = alta_grupa;
    delete [] de_sters;

    sportivi[n-1] = sportiv_nou;
}
void insert2(){
    Sportiv_Amator* sportiv_nou;
    sportiv_nou = new Sportiv_Amator;
    cin >> *sportiv_nou;
    //insert(sportiv_nou);
    Sportiv **alta_grupa;
    n++;
    alta_grupa = new Sportiv*[n];
    for (int i = 0; i < n-1 ; i++){
        alta_grupa[i] = sportivi[i];
    }
    Sportiv** de_sters = sportivi;
    sportivi = alta_grupa;
    delete [] de_sters;

    sportivi[n-1] = sportiv_nou;
}
void insert3(){
    Sportiv_de_performanta* sportiv_nou;
    sportiv_nou = new Sportiv_de_performanta;
    cin >> *sportiv_nou;
    //insert(sportiv_nou);
    Sportiv **alta_grupa;
    n++;
    alta_grupa = new Sportiv*[n];
    for (int i = 0; i < n-1 ; i++){
        alta_grupa[i] = sportivi[i];
    }
    Sportiv** de_sters = sportivi;
    sportivi = alta_grupa;
    delete [] de_sters;

    sportivi[n-1] = sportiv_nou;
}
void insert4(){
    Sportiv_lot_national* sportiv_nou;
    sportiv_nou = new Sportiv_lot_national;
    cin >> *sportiv_nou;
    //insert(sportiv_nou);
    Sportiv **alta_grupa;
    n++;
    alta_grupa = new Sportiv*[n];
    for (int i = 0; i < n-1 ; i++){
        alta_grupa[i] = sportivi[i];
    }
    Sportiv** de_sters = sportivi;
    sportivi = alta_grupa;
    delete [] de_sters;

    sportivi[n-1] = sportiv_nou;
}
void rmv(){
    int poz;
    cout << "Introduceti numarul sportivului pe care vreti sa il stergeti "; cin >> poz; cin.get();
    if (poz < 0 || poz >= n)
        throw range_error ("Range Error");
    for (int i = poz; i < n-1 ; i++){
        sportivi[i] = sportivi [i+1];
    }
    Sportiv** alta_grupa;
    n--;
    alta_grupa = new Sportiv*[n];
    for (int i = 0; i < n; i++){
        alta_grupa[i] = sportivi[i];
    }
    Sportiv** de_sters = sportivi;
    sportivi = alta_grupa;
    delete [] de_sters;
}
void solve(){
    long long salariu_max = 0;
    int indice_sportiv;
    for (int i = 0; i < n; i++){
        if (sportivi[i]->calculareSalariu() >= salariu_max){
            salariu_max = sportivi[i]->calculareSalariu();
            indice_sportiv = i;
        }
    }
    cout << "Salariul maxim la sfarsitul anului este " << salariu_max << " obtinut de sportivul " << indice_sportiv << ":\n";
    cout << *sportivi[indice_sportiv];
}
void modify(){
    int poz;
    cout << "Introduceti numarul sportivului pe care vreti sa il modificati "; cin >> poz; cin.get();
    if (poz < 0 || poz >= n)
        throw range_error ("Range Error");
    cout << "Sportivul este:\n " << *sportivi[poz];

    if (instanceof<Sportiv_Amator>(sportivi[poz])) { //sport si ani la amatori
        Sportiv_Amator *x = dynamic_cast<Sportiv_Amator*>(sportivi[poz]);
        char sport_nou[256];
        int ani_noi;
        cout << "Pentru a schimba sportul introduceti: SPORT\n";
        cout << "Pentru a schimba numarul de ani la amatori introduceti: ANI\n";
        char opt[256];
        cin.getline(opt,256);
        if (strcmp(opt,"SPORT") == 0) {
            cout << "Introduceti noul sport: "; cin.getline(sport_nou,256);
            x->set_nume_sport_practicat(sport_nou);
        }
        else if (strcmp(opt,"ANI") == 0){
            cout << "Introduceti numarul de ani: "; cin>>ani_noi; cin.get();
            x->set_ani_la_amatori(ani_noi);
        }
        else cout<<"Nu exista aceasta posibilitate\n";
        sportivi[poz] = x;
    }
    else if (instanceof<Sportiv_lot_national>(sportivi[poz])) {  //prima si salariu
        Sportiv_lot_national *x = dynamic_cast<Sportiv_lot_national*>(sportivi[poz]);
        cout << "Pentru a schimba prima introduceti: PRIMA\n";
        cout << "Pentru a schimba salariul introduceti: SALARIU\n";
        float prima_noua;
        int salariu_nou;
        char opt[256];
        cin.getline(opt,256);
        if (strcmp(opt,"PRIMA") == 0){
            cout << "Introduceti noua prima: "; cin>>prima_noua;
            x->set_prima_performanta_anuala(prima_noua);
        }
        else if (strcmp(opt,"SALARIU") == 0){
            cout << "Introduceti nuoul salariu: "; cin>>salariu_nou; cin.get();
            x->set_salariu(salariu_nou);
        }
        else cout<<"Nu exista aceasta posibilitate\n";
        sportivi[poz] = x;
    }
    else if (instanceof<Sportiv_de_performanta>(sportivi[poz])) { //sport si salariu
        Sportiv_de_performanta *x = dynamic_cast<Sportiv_de_performanta*>(sportivi[poz]);
        cout << "Pentru a schimba sportul introduceti: SPORT\n";
        cout << "Pentru a schimba salariul introduceti: SALARIU\n";
        char sport_nou[256], opt[256];
        int salariu_nou;
        cin.getline(opt,256);
        if (strcmp(opt,"SPORT") == 0){
            cout << "Introduceti noul sport: "; cin.getline(sport_nou,256);
            x->set_nume_sport_practicat(sport_nou);
        }
        else if (strcmp(opt,"SALARIU") == 0){
            cout << "Introduceti nuoul salariu: "; cin>>salariu_nou; cin.get();
            x->set_salariu(salariu_nou);
        }
        else cout<<"Nu exista aceasta posibilitate\n";
        sportivi[poz] = x;
    }
    else if (instanceof<Sportiv>(sportivi[poz])) {  //doar sportul
        Sportiv *x = sportivi[poz];
        char sport_nou[256];
        cout << "Introduceti noul sport: "; cin.getline(sport_nou,256);
        x->set_nume_sport_practicat(sport_nou);
        sportivi[poz] = x;
    }
}
void exit(){
    for (int i = 0; i < n; i++){
        delete [] sportivi[i];
        sportivi[i]= nullptr;
    }
}
void meniu(){
    cout << "Pentru a vedea optiunile introduceti: MENU\n";
    while (true){
        char opt[256];
        try {
            cin.getline(opt, 256);
            if (strstr("MENU EXIT READ WRITE INSERT MODIFY REMOVE SOLVE",opt) == nullptr)
                throw "Comanda nu exista!";

            if (strcmp(opt,"MENU") == 0) {
                afisare_meniu();
            }
            else if (strcmp(opt,"READ") == 0){
                read();
            }
            else if (strcmp(opt,"WRITE") == 0){
                write();
            }
            else if (strcmp(opt,"INSERT") == 0) {
                cout << "Selectati tipul de sportiv pe care vreti sa il introduceti:\n";
                cout << "Introduceti 1 pentru sportiv\n";
                cout << "Introduceti 2 pentru sportiv amator\n";
                cout << "Introduceti 3 pentru sportiv de performanta\n";
                cout << "Introduceti 4 pentru sportiv de lot national\n";
                int nr;
                cin>>nr;
                cin.get();
                if (!(nr>0 && nr<=4)){
                    throw "Nu exista acest tip de sportivi!";
                }
                switch (nr){
                    case 1:
                        insert1();
                        break;
                    case 2:
                        insert2();
                        break;
                    case 3:
                        insert3();
                        break;
                    case 4:
                        insert4();
                        break;
                    default:
                        cout << "Nu exista acest tip de sportiv";
                }
            }
            else if (strcmp(opt,"REMOVE") == 0){
                rmv();
            }
            else if (strcmp(opt,"SOLVE") == 0){
                solve();
            }
            else if (strcmp(opt,"MODIFY") == 0){
                modify();
            }
            else if (strcmp(opt,"EXIT") == 0){
                exit();
                break;
            }


        } catch (const char* msg){
            cout << msg <<'\n';
        }
    }
}


int main() {
    meniu();
    /*sportivi[0] = x1;
    sportivi[1] = x2;

    Sportiv_Amator maria("a","b","c",3);
    //cout<<maria;
    maria.citireSalariu();
    float sal;
    sal=maria.calculareSalariu();
    cout<<sal;


    Sportiv_lot_national ana(2,23.5,20,2000,"a","b","c");
    cout<<ana.get_nume()<<'\n'<<ana.get_prenume()<<'\n'<<ana.get_nume_sport_practicat()<<'\n'<<ana.get_nr_ore_antrenament_pe_saptamana()<<'\n'<<ana.get_prima_performanta_anuala()<<'\n';
    nimic(ana);
    Sportiv_lot_national maria;
    maria = ana;
    cout<<maria.get_nume()<<"maria\n"<<maria.get_prenume()<<'\n'<<maria.get_nume_sport_practicat()<<'\n'<<maria.get_nr_ore_antrenament_pe_saptamana()<<'\n'<<maria.get_prima_performanta_anuala()<<'\n';
    maria = ana;
    cout<<maria.get_nume()<<"maria\n"<<maria.get_prenume()<<'\n'<<maria.get_nume_sport_practicat()<<'\n'<<maria.get_nr_ore_antrenament_pe_saptamana()<<'\n'<<maria.get_prima_performanta_anuala()<<'\n';


    Sportiv_de_performanta marian(10,2000,"marian","ionel","sah");
    cout<<marian.calculareSalariu()<<'\n';

    Sportiv_de_performanta::citire_prima_de_baza();
    Sportiv_lot_national alex(3,23.5,10,2000,"alex","mihai","inot");
    cout<<alex.calculareSalariu()<<'\n';*/
    return 0;
}
