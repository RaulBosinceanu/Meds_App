#pragma once

#include "service.h"
#include <unordered_map>

class UI;
typedef void(UI::* functieUI)() const;

using std::unordered_map;

class UI {
private:
    Service& service;

    unordered_map<int, functieUI> commands = {
            {1, &UI::printAllMedsUI},
            {2, &UI::adaugaUI},
            {3, &UI::cautaUI},
            {4, &UI::modificaUI},
            {5, &UI::stergeUI},
            {6, &UI::filtrareUI},
            {7, &UI::sortareUI},
            {8, &UI::adaugaCos},
            {9, &UI::golesteCos},
            {10, &UI::adaugaRandomCos},
            {11, &UI::afiseazaCos},
            {12, &UI::saveCosToFile},
            {13, &UI::pretStatistic},
            {14, &UI::undoUI}
    };

public:

    /**
     * Constructor
     */
    explicit UI(Service& service) : service{ service }{};

    /**
     * Constructor de copiere
     */
    UI(UI& ot) = delete;

    /**
    * Printeaza meniul de tip consola
    */
    static void printMenu();

    /**
    * citeste un float pana cand utilizatorul introduce corect datele
    */
    static float cin_float();

    /**
    * Citeste un string pana cand utilizatorul introduce corect datele
    */
    static string cin_string();

    /**
    * Afiseaza atributele unui film
    */
    static void printMed(const Medicament& medicament);

    /**
    * Afiseaza toate mdicamentele din lista
    */
    void printAllMedsUI() const;

    /**
    * Afiseaza o lista de medicamente
    */
    static void printMeds(const vector<Medicament>& medicament);

    /**
    * Citeste datele introduse de utilizator pentru adaugarea unui medicament si returneaza mesaje de eroare daca datele
    * sunt invalide
    */
    void adaugaUI() const;

    /**
    * Citeste datele introduse de utilizator pentru cautare unui medicament si returneaza mesaje de eroare daca datele
    * sunt invalide
    */
    void cautaUI() const;

    /**
    *  Citeste datele introduse de utilizator pentru modificarea unui medicament si returneaza mesaje de eroare daca
    *  datele sunt invalide.
    */
    void modificaUI() const;

    /**
    *  Citeste datele introduse de utilizator pentru stergerea unui medicament si returneaza mesaje de eroare daca datele
    * sunt invalide
    */
    void stergeUI() const;

    /**
    * Citeste datele introduse de utilizator pentru filtrarea medicamentelor si returneaza mesaje de eroare daca
    *  datele sunt invalide.
    */
    void filtrareUI() const;

    /**
    * Citeste datele introduse de utilizator pentru sortarea medicamentelor si returneaza mesaje de eroare daca
    *  datele sunt invalide.
    */
    void sortareUI() const;

    /**
    * Citeste numele medicamentului de adaugat in Cos
    */
    void adaugaCos() const;


    /**
    * Goleste Cos
    */
    void golesteCos() const;


    /**
    * Citeste numarul de medicamente de adaugat random in Cos
    */
    void adaugaRandomCos() const;


    /**
    * Afiseaza medicamentele din Cos
    */
    void afiseazaCos() const;


    /**
     * Citeste numele fisierului in care va fi salvata lista de dorinte
     */
    void saveCosToFile() const;

    /**
    * Afiseaza un raport al medicamentelor dupa pret
    */
    void pretStatistic() const;

    /**
    * Apeleaza functia de undo din service
    */
    void undoUI() const;



public:
    void runUI() const;

};
