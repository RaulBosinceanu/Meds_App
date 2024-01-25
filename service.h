#pragma once

#include "repo.h"
#include "validari.h"
#include "exceptii.h"
#include "cos.h"
#include "undo.h"

#include <functional>
#include <map>

using std::function;
using std::map;

class Service {
private:
    AbstractRepository& repo;
    MedicamentValidator& val;
    Cos Coscurent;
    vector<UndoAction*> undoActionList;

public:
    /**
     * Constructor
     */
    Service(AbstractRepository &repo, MedicamentValidator &val) : repo{repo}, val{val} {};

    /**
     * Constructor de copiere
     */
    Service(const Service &ser) = delete;

    /**
    * returneaza numarul de medicamente din lista
    */
    int size();

    /**
    * returneaza numarul de medicamente din lista
    */
    vector<Medicament>getAllMeds() const;

    /**
    * Adauga un medicament cu nume, pret, producator si substanta activa
    */
    void adauga_service(const string &titlu, const float &pret, const string &producator, const string &subst_activa);

    /**
     * Returneaza medicamentul care indeplineste conditiile utilizatorului
     */
    const Medicament& cauta_service(const string &nume) const;

    /**
     * Modifica elementele unui medicament cu datele introduse de utilizator
     */
    const Medicament& modifica_service(const string &nume, const float &pret, const string &producator);

    /**
     * Sterge medicamentul medicament din lista de medicamente
     */
    const Medicament& sterge_service(const string& nume);

    /**
     * Filtreaza lista de medicamente dupa filtrul intodus de utilizator
     */
    vector<Medicament> Filtrare(function<bool(const Medicament &)> filtru) const;

    /**
     *  Filtreaza lista de medicamente dupa pret
     *  Returneaza o lista de medicamente care au pretul egal cu cel introdus de utilizator
     */
    vector<Medicament> FiltrarePret(const float &pret) const;

    /**
     * Filtreaza listade medicamente dupa substanta acotiva
     * Returneaza o lista de de medicamente filtrate dupa valoarea introdusa de utilizator
     */
    vector<Medicament> FiltrareSubstActiva(const string &subst_activa) const;

    /**
     * Compara 2 nume
     */
    static bool cmpNume(const Medicament &med1, const Medicament &med2, bool reverse);

    /**
    * Compara 2 producatori
    */
    static bool cmpProducator(const Medicament &med1, const Medicament &med2, bool reverse);

    /**
    * Compara dupa substanta activa dar si dupa pret
    */
    static bool cmpSubstantaPret(const Medicament &med1, const Medicament &med2, bool reverse);

    /**
     * Sorteaza descrescator sau crescator lista de medicamente in functie de nevoia utilizatorului si dupa ce tip
     * doreste
     */
    vector<Medicament> GenericSort(function<bool(const Medicament &, const Medicament &, bool)>, bool);

    /**
     * Adauga un film cu numele nume in Wishlist
     */
    void addtoCos(const string &nume);

    /**
     * Sterge toate medicamentele din wishlist
     */
    void emptyCos();

    /**
     * Adauga un numar random de medicamente in cos
     */
    int addRandomMedsToCos(int howMany);

    /**
     * Returneaza un vector cu toate medicamentele din cos
     */
    const vector<Medicament> &getCos() const;

    /**
     * Returneaza cate medicamentele sunt in cos
     */
    int sizeOfCos() const;

    /**
     * Salveaza toate medicamentele din cos in fisierul introdus de utilizator
     */
    void saveCosToFile(const string& fileName) const;

    /**
    * Returneaza o statsistica in functie de pretul medicamentelor
    */
    map<int, Med_DTO> pretStatistic();

    /**
    * Da undo la ultima operatie efectuata care mofifica repo-ul
    */
    void undo();

    Cos& getCurrentCos() {
        return Coscurent;
    }
};
