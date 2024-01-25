#pragma once

#include "repoAbstract.h"
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <random>


using std::to_string;
using std::vector;
using std::endl;
using std::string;
using std::unordered_map;
using std::pair;


class LabRepo : public AbstractRepository {
private:
    unordered_map<string, Medicament> AllMeds;
    double prob;

public:
    /**
     * Constructorul defaul care este aoelat atunci cand nu avem parametrii
     */
    explicit LabRepo(const double& prob) : prob { prob } {};

    /**
     * Constructor de copiere
     */
    LabRepo(const LabRepo& repo_de_copiat) = delete;


    /**
     * Destructor
     */
    ~LabRepo() = default;


    /**
     * Returneaza o lista cu toate filmele
     */
    vector<Medicament> getAllMeds() override ;


    /**
     * Returneaza numarul de filme din lista
     */
    int size() override ;

    /**
     * adauga un film in listaa
     * @param film: filmul pe care il adaugam  (Movie)
     * @return -
     *
     * @trows: RepoException daca exista deja in lista un film cu acelasi nume si acelasi an al aparitiei
     */
    void adauga_repo(const Medicament& med) override ;


    /**
     * Cauta un film in lista
     *
     * Returneaza : - filmu(unic) cu titilul si anul aparitiei introdus daca exista in lista un astfel de film
     *              - RepoException daca nu exista
     *
     * @param titlu: titilul dupa care se  cauta
     * @param an_aparitie : anul dupa care se cauta
     */
    const Medicament& cauta_repo(const string& nume) override ;


    /**
     * Modificam un film din lista
     * Modificam genul si actorul principal al unui film
     *
     *@param film: filmul cu noile date
     *
     * Returneaza: -
     *
     * @throw: RepoException daca nu exista nici un fil cu titlul si anul aparitiei ca al filmului introdus
     */
    void modifica_repo(const Medicament& med) override ;

    /**
     * Sterge un film din lista
     * Sterge filmul dupa titlu si an al aparitiei
     *
     *@param titlu, an aparitie: caracteristicile unic identificabile ale filmul care trebuie sters
     *
     * @throw: RepoException daca nu exista nici un fil cu titlul si anul aparitiei ca al filmului introdus
     */
    void sterge_repo(const Medicament& med) override ;

};