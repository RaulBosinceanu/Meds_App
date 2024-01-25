#pragma once

#include "repoAbstract.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using std::vector;
using std::find_if;
using std::ofstream;
using std::ifstream;
using std::stringstream;

class RepoMedicamente : public AbstractRepository{
private:
    vector <Medicament> AllMeds;
    string FilePath;
public:

    /**
     * Constructorul default care este apelat atunci cand nu avem parametrii
     */
    explicit RepoMedicamente(const string& filePath ) : FilePath{ filePath } {}

    /**
    * Constructor de copiere
    */
    RepoMedicamente(const RepoMedicamente& repo_de_copiat) = delete;

    /**
     * Destructor
     */
    ~RepoMedicamente() = default;

    /**
     * Returneaza o lista cu toate medicamentele
     */
    vector<Medicament> getAllMeds() override;

    /**
    * Returneaza nr de medicamente din lista
    */
    int size() override;

    /**
    * adauga um medicament in lista si arunca eroare daca medicamentul este deja in lista
    */
    void adauga_repo(const Medicament& medicament) override;

    /**
    * Returneaza true daca un medicament cu acelasi nume si substanta activa exista deja in lista
    */
    bool exists(const Medicament& medicament) ;

    /**
    * Cauta un medicament in lista
    */
    const Medicament& cauta_repo(const string& nume) override;

    /**
     * Modifica un medicament cu datele introduse de utilizator
     */
    void modifica_repo(const Medicament& medicament) override;

    /**
     * Sterge un medicament din lista de medicamente
     */
    void sterge_repo(const Medicament& nume) override;

    /**
     * Salveaza toate medicamentele in fisier
     */
    void writeAllToFile() const;

    /**
     * Scrie toate filmele din fisier in repo
     */
    void readAllFromFile() ;

    /**
     * Goleste un fisier
     */
    void emptyFile();
};
