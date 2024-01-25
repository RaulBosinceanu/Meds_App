#include "repo.h"
using std::endl;

using std::to_string;


int RepoMedicamente::size(){
    readAllFromFile();

    return (int)AllMeds.size();
}

vector<Medicament> RepoMedicamente::getAllMeds() {
    readAllFromFile();

    return AllMeds;
}

void RepoMedicamente::adauga_repo(const Medicament& medicament) {
    readAllFromFile();

    if (exists(medicament)){
        throw RepoException("Exista deja in lista un medicament cu titlul "+medicament.getNume()+" cu substana "
                                                                                                 "activa "+medicament.getSubstActiva()+"!\n");
    }
    AllMeds.push_back(medicament);

    writeAllToFile();
}

bool RepoMedicamente::exists(const Medicament& medicament) {
    readAllFromFile();

    try{
        cauta_repo(medicament.getNume());
        return true;
    }
    catch (RepoException&){
        return false;
    }
}

const Medicament& RepoMedicamente::cauta_repo(const string &nume) {
    readAllFromFile();

    auto MedsMatching = [=] (const Medicament& med) {
        return med.getNume() == nume;
    };
    auto f = find_if(AllMeds.begin(), AllMeds.end(), MedsMatching);
    if (f != AllMeds.end()) {
        return *f;
    }
    else{
        throw RepoException("Medicament inexistent");
    }
}

void RepoMedicamente::modifica_repo(const Medicament &medicament) {
    readAllFromFile();

    if (!exists(medicament)){
        throw RepoException("Nu exista in lista un medicament cu numele"+medicament.getNume()+" !\n" );
    }
    for (auto& f : AllMeds){
        if (f == medicament){
            f = medicament;
            break;
        }
    }

    writeAllToFile();
}

void RepoMedicamente::sterge_repo(const Medicament& nume) {
    readAllFromFile();

    for(int i = 0; i < AllMeds.size(); i++){
        if (AllMeds[i] == nume){
            AllMeds.erase(AllMeds.begin() + i);
            break;
        }
    }

    writeAllToFile();
}

void RepoMedicamente::writeAllToFile() const {
    ofstream fout(FilePath);

    if (!fout.is_open())
        throw RepoException("Fisierul Repository.txt nu a putu fi deschis!!\n");

    for (const auto& med: AllMeds) {
        fout << med.getNume() << ", " << med.getPret() << ", " << med.getProducator() << ", " <<
             med.getSubstActiva() << endl;
    }

    fout.close();
}

void RepoMedicamente::readAllFromFile() {
    ifstream fin (FilePath);
    AllMeds.clear();
    string line;
    string atribut;
    vector<string> atribute;

    while(getline(fin, line)) {
        stringstream linestream(line);
        while(getline(linestream, atribut, ',')) {
            atribute.push_back(atribut);
        }
        Medicament med{atribute[0], std::stof(atribute[1]), atribute[2].erase(0, 1),
                       atribute[3].erase(0, 1)};
        AllMeds.push_back(med);
        atribute.clear();
    }

    fin.close();
}

void RepoMedicamente::emptyFile() {
    ofstream fout(FilePath);
    fout.close();
}
