#include "ui.h"
#include <iostream>
#include <limits>

using std::cin;
using std::cout;
using std::ws;
using std::getline;
using std::endl;

void UI::printMenu() {
    cout << "\n\n\n\n-------------------------------------------------APLICATIE PENTRU FARMACIE---------------------"
            "---------------------------\n";
    cout << "MENIU:" << endl;
    cout << "      1. Afiseaza toate medicamentele" << endl;
    cout << "      2. Adauga un medicament" << endl;
    cout << "      3. Cauta un medicament" << endl;
    cout << "      4. Modifica un medicament" << endl;
    cout << "      5. Sterge un medicament" << endl;
    cout << "      6. Filtrarea medicamentelor dupa: " << endl;
    cout << "               a) Pret" << endl;
    cout << "               b) Substanta activa" << endl;
    cout << "      7.  Sortarea medicamentelor: " << endl;
    cout << "             Modul:" << endl;
    cout << "               i.crescator" << endl;
    cout << "               ii.descrescator" << endl;
    cout << "             Criteriul:" << endl;
    cout << "               a) Nume" << endl;
    cout << "               b) Producator" << endl;
    cout << "               c) Substanta activa + pret" << endl;
    cout << "      8. Adauga un medicament in cos " << endl;
    cout << "      9. Goleste cos " << endl;
    cout << "     10. Adauga medicamente random in cos " << endl;
    cout << "     11. Afiseaza toate medicamentele din cos " << endl;
    cout << "     12. Salveaza cos intr-un fisier " << endl;
    cout << "     13. Statistica unui pret " << endl;
    cout << "     14. Undo " << endl;
    cout << "     15. Exit" << endl;
}

float UI::cin_float() {
    float pret;
    while(true){
        cin >> pret;
        if (cin.fail()){
            cout << "Input invalid! Va rugam introduceti un pret valabil";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
            break;
    }
    return pret;
}

string UI::cin_string() {
    string s;
    getline(cin >> ws, s);
    return s;
}

void UI::printMed(const Medicament &medicament) {
    cout << "Nume: " << medicament.getNume() << " | Pret: " <<medicament.getPret()  << " | Producator: " <<
         medicament.getProducator() << " | Substanta activa: " << medicament.getSubstActiva() << endl;
}

void UI::printMeds(const vector<Medicament>& Medicamente) {
    if (Medicamente.empty())
        cout << "Nu exista medicamente in lista!\n";
    else {
        cout << "------------------------------------------------------------------------------------------"<< endl;
        for (auto& medicament: Medicamente) {
            printMed(medicament);
            cout << "------------------------------------------------------------------------------------------"<< endl;
        }
    }
}

void UI::printAllMedsUI() const {
    printMeds(service.getAllMeds());
}

void UI::adaugaUI() const {
    string nume, producator, subst_activa;
    float pret;

    cout <<"Denumirea medicamentului este: ";
    nume = cin_string();
    cout <<"Pretul medicamentului este: ";
    pret = cin_float();
    cout <<"Producatorul medicamentului este: ";
    producator = cin_string();
    cout <<"Substanta activa a medicamentului este: ";
    subst_activa = cin_string();

    service.adauga_service(nume, pret, producator, subst_activa);
    cout << "Medicamentul a fost adaugat cu succes! \n";
}

void UI::cautaUI() const {
    string nume;

    cout <<"Numele medicamentului pe care doriti sa-l cautati este: ";
    nume = cin_string();
    Medicament medicament_gasit = service.cauta_service(nume);
    printMed(medicament_gasit);
}

void UI::modificaUI() const {
    string nume, producator, subst_activa;
    float pret;

    cout <<"Denumirea medicamentului pe care doriti sa il modificati este: ";
    nume = cin_string();

    cout <<"Noul producator al medicamentului este: ";
    producator = cin_string();
    cout <<"Noul pret al medicamentului este: ";
    pret = cin_float();

    service.modifica_service(nume, pret, producator);
    cout << "Medicamentul a fost modificat cu succes! \n";
}

void UI::stergeUI() const {
    string nume;

    cout <<"Denumirea medicamentului pe care doriti sa il stergeti este: ";
    nume = cin_string();

    service.sterge_service(nume);
    cout << "Medicamentul a fost sters cu succes!\n";
}

void UI::filtrareUI() const {
    string criteriu;
    cout << "Introduceti criteriul dupa care doriti sa fie filtrate medicamentele: ";
    criteriu = cin_string();
    if (criteriu == "pret"){
        float pret;
        cout << "Introduceti pretul dupa care doriti sa fie filtrate medicamentele: ";
        pret = cin_float();
        printMeds(service.FiltrarePret(pret));
    }
    else if (criteriu == "substanta activa"){
        string subst_activa;
        cout << "Introduceti substanta activa dupa care doriti sa fie filtrate medicamentele: ";
        subst_activa = cin_string();
        printMeds(service.FiltrareSubstActiva(subst_activa));
    }
    else
        cout << "Criteriu invalid! \n";
}

void UI::sortareUI() const {
    string criteriu, rev;
    bool reverse;

    cout << "Introduceti modul dupa care doriti sa fie sortate medicamentele: ";
    rev = cin_string();
    if (rev == "crescator" )
        reverse = false;
    else
        reverse = true;

    cout << "Introduceti criteriul dupa care doriti sa fie sortate medicamentele: ";
    criteriu = cin_string();
    if (criteriu == "nume"){
        printMeds(service.GenericSort(Service::cmpNume, reverse));
    }
    else if (criteriu == "producator"){
        printMeds(service.GenericSort(Service::cmpProducator, reverse));
    }
    else if (criteriu == "subst_activa+pret"){
        printMeds(service.GenericSort(Service::cmpSubstantaPret, reverse));
    }
    else
        cout << "Criteriu invalid! \n";
}

void UI::adaugaCos() const {
    string nume;

    cout << "Introduceti numele medicamentului pe care doriti sa-l adaugati in cos: ";
    nume = cin_string();

    service.addtoCos(nume);
    cout << "Medicament adaugat in cos cu succes !" << endl;
    cout << "Numarul de medicamente din cos este: " << service.sizeOfCos();
}


void UI::golesteCos() const {
    service.emptyCos();
    cout << "Cos golit cu succes !";
}


void UI::adaugaRandomCos() const {
    int howMany;
    cout << "Introduceti numarul de medicamente adaugate random: ";
    howMany = cin_float();

    int howManyMoviesWasAdd = service.addRandomMedsToCos(howMany);
    if (howMany == howManyMoviesWasAdd) {
        cout << "Cele " << howMany << " medicamente au fost adaugate cu succes in cos !"<< endl;
        cout << "Numarul de filme din cos este: " << service.sizeOfCos();
    }
    else {
        cout << "In cos au fost adaugate doar " << howManyMoviesWasAdd << " filme !"<< endl;
        cout << "Numarul de filme din cos este: " << service.sizeOfCos();
    }
}


void UI::afiseazaCos() const {
    printMeds(service.getCos());
}


void UI::saveCosToFile() const {
    string fileName;
    cout << "Introduceti numele fisierului in care doriti sa salvati cos: ";
    fileName = cin_string();

    service.saveCosToFile(fileName);
    cout << "Cos salvat cu succes !";
}

void UI::pretStatistic() const {
    map<int, Med_DTO> map = service.pretStatistic();
    for (const auto& pair : map ) {
        cout << "Pretul "<< pair.first << " apare de " <<  pair.second.get_count() << endl;
    }
}

void UI::undoUI() const {
    service.undo();
    cout << "Undo realizat cu succes ! ";
}


void UI::runUI() const{
    int running = 1;
    int command;
    while (running){
        //system("clear");
        printMenu();
        cout << "Introduceti numarul comenzii: ";
        cin >> command;
        if (command > 15)
            cout << "Comanda invalida!\n";
        else
        if (command == 15)
            running = 0;
        else {
            try {
                (this->*commands.at(command))();
            }
            catch (RepoException &re) {
                cout << re.getMesajDeEroare();
            }
            catch (ValidatorException &ve) {
                cout << ve.getMesajDeEroare();
            }
        }
    }


}
