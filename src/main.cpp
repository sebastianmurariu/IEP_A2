#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;

class Masina
{
protected:
    int numar_locuri;
    char categorie;
    std::string numar_de_inmatriculare;
public:
    /* Costructor clasic */
    Masina(int numar_locuri, char categorie, std::string &numar_de_inmatriculare)
    {
        this->numar_locuri= numar_locuri;
        this->categorie = categorie;
        this->numar_de_inmatriculare = numar_de_inmatriculare;
    }

    /* Costructor clasic cu initialization list */
    /* Membrii din initialization list sunt in aceeasi ordine cum sunt definiti in clasa */
    Masina()
        : numar_locuri(5),
          categorie('A'),
          numar_de_inmatriculare("TM99MXS")
    {}
    /* Copy Constructor */
    Masina(const Masina &mas)
    {
        numar_locuri = mas.numar_locuri;
        categorie = mas.categorie;
        numar_de_inmatriculare = mas.numar_de_inmatriculare;
        cout<<"Copy constructor called "<<endl;
    }

    /* Copy assignment operator -> Have assignment operators return a reference to *this. (ITEM 10) */
    Masina &operator = (const Masina &mas)
    {
        if(this == &mas) return *this; /* identity test: if a self-assignment, do nothing (ITEM 11)*/

        numar_locuri = mas.numar_locuri;
        categorie = mas.categorie;
        numar_de_inmatriculare = mas.numar_de_inmatriculare;
        cout<<"Copy Assignment Operator called "<<endl;
        return *this;

    }

    /*Destructor */
    ~Masina()
    {
        cout << "Masina distrusa \n";
    };

    void afisareMasina()
    {
        std::cout << "Masina " << numar_de_inmatriculare << " are numarul de locuri " << numar_locuri << " si este de categoria " << categorie <<".\n";
    }

    int calculImpozit()
    {
        return int(categorie)*250 + numar_locuri*10;
    }

    std::string getNrInmatriculare ()
    {
        return numar_de_inmatriculare;
    }

};

/* Copying functions should be sure to copy all of an object’s data
members and all of its base class parts!!! (ITEM 12) */

class MasinaPrezindentiala : public Masina
{
private:
    std::string personalitate;
public:
    /* Costructor clasic */
    MasinaPrezindentiala(int numar_locuri, char categorie, std::string &numar_de_inmatriculare,  std::string &personalitate)
    {
        Masina(numar_locuri,categorie,numar_de_inmatriculare);
        this->personalitate= personalitate;
    }

    /* Costructor clasic cu initialization list */
    /* Membrii din initialization list sunt in aceeasi ordine cum sunt definiti in clasa */
    MasinaPrezindentiala()
        : Masina(),
          personalitate("Ion Popescu")
    {}
    /* Copy Constructor */
    MasinaPrezindentiala(const MasinaPrezindentiala &mas)
        :   Masina(mas),
            personalitate(mas.personalitate)
    {}

    /* Copy assignment operator -> Have assignment operators return a reference to *this. (ITEM 10) */
    MasinaPrezindentiala &operator = (const MasinaPrezindentiala &mas)
    {
        if(this == &mas) return *this; /* identity test: if a self-assignment, do nothing (ITEM 11)*/

        Masina::operator = (mas);
        personalitate = mas.personalitate;
        return *this;

    }
    /*Destructor */
    ~MasinaPrezindentiala()
    {
        cout << "Masina prezidentiala distrusa \n";
    };

    void afisareMasina()
    {
        std::cout << "Masina prezidentiala duce personalitatea: "<< personalitate << numar_de_inmatriculare << " are numarul de locuri " << numar_locuri << " si este de categoria " << categorie <<".\n";
    }
};
/* Don’t try to implement one of the copying functions in terms of the
other. Instead, put common functionality in a third function that
both call. */
class FirmaDeInmatriculari
{
private:
    std::string numar_pentru_inmatriculare;
    std::string nume_firma;
    /* Costructor clasic */
    FirmaDeInmatriculari(std::string &numar_pentru_inmatriculare, std::string &nume_firma)
    {
        this->numar_pentru_inmatriculare= numar_pentru_inmatriculare;
        this->nume_firma = nume_firma;
    }
    /* ITEM12 */
    void initializareFirma(const FirmaDeInmatriculari& firma)
    {
        this->numar_pentru_inmatriculare= firma.numar_pentru_inmatriculare;
        this->nume_firma = firma.nume_firma;
    }
    /* Copy Constructor */
    FirmaDeInmatriculari(const FirmaDeInmatriculari& firma)
    {
        initializareFirma(firma); //ITEM 12!!!!
    }

    /* Copy assignment operator */
    FirmaDeInmatriculari operator=(const FirmaDeInmatriculari& firma)
    {
        if(this == &firma) return *this; /* identity test: if a self-assignment, do nothing (ITEM 11*/

        initializareFirma(firma); //ITEM 12!!!!
        return *this;
    }

    /*Destructor */
    ~FirmaDeInmatriculari()
    {
        cout << "Firma De Inmatriculari distrusa \n";
    }

    void printFirmaDeInmatriculari()
    {

        cout << nume_firma << " " << numar_pentru_inmatriculare << endl;
        cout << endl;
    }

};

int main()
{
    int numar_locuri;
    char categorie;
    std::string numar_de_inmatriculare;

    /* initializare dinamica de la tastatura */
    cout << "Introduceti datele masinii: " << '\n';
    cout << "numar_locuri = ";
    cin >> numar_locuri;
    cout << "categorie = ";
    cin >> categorie;
    cout << "numar_de_inmatriculare = ";
    cin >> numar_de_inmatriculare;
    cout<<std::endl;
    Masina m1 = Masina(numar_locuri, categorie, numar_de_inmatriculare);
    m1.afisareMasina();
    Masina m2 = m1; /* Copy Constructor called */
    m2.afisareMasina();
    Masina m3;
    m3 = m2; /* Copy Assignment Operator called  */
    m3.afisareMasina();
    cout <<"Masina cu numarul de inmatriculare " << m3.getNrInmatriculare() << " are impozitul "<< m3.calculImpozit() << " lei. \n";
    MasinaPrezindentiala M1;
    M1.afisareMasina();
    cout <<"Masina cu numarul de inmatriculare " << M1.getNrInmatriculare() << " are impozitul "<< M1.calculImpozit() << " lei. \n";
    /*
    MasinaPrezindentiala M2(M1); // Eroare  pentru ca are ca si clasa de baza pe Uncopyable si atunci Copy Costructorul este generat
                                 // automat si nu poate fi folosit
    MasinaPrezindentiala M3 = M1; // La fel si pentru Copy Assignament Operator
    */
    return 0;
}
