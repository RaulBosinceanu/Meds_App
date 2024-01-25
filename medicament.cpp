#include "medicament.h"

string Medicament::getNume() const{
    return nume;
}

float Medicament::getPret() const{
    return pret;
}

string Medicament::getProducator() const{
    return producator;
}

string Medicament::getSubstActiva() const{
    return subst_activa;
}

void Medicament::setPret(const float& pret_nou){
    pret = pret_nou;
}

void Medicament::setProducator(const string &producator_nou){
    producator = producator_nou;
}

bool Medicament::operator==(const Medicament& f) const {
    return f.getNume() == nume && f.getSubstActiva() == subst_activa;
}