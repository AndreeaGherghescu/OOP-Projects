/*Tema 12. Se dau următoarele clase:
- Clasa Sportiv(char* nume, char*prenume, char* nume_sport_practicat);
- Sportiv_Amator(int ani_la_amatori): Sportiv
- Sportiv_de_performanta(int nr_ore_antrenament_pe_saptamana, int salariu) : Sportiv
- Sportiv_lot_national (int nr_trofee, float prima_performanta_anuala): Sportiv_de_performanta
Să se determine cel mai bogat sportiv la finalul anului, știind ca primei sportivului din lotul
        național se adaugă un 0 în coadă în funcție de numărul de trofee castigate, iar salariul lunar al
unui sportiv de performanta este conditionat de participarea la un număr minim de ore de
        antrenament pe saptamana (fiecare oră de antrenament la care nu participă îi va atrage o
                                  penalizare de 5% din salariu).  */
/*
 Cerinta bonus pentru tine este:
Se va completa structura de clase existenta cu urmatoarele clase:

- Sportiv_olimpic(int numar_participari_la_olimpiade, int numar_medalii_olimpice_de_aur) : Sportiv_de_performanta
- Sportiv_Hall_Of_Fame(int numar_recorduri_mondiale_detinute) : Sportiv_lot_national, Sportiv_olimpic

Sportivul olimpic primeste pe langa salariu si un premiu a carui valoare se calculeaza dupa formula 20 / 100 * salariu * numar_participari_la_olimpiade + 50 / 100 * numar_medalii_olimpice_de_aur.
Sportivul inclus in Hall of Fame primeste in semn de recunostiinta pentru performantele sale exceptionale pe langa un salariul lunar o suma calculata dupa formula
 1000* numar_recorduri_mondiale_detinute + 20 / 100 * salariu * numar_participari_la_olimpiade + 50 / 100 * numar_medalii_olimpice_de_aur.
 */
#include <iostream>
#include <cstring>
#include <stdexcept>
using namespace std;

template<typename Base, typename T>                     //https://stackoverflow.com/questions/500493/c-equivalent-of-javas-instanceof
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}

class Sportiv {
protected:
    char* nume;
    char* prenume;
    char* nume_sport_practicat;

    static int salariu_lunar_de_baza;

    //settere
    void set_nume(char nume[256]);
    void set_prenume(char prenume[256]);
public:
    void set_nume_sport_practicat(char sport[256]);

    //gettere
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
        //cout<<"baza::constr cu param\n";
    }
    //constructor de copiere
    Sportiv (const Sportiv &ob){
        this->nume = new char[strlen(ob.nume)+1];
        strcpy(this->nume, ob.nume);
        this->prenume = new char[strlen(ob.prenume)+1];
        strcpy(this->prenume, ob.prenume);
        this->nume_sport_practicat = new char[strlen(ob.nume_sport_practicat)+1];
        strcpy(this->nume_sport_practicat, ob.nume_sport_practicat);
        //cout<<"baza::constr copiere\n";
    }

    //metode
    static void citireSalariu();  //metoda prin care se citeste salariul lunar de baza al unui sportiv
    virtual float calculareSalariu(){  //metoda prin care se calculeaza salariul sportivului
        return (float)12*salariu_lunar_de_baza;
    }

    //destructor
    virtual ~Sportiv ()
    {
        //cout<<"baza::destr\n";
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
    friend istream &operator>>(istream &is, Sportiv &sportiv);
    friend ostream &operator<<(ostream &os, Sportiv &sportiv);
    friend bool operator==(const Sportiv& sportiv1, const Sportiv& sportiv2);
};
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
istream &operator>>(istream &is, Sportiv &sportiv){
    char nume[256], prenume[256],sport[256];
    cout << "Numele sportivului este: "; is.getline(nume,256);
    cout << "Prenumele sportivului este: "; is.getline(prenume,256);
    cout << "Sportul practicat de sportiv este: "; is.getline(sport,256);

    sportiv.nume = new char[strlen(nume) + 1];
    strcpy(sportiv.nume, nume);
    sportiv.prenume = new char[strlen(prenume) + 1];
    strcpy(sportiv.prenume, prenume);
    sportiv.nume_sport_practicat = new char[strlen(sport)+1];
    strcpy(sportiv.nume_sport_practicat, sport);
    return is;
}
ostream &operator<<(ostream &os, Sportiv &sportiv){
    os << "Nume sportiv: " << sportiv.nume <<'\n';
    os << "Prenume sportiv: " <<sportiv.prenume <<'\n';
    os << "Sport practicat: " << sportiv.nume_sport_practicat <<'\n';
    return os;
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
    ~Sportiv_Amator() {
        //cout<<"derivata::destr\n";
    }

    //supradefiniri
    Sportiv_Amator &operator= (const Sportiv_Amator& sportiv);
    friend istream &operator>>(istream &is,Sportiv_Amator &sportiv);
    friend ostream &operator<<(ostream &os,Sportiv_Amator &sportiv);
};
istream &operator>>(istream &is,Sportiv_Amator &sportiv) {
    char nume[256], prenume[256], sport[256];
    cout << "Numele sportivului este: ";
    is.getline(nume, 256);
    cout << "Prenumele sportivului este: ";
    is.getline(prenume, 256);
    cout << "Sportul practicat de sportiv este: ";
    is.getline(sport, 256);
    cout << "Numarul de ani la amatori este: ";
    is >> sportiv.ani_la_amatori;
    sportiv.nume = new char[strlen(nume) + 1];
    strcpy(sportiv.nume, nume);
    sportiv.prenume = new char[strlen(prenume) + 1];
    strcpy(sportiv.prenume, prenume);
    sportiv.nume_sport_practicat = new char[strlen(sport) + 1];
    strcpy(sportiv.nume_sport_practicat, sport);
    return is;
}
ostream &operator<<(ostream &os, Sportiv_Amator &sportiv) {
    os << "Nume sportiv: " << sportiv.nume << '\n';
    os << "Prenume sportiv: " << sportiv.prenume << '\n';
    os << "Sport practicat: " << sportiv.nume_sport_practicat << '\n';
    os << "Numar de ani la amatori: " << sportiv.ani_la_amatori << '\n';
    return os;
}
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

class Sportiv_de_performanta: public Sportiv{
protected:
    int nr_ore_antrenament_pe_saptamana;
    int salariu;

    static const int nr_obligatoriu_ore_antrenament;

public:
    //settere
    void set_nr_ore_antrenament_pe_saptamana(int ore);
    void set_salariu(int salariu);

    //gettere
    int get_nr_ore_antrenament_pe_saptamana() const{return nr_ore_antrenament_pe_saptamana;}
    int get_salariu() const{return salariu;}

    //constructori
    Sportiv_de_performanta():Sportiv(),nr_ore_antrenament_pe_saptamana(0),salariu(0){}
    Sportiv_de_performanta(int ore, int salariu, char nume[256], char prenume[256], char sport[256]):Sportiv(nume, prenume, sport),nr_ore_antrenament_pe_saptamana(ore),
                            salariu(salariu){}
    Sportiv_de_performanta(const Sportiv_de_performanta& ob):Sportiv(ob){
        cout << "constr copiere::sportiv_de_perf";
        this->nr_ore_antrenament_pe_saptamana = ob.nr_ore_antrenament_pe_saptamana;
        this->salariu = ob.salariu;
    }
    //destructor
    virtual ~Sportiv_de_performanta() {}

    //supradefiniri
    Sportiv_de_performanta &operator= (const Sportiv_de_performanta& sportiv);
    friend istream &operator>>(istream &is, Sportiv_de_performanta &sportiv);
    friend ostream &operator<<(ostream &os, Sportiv_de_performanta &sporitv);

    //calculare salariu anual pt sportivul de performanta
    virtual float calculareSalariu(){
        int ore_lipsa;
        if (nr_ore_antrenament_pe_saptamana >= nr_obligatoriu_ore_antrenament)
            ore_lipsa = 0;
        else
            ore_lipsa = nr_obligatoriu_ore_antrenament - nr_ore_antrenament_pe_saptamana;
        float procent;
        procent = (float)5/100*(float)salariu*4;
        if ((float)salariu < procent*(float)ore_lipsa)
            return 0;
        else
            return ((float)salariu - procent*(float)ore_lipsa)*12;
    }
};
const int Sportiv_de_performanta::nr_obligatoriu_ore_antrenament = 12;
void Sportiv_de_performanta::set_nr_ore_antrenament_pe_saptamana(int ore) {
    this->nr_ore_antrenament_pe_saptamana = ore;
}
void Sportiv_de_performanta::set_salariu(int salariu) {
    this->salariu = salariu;
}
istream &operator>>(istream &is,Sportiv_de_performanta &sportiv) {
    char nume[256], prenume[256], sport[256];
    cout << "Numele sportivului este: ";
    is.getline(nume, 256);
    cout << "Prenumele sportivului este: ";
    is.getline(prenume, 256);
    cout << "Sportul practicat de sportiv este: ";
    is.getline(sport, 256);
    cout << "Numarul de ore de antrenament pe saptamana este: ";
    is >> sportiv.nr_ore_antrenament_pe_saptamana;
    cout << "Salariul este: ";
    is >> sportiv.salariu;
    sportiv.nume = new char[strlen(nume) + 1];
    strcpy(sportiv.nume, nume);
    sportiv.prenume = new char[strlen(prenume) + 1];
    strcpy(sportiv.prenume, prenume);
    sportiv.nume_sport_practicat = new char[strlen(sport) + 1];
    strcpy(sportiv.nume_sport_practicat, sport);
    return is;
}
ostream &operator<<(ostream &os, Sportiv_de_performanta &sportiv) {
    os << "Nume sportiv: " << sportiv.nume << '\n';
    os << "Prenume sportiv: " << sportiv.prenume << '\n';
    os << "Sport practicat: " << sportiv.nume_sport_practicat << '\n';
    os << "Numar de ore de antrenament este: " << sportiv.nr_ore_antrenament_pe_saptamana << '\n';
    os << "Salariul este: " << sportiv.salariu << '\n';
    return os;
}
Sportiv_de_performanta& Sportiv_de_performanta::operator=(const Sportiv_de_performanta& sportiv){
    if (&sportiv != this){
        this->Sportiv::operator=(sportiv);
        this->nr_ore_antrenament_pe_saptamana = sportiv.nr_ore_antrenament_pe_saptamana;
        this->salariu = sportiv.salariu;
    }
    return *this;
}
class Sportiv_lot_national:virtual public Sportiv_de_performanta{
protected:
    int nr_trofee;
    float prima_performanta_anuala;

    //settere
    void set_nr_trofee(int trofee);
public:
    void set_prima_performanta_anuala(float performanta);

    //gettere
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
    ~Sportiv_lot_national(){}

    //overloading
    Sportiv_lot_national &operator= (const Sportiv_lot_national& sportiv);
    friend istream &operator>>(istream &is, Sportiv_lot_national &sportiv);
    friend ostream &operator<<(ostream &os, Sportiv_lot_national &sportiv);

    //metoda prin care se calculeaza salariul anual al sportivului din lotul national
    float calculareSalariu();
};
void Sportiv_lot_national::set_nr_trofee(int trofee){
    this->nr_trofee = trofee;
}
void Sportiv_lot_national::set_prima_performanta_anuala(float performanta){
    prima_performanta_anuala = performanta;
}
istream &operator>>(istream &is,Sportiv_lot_national &sportiv) {
    char nume[256], prenume[256], sport[256];
    cout << "Numele sportivului este: ";
    is.getline(nume, 256);
    cout << "Prenumele sportivului este: ";
    is.getline(prenume, 256);
    cout << "Sportul practicat de sportiv este: ";
    is.getline(sport, 256);
    cout << "Numarul de ore de antrenament pe saptamana este: ";
    is >> sportiv.nr_ore_antrenament_pe_saptamana;
    cout << "Salariul este: ";
    is >> sportiv.salariu;
    cout << "Numarul de trofee castigate este: ";
    is >> sportiv.nr_trofee;
    cout << "Prima de performanta anuala este: ";
    is >> sportiv.prima_performanta_anuala;
    sportiv.nume = new char[strlen(nume) + 1];
    strcpy(sportiv.nume, nume);
    sportiv.prenume = new char[strlen(prenume) + 1];
    strcpy(sportiv.prenume, prenume);
    sportiv.nume_sport_practicat = new char[strlen(sport) + 1];
    strcpy(sportiv.nume_sport_practicat, sport);
    return is;
}
ostream &operator<<(ostream &os, Sportiv_lot_national &sportiv) {
    os << "Nume sportiv: " << sportiv.nume << '\n';
    os << "Prenume sportiv: " << sportiv.prenume << '\n';
    os << "Sport practicat: " << sportiv.nume_sport_practicat << '\n';
    os << "Numar de ore de antrenament este: " << sportiv.nr_ore_antrenament_pe_saptamana << '\n';
    os << "Salariul este: " << sportiv.salariu << '\n';
    os << "Numarul de trofee castigate este: " << sportiv.nr_trofee << '\n';
    os << "Prima de performant anuala este: " << sportiv.prima_performanta_anuala << '\n';
    return os;
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
    //cout<<"salariu pt lot";
    int copie_trofee = nr_trofee;
    float copie_perf = prima_performanta_anuala;
    while (copie_trofee){
        copie_perf *=10;
        copie_trofee--;
    }
    return (float)salariu*12 + copie_perf;
}
class Sportiv_olimpic: virtual public Sportiv_de_performanta {
protected:
    int numar_participari_la_olimpiade;
    int numar_medalii_olimpice_de_aur;

    //settere
    void set_numar_medalii_olimpice_de_aur(int medalii);
public:
    void set_numar_participari_la_olimpiade(int participari);
    //gettere
    int get_numar_participari_la_olimpiade() const{return numar_participari_la_olimpiade;}
    int get_numar_medalii_olimpice_de_aur() const{return numar_medalii_olimpice_de_aur;}
    //constructori
    Sportiv_olimpic(): Sportiv_de_performanta(),numar_participari_la_olimpiade(0),numar_medalii_olimpice_de_aur(0){}
    Sportiv_olimpic(int participari, int medalii,int ore, int salariu, char nume[256], char prenume[256], char sport[256]):
                    Sportiv_de_performanta(ore,salariu,nume,prenume,sport),numar_participari_la_olimpiade(participari),numar_medalii_olimpice_de_aur(medalii){}

    Sportiv_olimpic(const Sportiv_olimpic &ob):Sportiv_de_performanta(ob){
        this->numar_participari_la_olimpiade = ob.numar_participari_la_olimpiade;
        this->numar_medalii_olimpice_de_aur = ob.numar_medalii_olimpice_de_aur;
    }
    //destructor
    ~Sportiv_olimpic(){}

    //overloading
    Sportiv_olimpic &operator= (const Sportiv_olimpic& sportiv);
    friend istream &operator>>(istream &is, Sportiv_olimpic &sportiv);
    friend ostream &operator<<(ostream &os, Sportiv_olimpic &sportiv);

    //metoda prin care se calculeaza salariul anual al sportivului olimpic
    float calculareSalariu();
};
void Sportiv_olimpic::set_numar_participari_la_olimpiade(int participari) {
    numar_participari_la_olimpiade = participari;
}
void Sportiv_olimpic::set_numar_medalii_olimpice_de_aur(int medalii) {
    numar_medalii_olimpice_de_aur = medalii;
}
istream &operator>>(istream &is,Sportiv_olimpic &sportiv) {
    char nume[256], prenume[256], sport[256];
    cout << "Numele sportivului este: ";
    is.getline(nume, 256);
    cout << "Prenumele sportivului este: ";
    is.getline(prenume, 256);
    cout << "Sportul practicat de sportiv este: ";
    is.getline(sport, 256);
    cout << "Numarul de ore de antrenament pe saptamana este: ";
    is >> sportiv.nr_ore_antrenament_pe_saptamana;
    cout << "Salariul este: ";
    is >> sportiv.salariu;
    cout << "Numarul de participari la olimpiade este: ";
    is >> sportiv.numar_participari_la_olimpiade;
    cout << "Numarul medaliilor olimpice de aur este: ";
    is >> sportiv.numar_medalii_olimpice_de_aur;

    sportiv.nume = new char[strlen(nume) + 1];
    strcpy(sportiv.nume, nume);
    sportiv.prenume = new char[strlen(prenume) + 1];
    strcpy(sportiv.prenume, prenume);
    sportiv.nume_sport_practicat = new char[strlen(sport) + 1];
    strcpy(sportiv.nume_sport_practicat, sport);
    return is;
}
ostream &operator<<(ostream &os, Sportiv_olimpic &sportiv) {
    os << "Nume sportiv: " << sportiv.nume << '\n';
    os << "Prenume sportiv: " << sportiv.prenume << '\n';
    os << "Sport practicat: " << sportiv.nume_sport_practicat << '\n';
    os << "Numar de ore de antrenament este: " << sportiv.nr_ore_antrenament_pe_saptamana << '\n';
    os << "Salariul este: " << sportiv.salariu << '\n';
    os << "Numarul de participari la olimpiade este: " << sportiv.numar_participari_la_olimpiade << '\n';
    os << "Numarul medaliilor olimpice de aur este: " << sportiv.numar_medalii_olimpice_de_aur << '\n';
    return os;
}
Sportiv_olimpic& Sportiv_olimpic::operator=(const Sportiv_olimpic& sportiv){
    if (&sportiv != this){
        this->Sportiv_de_performanta::operator=(sportiv);
        this->numar_participari_la_olimpiade = sportiv.numar_participari_la_olimpiade;
        this->numar_medalii_olimpice_de_aur = sportiv.numar_medalii_olimpice_de_aur;
    }
    return *this;
}
float Sportiv_olimpic::calculareSalariu() {
    float premiu;
    premiu = (float)20/100*(float)salariu*(float)numar_participari_la_olimpiade+(float)50/100*(float)numar_medalii_olimpice_de_aur;
    return (float)salariu*12+premiu;
}

class Sportiv_Hall_Of_Fame:public Sportiv_lot_national, public Sportiv_olimpic{
    int numar_recorduri_mondiale_detinute;

public:
    //setter
    void set_numar_recorduri_mondiale_detinute(int record);
    //getter
    int get_numar_recorduri_mondiale_detinute() const{return numar_recorduri_mondiale_detinute;}

    //constructori
    Sportiv_Hall_Of_Fame():Sportiv_lot_national(),Sportiv_olimpic(),numar_recorduri_mondiale_detinute(0){}
    Sportiv_Hall_Of_Fame(int recorduri, char nume[256], char prenume[256], char sport[256], int ore, int salariu, int trofee, float prima, int participari, int medalii):
                        Sportiv_de_performanta(ore, salariu, nume, prenume, sport),
                        Sportiv_lot_national(trofee, prima, ore, salariu, nume, prenume, sport),
                        Sportiv_olimpic(participari, medalii, ore, salariu, nume, prenume, sport),
                        numar_recorduri_mondiale_detinute(recorduri){}
    Sportiv_Hall_Of_Fame(const Sportiv_Hall_Of_Fame &ob):
                        Sportiv_de_performanta(ob),
                        Sportiv_lot_national(ob),
                        Sportiv_olimpic(ob){
        this->numar_recorduri_mondiale_detinute = ob.numar_recorduri_mondiale_detinute;
    }
    //destructor
    ~Sportiv_Hall_Of_Fame(){}

    //overloading
    Sportiv_Hall_Of_Fame &operator= (const Sportiv_Hall_Of_Fame &sportiv);
    friend istream &operator>>(istream &is, Sportiv_Hall_Of_Fame &sportiv);
    friend ostream &operator<<(ostream &os, Sportiv_Hall_Of_Fame &sportiv);

    //metoda prin care se calculeaza salariul anual al sportivului din Hall Of Fame
    float calculareSalariu();

};
void Sportiv_Hall_Of_Fame::set_numar_recorduri_mondiale_detinute(int record) {
    this->numar_recorduri_mondiale_detinute = record;
}
istream &operator>>(istream &is,Sportiv_Hall_Of_Fame &sportiv) {
    char nume[256], prenume[256], sport[256];
    cout << "Numele sportivului este: ";
    is.getline(nume, 256);
    cout << "Prenumele sportivului este: ";
    is.getline(prenume, 256);
    cout << "Sportul practicat de sportiv este: ";
    is.getline(sport, 256);
    cout << "Numarul de ore de antrenament pe saptamana este: ";
    is >> sportiv.nr_ore_antrenament_pe_saptamana;
    cout << "Salariul este: ";
    is >> sportiv.salariu;
    cout << "Numarul de trofee castigate este: ";
    is >> sportiv.nr_trofee;
    cout << "Prima de performanta anuala este: ";
    is >> sportiv.prima_performanta_anuala;
    cout << "Numarul de participari la olimpiade este: ";
    is >> sportiv.numar_participari_la_olimpiade;
    cout << "Numarul medaliilor olimpice de aur este: ";
    is >> sportiv.numar_medalii_olimpice_de_aur;
    cout << "Numarul de recorduri mondiale detinute este: ";
    is >> sportiv.numar_recorduri_mondiale_detinute;

    sportiv.nume = new char[strlen(nume) + 1];
    strcpy(sportiv.nume, nume);
    sportiv.prenume = new char[strlen(prenume) + 1];
    strcpy(sportiv.prenume, prenume);
    sportiv.nume_sport_practicat = new char[strlen(sport) + 1];
    strcpy(sportiv.nume_sport_practicat, sport);
    return is;
}
ostream &operator<<(ostream &os, Sportiv_Hall_Of_Fame &sportiv) {
    os << "Nume sportiv: " << sportiv.nume << '\n';
    os << "Prenume sportiv: " << sportiv.prenume << '\n';
    os << "Sport practicat: " << sportiv.nume_sport_practicat << '\n';
    os << "Numar de ore de antrenament este: " << sportiv.nr_ore_antrenament_pe_saptamana << '\n';
    os << "Salariul este: " << sportiv.salariu << '\n';
    os << "Numarul de trofee castigate este: " << sportiv.nr_trofee << '\n';
    os << "Prima de performanta anuala este: " << sportiv.prima_performanta_anuala << '\n';
    os << "Numarul de participari la olimpiade este: " << sportiv.numar_participari_la_olimpiade << '\n';
    os << "Numarul medaliilor olimpice de aur este: " << sportiv.numar_medalii_olimpice_de_aur << '\n';
    os << "Numarul de recorduri mondiale detinute este: " << sportiv.numar_recorduri_mondiale_detinute << '\n';
    return os;
}
Sportiv_Hall_Of_Fame& Sportiv_Hall_Of_Fame::operator=(const Sportiv_Hall_Of_Fame& sportiv){
    if (&sportiv != this){
        this->Sportiv_de_performanta::operator=(sportiv);
        this->Sportiv_lot_national::operator=(sportiv);
        this->Sportiv_olimpic::operator=(sportiv);
        this->numar_recorduri_mondiale_detinute = sportiv.numar_recorduri_mondiale_detinute;
    }
    return *this;
}
float Sportiv_Hall_Of_Fame::calculareSalariu() {
    float premiu;
    premiu = (float)1000*(float)numar_recorduri_mondiale_detinute+(float)salariu*20/100*(float)numar_participari_la_olimpiade+(float)50/100*(float)numar_medalii_olimpice_de_aur;
    return float(salariu)*12+premiu;
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
Sportiv** read(int &n, Sportiv **sportivi){
    cout << "Numarul de sportivi este: "; cin >> n;
    cin.get();
    sportivi = new Sportiv*[n];
    for (int i = 0; i < n; i++){
        Sportiv sportiv1;
        cin >> sportiv1;
        sportivi[i]= new Sportiv ((Sportiv&) sportiv1);  //constr de copiere
    }

    return sportivi;
}
void write(int n, Sportiv **sportivi){
    for (int i = 0; i < n; i++){
        int poz = i;
        //cout << *sportivi[i];
        if (instanceof<Sportiv_Hall_Of_Fame>(sportivi[poz])){
            Sportiv_Hall_Of_Fame *x = dynamic_cast<Sportiv_Hall_Of_Fame*>(sportivi[poz]);
            cout << *x;
        }
        else if (instanceof<Sportiv_olimpic>(sportivi[poz])){
            Sportiv_olimpic *x = dynamic_cast<Sportiv_olimpic*>(sportivi[poz]);
            cout << *x;
        }
        else if (instanceof<Sportiv_Amator>(sportivi[poz])) {
            Sportiv_Amator *x = dynamic_cast<Sportiv_Amator*>(sportivi[poz]);
            cout << *x;
        }
        else if (instanceof<Sportiv_lot_national>(sportivi[poz])) {
            Sportiv_lot_national *x = dynamic_cast<Sportiv_lot_national*>(sportivi[poz]);
            cout << *x;
        }
        else if (instanceof<Sportiv_de_performanta>(sportivi[poz])) {
            Sportiv_de_performanta *x = dynamic_cast<Sportiv_de_performanta*>(sportivi[poz]);
            cout << *x;
        }
        else if (instanceof<Sportiv>(sportivi[poz])) {
            Sportiv *x = sportivi[poz];
            cout << *x;
        }
    }
}
Sportiv** insert1(int &n, Sportiv** sportivi){
    Sportiv* sportiv_nou;
    sportiv_nou = new Sportiv;
    cin >> *sportiv_nou;
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
    return sportivi;
}
Sportiv** insert2(int &n, Sportiv** sportivi){
    Sportiv_Amator* sportiv_nou;
    sportiv_nou = new Sportiv_Amator;
    cin >> *sportiv_nou;
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
    return sportivi;
}
Sportiv** insert3(int &n, Sportiv** sportivi){
    Sportiv_de_performanta* sportiv_nou;
    sportiv_nou = new Sportiv_de_performanta;
    cin >> *sportiv_nou;
    Sportiv **alta_grupa;
    n++;
    alta_grupa = new Sportiv*[n];
    for (int i = 0; i < n-1 ; i++){
        alta_grupa[i] = sportivi[i];
    }
    Sportiv** de_sters = sportivi;
    sportivi = alta_grupa;
    delete [] de_sters;

    sportivi[n-1] = sportiv_nou; //upcasting
    return sportivi;
}
Sportiv** insert4(int &n, Sportiv** sportivi){
    Sportiv_lot_national* sportiv_nou;
    sportiv_nou = new Sportiv_lot_national;
    cin >> *sportiv_nou;
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
    return sportivi;
}
Sportiv** insert5(int &n, Sportiv** sportivi){
    Sportiv_olimpic* sportiv_nou;
    sportiv_nou = new Sportiv_olimpic;
    cin >> *sportiv_nou;
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
    return sportivi;
}
Sportiv** insert6(int &n, Sportiv** sportivi){
    Sportiv_Hall_Of_Fame* sportiv_nou;
    sportiv_nou = new Sportiv_Hall_Of_Fame;
    cin >> *sportiv_nou;
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
    return sportivi;
}
Sportiv** rmv(int &n, Sportiv** sportivi){
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
    return sportivi;
}
void solve(int n, Sportiv** sportivi){
    float salariu_max = 0, salariu;
    int indice_sportiv;
    for (int i = 0; i < n; i++){
        salariu = sportivi[i]->calculareSalariu();
        if (salariu >= salariu_max){
            salariu_max = salariu;
            indice_sportiv = i;
        }
    }
    cout << "Salariul maxim la sfarsitul anului este " << salariu_max << " obtinut de sportivul " << indice_sportiv << ":\n";
    int poz = indice_sportiv;
    if (instanceof<Sportiv_Hall_Of_Fame>(sportivi[poz])) {
        Sportiv_Hall_Of_Fame *x = dynamic_cast<Sportiv_Hall_Of_Fame*>(sportivi[poz]);
        cout << *x;
    }
    else if (instanceof<Sportiv_olimpic>(sportivi[poz])) {
        Sportiv_olimpic *x = dynamic_cast<Sportiv_olimpic*>(sportivi[poz]);
        cout << *x;
    }
    else if (instanceof<Sportiv_Amator>(sportivi[poz])) {
        Sportiv_Amator *x = dynamic_cast<Sportiv_Amator*>(sportivi[poz]);
        cout << *x;
    }
    else if (instanceof<Sportiv_lot_national>(sportivi[poz])) {
        Sportiv_lot_national *x = dynamic_cast<Sportiv_lot_national*>(sportivi[poz]);
        cout << *x;
    }
    else if (instanceof<Sportiv_de_performanta>(sportivi[poz])) {
        Sportiv_de_performanta *x = dynamic_cast<Sportiv_de_performanta*>(sportivi[poz]);
        cout << *x;
    }
    else if (instanceof<Sportiv>(sportivi[poz])) {
        Sportiv *x = sportivi[poz];
        cout << *x;
    }
}
Sportiv** modify(int n, Sportiv** sportivi){
    int poz;
    cout << "Introduceti numarul sportivului pe care vreti sa il modificati "; cin >> poz; cin.get();
    if (poz < 0 || poz >= n)
        throw range_error ("Range Error");
    cout << "Sportivul este:\n" ;
    if (instanceof<Sportiv_Hall_Of_Fame>(sportivi[poz])) {
        Sportiv_Hall_Of_Fame *x = dynamic_cast<Sportiv_Hall_Of_Fame*>(sportivi[poz]);
        cout << *x;
    }
    else if (instanceof<Sportiv_olimpic>(sportivi[poz])) {
        Sportiv_olimpic *x = dynamic_cast<Sportiv_olimpic*>(sportivi[poz]);
        cout << *x;
    }
    else if (instanceof<Sportiv_Amator>(sportivi[poz])) { //sport si ani la amatori
        Sportiv_Amator *x = dynamic_cast<Sportiv_Amator*>(sportivi[poz]);
        cout << *x;
    }
    else if (instanceof<Sportiv_lot_national>(sportivi[poz])) {  //prima si salariu
        Sportiv_lot_national *x = dynamic_cast<Sportiv_lot_national*>(sportivi[poz]);
        cout << *x;
    }
    else if (instanceof<Sportiv_de_performanta>(sportivi[poz])) { //sport si salariu
        Sportiv_de_performanta *x = dynamic_cast<Sportiv_de_performanta*>(sportivi[poz]);
        cout << *x;
    }
    else if (instanceof<Sportiv>(sportivi[poz])) {  //doar sportul
        Sportiv *x = sportivi[poz];
        cout << *x;
    }

    if (instanceof<Sportiv_Hall_Of_Fame>(sportivi[poz])) { //nr recorduri mondiale si prima
        Sportiv_Hall_Of_Fame *x = dynamic_cast<Sportiv_Hall_Of_Fame*>(sportivi[poz]);
        int record_nou;
        float prima_noua;
        char opt[256];
        cout << "Pentru a schimba prima introduceti: PRIMA\n";
        cout << "Pentru a schimba numarul de recorduri mondiale introduceti: RECORD\n";
        cin.getline(opt,256);
        if (strcmp(opt,"PRIMA") == 0) {
            cout << "Introduceti noua prima: "; cin >> prima_noua;
            x->set_prima_performanta_anuala(prima_noua);
        }
        else if (strcmp(opt,"RECORD") == 0) {
            cout << "Introduceti noul numar de recorduri mondiale: "; cin >> record_nou;
            x->set_numar_recorduri_mondiale_detinute(record_nou);
        }
        else cout<<"Nu exista aceasta posibilitate\n";
        sportivi[poz] = x;
    }
    else if (instanceof<Sportiv_olimpic>(sportivi[poz])) { //nr participari la olimp si nr ore antr
        Sportiv_olimpic *x = dynamic_cast<Sportiv_olimpic*>(sportivi[poz]);
        char opt[256];
        int participari_noi, ore_noi;
        cout << "Pentru a schimba numarul de participari la olimpiada introduceti: PARTICIPARI\n";
        cout << "Pentru a schimba numarul de ore de antrenament pe saptamana introduceti: ORE\n";
        cin.getline(opt,256);
        if (strcmp(opt,"PARTICIPARI") == 0) {
            cout << "Introduceti noul numar de participari la olimpiade: "; cin >> participari_noi;
            x->set_numar_participari_la_olimpiade(participari_noi);
        }
        else if (strcmp(opt,"ORE") == 0) {
            cout << "Introduceti noul numar de ore de antrenament pe saptamana: "; cin >> ore_noi;
            x->set_nr_ore_antrenament_pe_saptamana(ore_noi);
        }
        else cout << "Nu exista aceasta posibilitate\n";
        sportivi[poz] = x;
    }
    else if (instanceof<Sportiv_Amator>(sportivi[poz])) { //sport si ani la amatori
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
    return sportivi;
}
void exit(int n, Sportiv** sportivi){
    for (int i = 0; i < n; i++){
        delete [] sportivi[i];
        sportivi[i]= nullptr;
    }
}
void meniu(int n, Sportiv** sportivi){
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
                sportivi = read(n,sportivi);
            }
            else if (strcmp(opt,"WRITE") == 0){
                write(n,sportivi);
            }
            else if (strcmp(opt,"INSERT") == 0) {
                cout << "Selectati tipul de sportiv pe care vreti sa il introduceti:\n";
                cout << "Introduceti 1 pentru sportiv\n";
                cout << "Introduceti 2 pentru sportiv amator\n";
                cout << "Introduceti 3 pentru sportiv de performanta\n";
                cout << "Introduceti 4 pentru sportiv de lot national\n";
                cout << "Introduceti 5 pentru sportiv olimpic\n";
                cout << "Introduceti 6 pentru sportiv din Hall Of Fame\n";
                int nr;
                cin>>nr;
                cin.get();
                if (!(nr>0 && nr<=6)){
                    throw "Nu exista acest tip de sportivi!";
                }
                switch (nr){
                    case 1:
                        sportivi = insert1(n, sportivi);
                        break;
                    case 2:
                        sportivi = insert2(n, sportivi);
                        break;
                    case 3:
                        sportivi = insert3(n, sportivi);
                        break;
                    case 4:
                        sportivi = insert4(n, sportivi);
                        break;
                    case 5:
                        sportivi = insert5(n, sportivi);
                        break;
                    case 6:
                        sportivi = insert6(n, sportivi);
                        break;
                    default:
                        cout << "Nu exista acest tip de sportiv";
                        break;
                }
            }
            else if (strcmp(opt,"REMOVE") == 0){
                sportivi = rmv(n, sportivi);
            }
            else if (strcmp(opt,"SOLVE") == 0){
                solve(n,sportivi);
            }
            else if (strcmp(opt,"MODIFY") == 0){
                sportivi = modify(n, sportivi);
            }
            else if (strcmp(opt,"EXIT") == 0){
                exit(n, sportivi);
                n = 0;
                break;
            }
        } catch (const char* msg){
            cout << msg <<'\n';
        }
    }
}
int main() {
    int n = 0;
    Sportiv **sportivi;

    Sportiv::citireSalariu();
    meniu(n, sportivi);

    return 0;
}
