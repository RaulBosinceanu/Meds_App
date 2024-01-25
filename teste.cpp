#include "teste.h"
#include <cassert>
#include <iostream>

using namespace std;

//------------------------------------------------TESTE DOMAIN---------------------------------------------------------

void Teste::Ruleaza_teste_domain() {
    Medicament medicament{"Paracetamol", 167.5, "Par", "Ibuprofen"};
    Medicament med{};
    assert(medicament.getNume() == "Paracetamol");
    assert(medicament.getPret() == 167.5);
    assert(medicament.getProducator() == "Par");
    assert(medicament.getSubstActiva() == "Ibuprofen");

    medicament.setPret(189);
    medicament.setProducator("Far");
    assert(medicament.getPret() == 189);
    assert(medicament.getProducator() == "Far");
}

//------------------------------------------------TESTE VALIDATOR---------------------------------------------------------

void Teste::Ruleaza_teste_validator() {
    Medicament med1{"Paracetamol", 167.5, "Par", "Ibuprofen"};
    Medicament med2{"", 16, "Nur", "Ibu"};
    Medicament med3{"Nurofen", 17.6, "", "Iacobs"};
    Medicament med4{"", 167.5, "", ""};

    MedicamentValidator::valideaza(med1);
    try{
        MedicamentValidator::valideaza(med2);
        assert(false);
    }
    catch (ValidatorException&){
        assert(true);
    }


    try{
        MedicamentValidator::valideaza(med3);
        assert(false);
    }
    catch (ValidatorException&){
        assert(true);
    }


    try{
        MedicamentValidator::valideaza(med4);
        assert(false);
    }
    catch (ValidatorException&){
        assert(true);
    }
}

//------------------------------------------------TESTE REPO---------------------------------------------------------

void Teste::Ruleaza_teste_repo() {
    Ruleaza_teste_adauga_repo();
    Ruleaza_teste_cauta_repo();
    Ruleaza_teste_modifica_repo();
    Ruleaza_teste_sterge_repo();

}

void Teste::Ruleaza_teste_adauga_repo() {
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    Medicament med1{"Paracetamol", 167.5, "Par", "Ibuprofen"};
    Medicament med2{"Nurofen", 16, "Nur", "Ibu"};
    Medicament med3{"Paracetamol", 17.6, "Far", "Iacobs"};
    Medicament med4{"Ascovit", 8, "Ascutit", "Laminte"};

    repo.getAllMeds();
    repo.adauga_repo(med1);
    repo.adauga_repo(med2);
    repo.adauga_repo(med4);
    assert(repo.size() == 3);

    try{
        repo.adauga_repo(med3);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
    assert(repo.size() == 3);
}

void Teste::Ruleaza_teste_cauta_repo() {
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    Medicament med1{"Paracetamol", 167.5, "Par", "Ibuprofen"};
    Medicament med2{"Nurofen", 16, "Nur", "Ibu"};
    Medicament med3{"Algocalmin", 17.6, "Far", "Iacobs"};
    Medicament med4{"Ascovit", 8, "Ascutit", "Laminte"};

    repo.getAllMeds();
    repo.adauga_repo(med1);
    repo.adauga_repo(med2);
    repo.adauga_repo(med4);
    assert(repo.size() == 3);

    assert(med1 == repo.cauta_repo(med1.getNume()));
    assert(repo.cauta_repo(med2.getNume()) == med2);
    try{
        repo.cauta_repo("mhm");
        assert(false);
    }
    catch(RepoException&){
        assert(true);
    }
}

void Teste::Ruleaza_teste_modifica_repo() {
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    Medicament med1{"Paracetamol", 167.5, "Par", "Ibuprofen"};
    Medicament med2{"Nurofen", 16, "Nur", "Ibu"};
    Medicament med1_modificat{"Paracetamol", 17.6, "Far", "Ibuprofen"};
    Medicament med4{"Ascovit", 8, "Ascutit", "Laminte"};

    repo.adauga_repo(med1);
    repo.adauga_repo(med2);
    repo.adauga_repo(med4);

    repo.modifica_repo(med1_modificat);
    assert(repo.size() == 3);
    assert(med1_modificat == repo.cauta_repo(med1.getNume()));
    try{
        repo.modifica_repo(Medicament {"ups", 128, "pp", "ww"});
        assert(false);
    }
    catch(RepoException&){
        assert(true);
    }
}

void Teste::Ruleaza_teste_sterge_repo() {
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    Medicament med1{"Paracetamol", 167.5, "Par", "Ibuprofen"};
    Medicament med2{"Nurofen", 16, "Nur", "Ibu"};
    Medicament med4{"Ascovit", 8, "Ascutit", "Laminte"};

    repo.adauga_repo(med1);
    repo.adauga_repo(med2);
    repo.adauga_repo(med4);
    assert(repo.size() == 3);

    repo.sterge_repo(med2);
    assert(repo.size() == 2);
    repo.sterge_repo(med1);
    assert(repo.size() == 1);

}


//------------------------------------------------TESTE LAB REPO---------------------------------------------------------

void Teste::Ruleaza_teste_lab_repo() {
    Ruleaza_teste_adauga_lab_repo();
    Ruleaza_teste_cauta_lab_repo();
    Ruleaza_teste_modifica_lab_repo();
    Ruleaza_teste_sterge_lab_repo();

}

void Teste::Ruleaza_teste_adauga_lab_repo() {
    LabRepo repo{1};
    Medicament med1{"Paracetamol", 167.5, "Par", "Ibuprofen"};
    Medicament med2{"Nurofen", 16, "Nur", "Ibu"};
    Medicament med3{"Paracetamol", 17.6, "Far", "Iacobs"};
    Medicament med4{"Ascovit", 8, "Ascutit", "Laminte"};

    repo.adauga_repo(med1);
    repo.adauga_repo(med2);
    repo.adauga_repo(med4);
    assert(repo.size() == 3);
    repo.getAllMeds();

    try{
        repo.adauga_repo(med3);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
    assert(repo.size() == 3);

    LabRepo repo0{0};
    try {
        repo0.getAllMeds();
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }

    try {
        repo0.adauga_repo(med1);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
    try {
        repo0.adauga_repo(med2);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
    try {
        repo0.adauga_repo(med3);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
    try {
        repo0.size();
        assert(true);
    }
    catch (RepoException&) {
        assert(true);
    }
    try {
        repo0.getAllMeds();
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}

void Teste::Ruleaza_teste_cauta_lab_repo() {
    LabRepo repo{1};
    Medicament med1{"Paracetamol", 167.5, "Par", "Ibuprofen"};
    Medicament med2{"Nurofen", 16, "Nur", "Ibu"};
    Medicament med3{"Algocalmin", 17.6, "Far", "Iacobs"};
    Medicament med4{"Ascovit", 8, "Ascutit", "Laminte"};

    repo.getAllMeds();
    repo.adauga_repo(med1);
    repo.adauga_repo(med2);
    repo.adauga_repo(med4);
    assert(repo.size() == 3);

    assert(med1 == repo.cauta_repo(med1.getNume()));
    assert(repo.cauta_repo(med2.getNume()) == med2);
    try{
        repo.cauta_repo("mhm");
        assert(false);
    }
    catch(RepoException&){
        assert(true);
    }

    LabRepo repo1{0};
    try{
        repo1.cauta_repo(med1.getNume());
        assert(true);
    }
    catch (RepoException&) {
        assert(true);
    }
}

void Teste::Ruleaza_teste_modifica_lab_repo() {
    LabRepo repo{1};
    Medicament med1{"Paracetamol", 167.5, "Par", "Ibuprofen"};
    Medicament med2{"Nurofen", 16, "Nur", "Ibu"};
    Medicament med1_modificat{"Paracetamol", 17.6, "Far", "Ibuprofen"};
    Medicament med4{"Ascovit", 8, "Ascutit", "Laminte"};

    repo.adauga_repo(med1);
    repo.adauga_repo(med2);
    repo.adauga_repo(med4);

    repo.modifica_repo(med1_modificat);
    assert(repo.size() == 3);
    assert(med1_modificat == repo.cauta_repo(med1.getNume()));
    try{
        repo.modifica_repo(Medicament {"ups", 128, "pp", "ww"});
        assert(false);
    }
    catch(RepoException&){
        assert(true);
    }
    assert(med1_modificat == repo.cauta_repo(med1.getNume()));

    LabRepo repo0{0};
    try {
        repo0.modifica_repo(med1_modificat);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }
}

void Teste::Ruleaza_teste_sterge_lab_repo() {
    LabRepo repo{1};
    Medicament med1{"Paracetamol", 167.5, "Par", "Ibuprofen"};
    Medicament med2{"Nurofen", 16, "Nur", "Ibu"};
    Medicament med4{"Ascovit", 8, "Ascutit", "Laminte"};

    repo.adauga_repo(med1);
    repo.adauga_repo(med2);
    repo.adauga_repo(med4);
    assert(repo.size() == 3);

    repo.sterge_repo(med2);
    assert(repo.size() == 2);
    repo.sterge_repo(med1);
    assert(repo.size() == 1);
    LabRepo repo1{0};

    LabRepo repo0{0};
    try {
        repo0.sterge_repo(med1);
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }

}

//------------------------------------------------TESTE SERVICE---------------------------------------------------------

void Teste::Ruleaza_teste_service() {
    Ruleaza_teste_adauga_service();
    Ruleaza_teste_cauta_service();
    Ruleaza_teste_modifica_service();
    Ruleaza_teste_sterge_service();
    Ruleaza_teste_filtrare_service();
    Ruleaza_teste_sortare_service();
    Ruleaza_teste_adauga_cos();
    Ruleaza_teste_goleste_cos();
    Ruleaza_teste_adauga_random_cos();
    Ruleaza_teste_salveaza_cos_in_fisier();
    Ruleaza_teste_pretStatistic();
    Ruleaza_teste_undo();
}

void Teste::Ruleaza_teste_adauga_service() {
    string nume1 = "Paracetamol", nume2 = "Nurofen", nume3 = "Algocalmin", nume_invalid;
    float pret1 = 14, pret2 = 28, pret3 = 11.5, pret_invalid = -16;
    string producator1 = "Para", producator2 = "Nuro", producator3 = "Algo", producator_invalid;
    string subst_activa1 = "Ibuprofen", subst_activa2 = "alcool", subst_activa3 = "Melatinina", subst_activa_invalida;

    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};

    assert(service.size() == 0);

    service.adauga_service(nume1, pret1,producator1, subst_activa1);
    service.adauga_service(nume2, pret2,producator2, subst_activa2);
    service.adauga_service(nume3, pret3,producator3, subst_activa3);
    assert(service.size() == 3);

    try{
        service.adauga_service(nume_invalid, pret_invalid, producator_invalid, subst_activa_invalida);
        assert(false);
    }
    catch (ValidatorException&){
        assert(true);
    }

    try {
        service.adauga_service(nume3, pret3, producator3, subst_activa3);
        assert(false);
    }
    catch (RepoException&){
        assert(true);
    }
}

void Teste::Ruleaza_teste_cauta_service() {
    string nume1 = "Paracetamol", nume2 = "Nurofen", nume3 = "Algocalmin", nume_invalid;
    float pret1 = 14, pret2 = 28, pret3 = 11.5;
    string producator1 = "Para", producator2 = "Nuro", producator3 = "Algo", producator_invalid;
    string subst_activa1 = "Ibuprofen", subst_activa2 = "alcool", subst_activa3 = "Melatinina", subst_activa_invalida;

    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};

    vector<Medicament> toate_medicamentele = service.getAllMeds();
    assert(toate_medicamentele.empty());
    assert(service.size() == 0);

    service.adauga_service(nume1, pret1, producator1, subst_activa1);
    service.adauga_service(nume2, pret2, producator2, subst_activa2);
    service.adauga_service(nume3, pret3, producator3, subst_activa3);

    Medicament med1{nume1, pret1, producator1, subst_activa1};
    assert(med1 == service.cauta_service(nume1));

    try {
        service.cauta_service("bum");
        assert(false);
    }
    catch (RepoException &) {
        assert(true);
    }
}

void Teste::Ruleaza_teste_modifica_service() {
    string nume1 = "Paracetamol", nume2 = "Nurofen", nume3 = "Algocalmin", nume_invalid;
    float pret1 = 14, pret2 = 28, pret3 = 11.5;
    string producator1 = "Para", producator2 = "Nuro", producator3 = "Algo", producator_invalid;
    string subst_activa1 = "Ibuprofen", subst_activa2 = "alcool", subst_activa3 = "Melatinina", subst_activa_invalida;

    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};

    assert(service.size() == 0);

    service.adauga_service(nume1, pret1,producator1, subst_activa1);
    service.adauga_service(nume2, pret2,producator2, subst_activa2);
    service.adauga_service(nume3, pret3,producator3, subst_activa3);

    service.modifica_service(nume3, 12, "Usr");
    Medicament medicament_modificat{nume3, 12, "Usr", subst_activa3};
    assert(service.cauta_service(nume3) == medicament_modificat);

    try{
        service.modifica_service(nume3, -2, "");
        assert(false);
    }
    catch (ValidatorException&){
        assert(true);
    }

    try {
        service.modifica_service("alpha", pret3, producator3);
        assert(false);
    }
    catch (RepoException&){
        assert(true);
    }

    vector<Medicament> toate_medicamentele = service.getAllMeds();
    assert(toate_medicamentele.size() == 3);
}

void Teste::Ruleaza_teste_sterge_service() {
    string nume1 = "Paracetamol", nume2 = "Nurofen", nume3 = "Algocalmin", nume_invalid;
    float pret1 = 14, pret2 = 28, pret3 = 11.5;
    string producator1 = "Para", producator2 = "Nuro", producator3 = "Algo", producator_invalid;
    string subst_activa1 = "Ibuprofen", subst_activa2 = "alcool", subst_activa3 = "Melatinina", subst_activa_invalida;

    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};

    assert(service.size() == 0);

    service.adauga_service(nume1, pret1,producator1, subst_activa1);
    service.adauga_service(nume2, pret2,producator2, subst_activa2);
    service.adauga_service(nume3, pret3,producator3, subst_activa3);

    assert(service.size() == 3);
    service.sterge_service(nume3);
    assert(service.size() == 2);
    service.sterge_service(nume2);
    assert(service.size() == 1);
    service.sterge_service(nume1);
    assert(service.size() == 0);

    try {
        service.sterge_service(nume1);
        assert(false);
    }
    catch (RepoException&){
        assert(true);
    }
}

void Teste::Ruleaza_teste_filtrare_service() {
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};
    service.adauga_service("Paracetamol", 18.9, "Far", "Ibuprofen");
    service.adauga_service("Nurofen", 18.9, "Phar", "Nur");
    service.adauga_service("Ascovit", 15, "Mir", "Ascutit");
    service.adauga_service("Algocalmin", 6.35, "Alb", "Ascutit");
    service.adauga_service("Decasept", 21.40, "Mert", "Deci");
    service.adauga_service("Profi", 0.87, "Lasa", "Proxi");

    vector<Medicament> lista_filtrata= service.FiltrarePret(18.9);
    assert(lista_filtrata.size() == 2);
    Medicament med1{"Paracetamol", 18.9, "Far", "Ibuprofen"};
    assert(lista_filtrata[0] == med1);
    Medicament med2{"Nurofen", 18.9, "Phar", "Nur"};
    assert(lista_filtrata[1] == med2);

    lista_filtrata = service.FiltrareSubstActiva("Ascutit");
    assert(lista_filtrata.size() == 2);
    assert(lista_filtrata[0] == Medicament("Ascovit", 15, "Mir", "Ascutit"));
    assert(lista_filtrata[1] == Medicament("Algocalmin", 6.35, "Alb", "Ascutit"));
}

void Teste::Ruleaza_teste_sortare_service() {
    //RepoMedicamente repo;
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};
    service.adauga_service("Paracetamol", 18.9, "Far", "Ibuprofen");
    service.adauga_service("Nurofen", 18.9, "Phar", "Nur");
    service.adauga_service("Ascovit", 15, "Mir", "Ascutit");
    service.adauga_service("Algocalmin", 6.35, "Alb", "Ascutit");
    service.adauga_service("Decasept", 21.40, "Mert", "Deci");
    service.adauga_service("Profi", 0.87, "Lasa", "Proxi");

    vector<Medicament> lista_sortata;
    lista_sortata = service.GenericSort(Service::cmpNume, true);
    assert(lista_sortata[0] == Medicament("Profi", 0.87, "Lasa", "Proxi"));
    assert(lista_sortata[1] == Medicament("Paracetamol", 18.9, "Far", "Ibuprofen"));
    assert(lista_sortata[2] == Medicament("Nurofen", 18.9, "Phar", "Nur"));

    lista_sortata = service.GenericSort(Service::cmpProducator, true);
    assert(lista_sortata[1] == Medicament("Ascovit", 15, "Mir", "Ascutit"));
    assert(lista_sortata[2] == Medicament("Decasept", 21.40, "Mert", "Deci"));
    assert(lista_sortata[0] == Medicament("Nurofen", 18.9, "Phar", "Nur"));

    lista_sortata = service.GenericSort(Service::cmpSubstantaPret, true);
    assert(lista_sortata[4] == Medicament("Ascovit", 15, "Mir", "Ascutit"));
    assert(lista_sortata[3] == Medicament("Decasept", 21.40, "Mert", "Deci"));
    assert(lista_sortata[5] == Medicament("Algocalmin", 6.35, "Alb", "Ascutit"));

    lista_sortata = service.GenericSort(Service::cmpNume, false);
    assert(lista_sortata[1] == Medicament("Ascovit", 15, "Mir", "Ascutit"));
    assert(lista_sortata[2] == Medicament("Decasept", 21.40, "Mert", "Deci"));
    assert(lista_sortata[0] == Medicament("Algocalmin", 6.35, "Alb", "Ascutit"));

    lista_sortata = service.GenericSort(Service::cmpProducator, false);
    assert(lista_sortata[4] == Medicament("Ascovit", 15, "Mir", "Ascutit"));
    assert(lista_sortata[3] == Medicament("Decasept", 21.40, "Mert", "Deci"));
    assert(lista_sortata[0] == Medicament("Algocalmin", 6.35, "Alb", "Ascutit"));

    lista_sortata = service.GenericSort(Service::cmpSubstantaPret, false);
    assert(lista_sortata[1] == Medicament("Ascovit", 15, "Mir", "Ascutit"));
    assert(lista_sortata[2] == Medicament("Decasept", 21.40, "Mert", "Deci"));
    assert(lista_sortata[0] == Medicament("Algocalmin", 6.35, "Alb", "Ascutit"));
}

void Teste::Ruleaza_teste_adauga_cos() {
    //RepoMedicamente repo;
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};
    service.adauga_service("Paracetamol", 18.9, "Far", "Ibuprofen");
    service.adauga_service("Nurofen", 18.9, "Phar", "Nur");
    service.adauga_service("Ascovit", 15, "Mir", "Ascutit");
    service.adauga_service("Algocalmin", 6.35, "Alb", "Ascutit");
    service.adauga_service("Decasept", 21.40, "Mert", "Deci");
    service.adauga_service("Profi", 0.87, "Lasa", "Proxi");

    assert(service.sizeOfCos() == 0);
    service.addtoCos("Paracetamol");
    assert(service.sizeOfCos() == 1);
    service.addtoCos("Algocalmin");
    assert(service.sizeOfCos() == 2);
    vector<Medicament> lista = service.getCos();
    assert(lista.size() == 2);

    try {
        service.addtoCos("Paracetamol");
        assert(false);
    }
    catch (CosException&){
        assert(true);
    }

    try {
        service.addtoCos("Parc");
        assert(false);
    }
    catch (RepoException&){
        assert(true);
    }

}

void Teste::Ruleaza_teste_goleste_cos() {
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};
    service.adauga_service("Paracetamol", 18.9, "Far", "Ibuprofen");
    service.adauga_service("Nurofen", 18.9, "Phar", "Nur");
    service.adauga_service("Ascovit", 15, "Mir", "Ascutit");
    service.addtoCos("Ascovit");
    assert(service.sizeOfCos() == 1);
    service.addtoCos("Nurofen");
    assert(service.sizeOfCos() == 2);
    service.emptyCos();
    assert(service.sizeOfCos() == 0);
}

void Teste::Ruleaza_teste_adauga_random_cos() {
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};
    service.adauga_service("Paracetamol", 18.9, "Far", "Ibuprofen");
    service.adauga_service("Nurofen", 18.9, "Phar", "Nur");
    service.adauga_service("Ascovit", 15, "Mir", "Ascutit");
    service.adauga_service("Algocalmin", 6.35, "Alb", "Ascutit");
    service.adauga_service("Decasept", 21.40, "Mert", "Deci");
    service.adauga_service("Profi", 0.87, "Lasa", "Proxi");

    assert(service.sizeOfCos() == 0);
    int nr = service.addRandomMedsToCos(4);
    assert(nr == 4);
    assert(service.sizeOfCos() == 4);
    nr = service.addRandomMedsToCos(4);
    assert(nr == 2);
    assert(service.sizeOfCos() == 6);
}

void Teste::Ruleaza_teste_salveaza_cos_in_fisier() {
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};
    service.adauga_service("Paracetamol", 18.9, "Far", "Ibuprofen");
    service.adauga_service("Nurofen", 18.9, "Phar", "Nur");
    service.adauga_service("Ascovit", 15, "Mir", "Ascutit");
    service.adauga_service("Algocalmin", 6.35, "Alb", "Ascutit");
    service.adauga_service("Decasept", 21.40, "Mert", "Deci");
    service.adauga_service("Profi", 0.87, "Lasa", "Proxi");
    service.addRandomMedsToCos(6);
    assert(service.sizeOfCos() == 6);
    service.saveCosToFile("../CosTeste.txt");
    assert(service.sizeOfCos() == 6);

    ifstream fin("../CosTeste.txt");
    string line;
    int numberoflines = 0;
    while (getline(fin, line)) {
        numberoflines++;
    }
    assert(numberoflines == 6);
}

void Teste::Ruleaza_teste_pretStatistic() {
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};
    service.adauga_service("Paracetamol", 18.9, "Far", "Ibuprofen");
    service.adauga_service("Nurofen", 18.9, "Phar", "Nur");
    service.adauga_service("Ascovit", 15, "Mir", "Ascutit");
    service.adauga_service("Algocalmin", 6.35, "Alb", "Ascutit");
    service.adauga_service("Decasept", 21.40, "Mert", "Deci");
    service.adauga_service("Profi", 0.87, "Lasa", "Proxi");

    map<int, Med_DTO> map = service.pretStatistic();
    assert(map.size() == 5);
    assert(map[18.9].get_count() == 2);
    assert(map[0.87].get_count() == 1);
}


//------------------------------------------------TESTE UNDO---------------------------------------------------------

void Teste::Ruleaza_teste_undo() {
    RepoMedicamente repo{"../teste.txt"};
    repo.emptyFile();
    MedicamentValidator val;
    Service service{repo, val};
    service.adauga_service("Paracetamol", 18.9, "Far", "Ibuprofen");
    service.adauga_service("Nurofen", 18.9, "Phar", "Nur");
    assert(service.size() == 2);
    service.sterge_service("Paracetamol" );
    assert(service.size() == 1);
    service.undo();
    assert(service.size() == 2);
    service.modifica_service("Paracetamol", 18.9, "Farmec");
    Medicament med = service.cauta_service("Paracetamol");
    assert(med.getProducator() == "Farmec");
    service.undo();
    med = service.cauta_service("Paracetamol");
    assert(med.getProducator() == "Far");
    assert(service.size() == 2);
    service.undo();
    assert(service.size() == 1);
    service.undo();
    assert(service.size() == 0);
    try {
        service.undo();
        assert(false);
    }
    catch (UndoException&) {
        assert(true);
    }
}

//------------------------------------------------TESTE EXCEPTII---------------------------------------------------------

void Teste::Ruleaza_teste_exceptii(){
    RepoException exceptie1("Mesaj de eroare pt test");
    ValidatorException exceptie2("Mesaj de eroare pt test");
    CosException exceptie3("Mesaj de eroare pentru test");
    UndoException exceptie4("Mesaj de eroare pentru test");
    assert(exceptie1.getMesajDeEroare() == "Mesaj de eroare pt test");
    assert(exceptie2.getMesajDeEroare() == "Mesaj de eroare pt test");
    assert(exceptie3.getMesajDeEroare() == "Mesaj de eroare pentru test");
    assert(exceptie4.getMesajDeEroare() == "Mesaj de eroare pentru test");
}

//------------------------------------------------TESTE TOATE TESTELE-------------------------------------------------

void Teste::Ruleaza_toate_testele() {
    Ruleaza_teste_domain();
    cout << "Teste Domain trecute cu succes!\n";
    Ruleaza_teste_validator();
    cout << "Teste Validator trecute cu succes!\n";
    Ruleaza_teste_exceptii();
    cout << "Teste Exceptii trecute cu succes!\n";
    Ruleaza_teste_repo();
    cout << "Teste Repository trecute cu succes!\n";
    Ruleaza_teste_lab_repo();
    cout << "Teste Lab Repository trecute cu succes!\n";
    Ruleaza_teste_service();
    cout << "Teste Service trecute cu succes!\n";
}
