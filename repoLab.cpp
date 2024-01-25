#include "repoLab.h"


int LabRepo::size(){
    return (int)AllMeds.size();
}


vector<Medicament> LabRepo::getAllMeds() {
#include <random>
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_real_distribution<> dist(0.0, 1.0);
    double random_prob = dist(mt);// numar aleator intre [0, 1]
    cout << random_prob << " \n";

    if (random_prob < prob) {
        vector<Medicament> movies;
        for (const auto& movie: AllMeds) {
            movies.push_back(movie.second);
        }
        return movies;
    }
    else {
        throw RepoException("Nu s-a putut efectua getAllMeds!\n");
    }
}


void LabRepo::adauga_repo(const Medicament& med){
    string key = med.getNume();

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_real_distribution<> dist(0, 1);
    double random_prob = dist(mt);// numar aleator intre [0, 1]

    if (random_prob < prob) {
        if (AllMeds.find(key) != AllMeds.end()) {
            throw RepoException("Exista deja in lista un medicament cu numele " + med.getNume() + " !\n");
        }
        AllMeds.insert({key, med});
    }
    else {
        throw RepoException("Nu s-a putut efectua adauga_repo!\n");
    }
}


const Medicament& LabRepo::cauta_repo(const string& nume) {
    string key = nume;

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_real_distribution<> dist(0, 1);
    double random_prob = dist(mt);// numar aleator intre [0, 1]

    if (random_prob < prob) {

        if (AllMeds.find(key) != AllMeds.end()) {
            return AllMeds[key];
        } else {
            throw RepoException("Medicament inexistent");
        }

    }
    else {
        throw RepoException("Nu s-a putut efectua cauta_repo!\n");
    }
}

void LabRepo::modifica_repo(const Medicament& med){
    string key = med.getNume();

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_real_distribution<> dist(0, 1);
    double random_prob = dist(mt);// numar aleator intre [0, 1]

    if (random_prob < prob) {
        if ( AllMeds.find(key) != AllMeds.end()) {
            AllMeds[key] = med;
        }
        else {
            throw RepoException("Medicament inexistent");
        }
    }
    else {
        throw RepoException("Nu s-a putut efectua modifica_repo!\n");
    }
}

void LabRepo::sterge_repo(const Medicament& med){
    string key = med.getNume();

    std::mt19937 mt{ std::random_device{}() };
    std::uniform_real_distribution<> dist(0, 1);
    double random_prob = dist(mt);// numar aleator intre [0, 1]

    if (random_prob < prob) {
        {
            auto i = AllMeds.find(key);
            AllMeds.erase(i);
        }
    }
    else {
        throw RepoException("Nu s-a putut efectua sterge_repo!\n");
    }
}
