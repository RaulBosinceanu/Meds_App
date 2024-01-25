#include "cos.h"
#include <random>
#include <fstream>
#include <algorithm>

using std::shuffle;
using std::find_if;
using std::ofstream;
using std::endl;

bool Cos::exist(const string& nume) {
    auto MedsMatching = [=](const Medicament &med) {
        return med.getNume() == nume;
    };
    auto f = find_if(CosMedicamente.begin(), CosMedicamente.end(), MedsMatching);

    if (f != CosMedicamente.end()) {
        return true;
    }
    else {
        return false;
    }
}

void Cos::addMedToCos(const Medicament &med) {
    if (!exist(med.getNume())) {
        CosMedicamente.push_back(med);
        notify();
    }
    else {
        throw CosException("Medicamentul este deja in Cos!");
    }
}

void Cos::emptyCos() {
    CosMedicamente.clear();
    notify();
}

int Cos::addRandomMeds(vector<Medicament> theSourceofMeds, int howmany) {
    int howManyMoviesWasAdd = 0;
    shuffle(theSourceofMeds.begin(), theSourceofMeds.end(),
            std::default_random_engine(std::random_device{}()));
    while(howManyMoviesWasAdd < howmany && !theSourceofMeds.empty()) {
        Medicament med = theSourceofMeds.back();
        if (!exist(med.getNume())) {
            CosMedicamente.push_back(theSourceofMeds.back());
            howManyMoviesWasAdd++;
        }
        theSourceofMeds.pop_back();
    }
    notify();
    return howManyMoviesWasAdd;
}

const vector<Medicament>& Cos::getAllMedsFromCos() const {
    return CosMedicamente;
}

int Cos::sizeOfCos() const {
    return (int) CosMedicamente.size();
}

void Cos::saveCosToFile(const string &fileName) const {
    ofstream fout(fileName);
    for (const auto& med:CosMedicamente) {
        fout << med.getNume() << ", " << med.getPret() << ", " << med.getProducator() << ", "
             << med.getSubstActiva() << endl;
    }
    fout.close();
}