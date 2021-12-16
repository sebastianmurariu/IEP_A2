#include<memory>
#include<mutex>
#include<thread>
#include<iostream>

using namespace std;

mutex m;
int i = 0;

void makeATripWithASofer()
{
    m.lock();                        //m blocheaza soferul cat timp e in cursa
    cout << "Soferul " << i << " is in a trip right now" << endl;
    i++;                            //niciun alt thread nu are acces la sofer pana cand se apeleaza m.unlock()
    m.unlock();                     //se deblocheaza soferul
}

class Masina
{
protected:
    int numar_locuri;
    char categorie;
    std::string numar_de_inmatriculare;
public:
    /* Costructor clasic */
    Masina(int numar_locuri, char categorie, std::string& numar_de_inmatriculare)
    {
        this->numar_locuri = numar_locuri;
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
    Masina(const Masina& mas)
    {
        numar_locuri = mas.numar_locuri;
        categorie = mas.categorie;
        numar_de_inmatriculare = mas.numar_de_inmatriculare;
    }

    /* Copy assignment operator -> Have assignment operators return a reference to *this. (ITEM 10) */
    Masina& operator = (const Masina& mas)
    {
        if (this == &mas) return *this; /* identity test: if a self-assignment, do nothing (ITEM 11)*/

        numar_locuri = mas.numar_locuri;
        categorie = mas.categorie;
        numar_de_inmatriculare = mas.numar_de_inmatriculare;
        return *this;

    }

    /*Destructor */
    ~Masina()
    {
    };

    void afisareMasina()
    {
        std::cout << "Masina " << numar_de_inmatriculare << " are numarul de locuri " << numar_locuri << " si este de categoria " << categorie << ".\n";
    }

    int calculImpozit()
    {
        return int(categorie) * 250 + numar_locuri * 10;
    }

    std::string getNrInmatriculare()
    {
        return numar_de_inmatriculare;
    }

    int getNrLocuri()
    {
        return numar_locuri;
    }

};

class Sofer
{
private:
    std::string nume_sofer;
    Masina mas;
public:
    /* Costructor clasic */
    Sofer(std::string& nume_sofer, Masina  mas)
    {
        this->nume_sofer = nume_sofer;
        this->mas = mas;
    }

    std::shared_ptr<Masina> chooseMasinaImpozit(Masina m1, Masina m2)
    {
        std::shared_ptr<Masina> mas1 = std::make_shared<Masina>(m1);
        std::shared_ptr<Masina> mas2 = std::make_shared<Masina>(m2);
        if (m1.calculImpozit() < m2.calculImpozit())
            mas2 = mas1;
        return mas2;

    }


    std::auto_ptr<Masina> chooseMasinaNrLocuri(Masina m1, Masina m2)
    {
        std::auto_ptr<Masina> mas1(new Masina(m1));
        std::auto_ptr<Masina> mas2(new Masina(m2));
        if (m1.getNrLocuri() < m2.getNrLocuri())
            mas2 = mas1;
        return mas2;

    }
    void printSofer()
    {

        cout << nume_sofer << " ";
        mas.afisareMasina();
        cout << endl;
    }

};

int main()
{
    int numar_locuri;
    char categorie;
    std::string numar_de_inmatriculare1 = "TM99MXS";
    std::string numar_de_inmatriculare2 = "TM77AAA";
    Masina m1 = Masina(5, 'B', numar_de_inmatriculare1);
    Masina m2 = Masina(4, 'A', numar_de_inmatriculare2);
    m1.afisareMasina();
    m2.afisareMasina();
    std::string nume_sofer1 = "Dani";
    std::string nume_sofer2 = "Ionel";
    Sofer s1 = Sofer(nume_sofer1, m1);
    Sofer s2 = Sofer(nume_sofer2, m2);
    std::auto_ptr<Masina> mas4(new Masina());
    std::auto_ptr<Masina> mas5(new Masina());
    std::shared_ptr<Masina> mas3 = std::make_shared<Masina>();
    mas3 = s1.chooseMasinaImpozit(m1, m2);
    mas4 = s1.chooseMasinaNrLocuri(m1, m2);
    mas5 = mas4;
    std::cout << "mas3 points to" << mas3.get() << '\n';
    std::cout << "mas3 points to" << mas4.get() << '\n';
    std::cout << "mas3 points to" << mas5.get() << '\n';
    //mutex
    thread person1(makeATripWithASofer);
    thread person2(makeATripWithASofer);

    person1.join();
    person2.join();
    return 0;
}
