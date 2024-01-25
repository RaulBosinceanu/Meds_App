#include "service.h"

int Service::size(){
    return repo.size();
}

vector<Medicament> Service::getAllMeds() const {
    return repo.getAllMeds();
}

void Service::adauga_service(const string &nume, const float &pret, const string &producator,
                             const string &subst_activa) {
    Medicament medicament_de_adaugat{nume, pret, producator, subst_activa};
    val.valideaza(medicament_de_adaugat);
    repo.adauga_repo(medicament_de_adaugat);
    undoActionList.push_back(new AddUndo{repo, medicament_de_adaugat});
}

const Medicament& Service::cauta_service(const string &nume) const {
    return repo.cauta_repo(nume);
}

const Medicament& Service::modifica_service(const string &nume, const float &pret, const string &producator) {
    const Medicament& medicament_de_modificat = repo.cauta_repo(nume);
    Medicament medicament_modificat{ nume, pret, producator, medicament_de_modificat.getSubstActiva()};
    val.valideaza(medicament_modificat);
    undoActionList.push_back(new ModifyUndo(repo, medicament_de_modificat));
    repo.modifica_repo(medicament_modificat);
    return medicament_de_modificat;
}

const Medicament& Service::sterge_service(const string& nume) {
    const Medicament& medicament_de_sters = repo.cauta_repo(nume);
    undoActionList.push_back(new DeleteUndo(repo, medicament_de_sters));
    repo.sterge_repo(medicament_de_sters);
    return medicament_de_sters;
}

vector<Medicament>Service::Filtrare(function<bool(const Medicament &)> filtru) const {
    vector<Medicament> filme_filtrate;
    for (const auto& medicament: repo.getAllMeds()){
        if (filtru(medicament)) {
            filme_filtrate.push_back(medicament);
        }
    }
    return filme_filtrate;}

vector<Medicament>Service::FiltrarePret(const float& pret) const {
    function<bool(const Medicament&)> filtruPret = [pret](const Medicament& medicament){return medicament.getPret() == pret;};
    return Filtrare(filtruPret);
}

vector<Medicament>Service::FiltrareSubstActiva(const string &subst_activa) const {
    return Filtrare([subst_activa](const Medicament& medicament){return medicament.getSubstActiva() == subst_activa;});
}

bool Service::cmpNume(const Medicament &med1, const Medicament &med2, bool reverse) {
    if (!reverse)
        return med1.getNume() <= med2.getNume();
    else
        return med1.getNume() >= med2.getNume();
}

bool Service::cmpProducator(const Medicament &med1, const Medicament &med2, bool reverse) {
    if (!reverse)
        return med1.getProducator() <= med2.getProducator();
    else
        return med1.getProducator() >= med2.getProducator();
}

bool Service::cmpSubstantaPret(const Medicament &med1, const Medicament &med2, bool reverse) {
    if (!reverse){
        if (med1.getSubstActiva() == med2.getSubstActiva())
            return med1.getPret() <= med2.getPret();
        else
            return med1.getSubstActiva() <= med2.getSubstActiva();
    }
    else {
        if (med1.getSubstActiva() == med2.getSubstActiva())
            return med1.getPret() >= med2.getPret();
        else
            return med1.getSubstActiva() >= med2.getSubstActiva();
    }
}

vector<Medicament> Service::GenericSort(function<bool(const Medicament &, const Medicament &, bool) > cmp, bool reverse) {
    vector<Medicament> toate_medicamentele {repo.getAllMeds()};
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for(int i = 0; i < repo.size() - 1; i++){
            if (!cmp(toate_medicamentele[i], toate_medicamentele[i+1], reverse)){
                sorted = false;
                Medicament aux{toate_medicamentele[i].getNume(), toate_medicamentele[i].getPret(),
                               toate_medicamentele[i].getProducator(), toate_medicamentele[i].getSubstActiva()};
                toate_medicamentele[i] = toate_medicamentele[i+1];
                toate_medicamentele[i+1] = aux;
            }
        }
    }
    return toate_medicamentele;}

void Service::addtoCos(const string& nume){
    Medicament med = repo.cauta_repo(nume);
    Coscurent.addMedToCos(med);
}

void Service::emptyCos() {
    Coscurent.emptyCos();
}

int Service::addRandomMedsToCos(int howMany) {
    return Coscurent.addRandomMeds(repo.getAllMeds(), howMany);
}

const vector<Medicament>& Service::getCos() const {
    return Coscurent.getAllMedsFromCos();
}

int Service::sizeOfCos() const {
    return Coscurent.sizeOfCos();
}

void Service::saveCosToFile(const string &fileName) const {
    Coscurent.saveCosToFile(fileName);
}

map<int, Med_DTO> Service::pretStatistic() {
    vector<Medicament> allMovies = repo.getAllMeds();
    map<int, Med_DTO> m;

    for (const auto& med: allMovies) {
        int pret = med.getPret();
        auto poz = m.find(pret);
        if (poz != m.end()) {
            //exista cheia in map
            m[pret].increment_count();
        }
        else
        {
            //nu exitsa cheia
            m.insert(std::make_pair(pret, Med_DTO{pret, 1}));
        }
    }
    return m;
}


//------------------------------------------------UNDO------------------------------------------------------------------

void Service::undo() {
    if ( undoActionList.empty() ) {
        throw UndoException("Nu se mai poate realizat Undo !");
    }

    UndoAction* undo_action = undoActionList.back();
    undo_action->doUndo();

    undoActionList.pop_back();
    delete undo_action;
}
