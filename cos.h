#pragma once
#include "medicament.h"
#include "exceptii.h"
#include "observer.h"
#include <vector>

using std::vector;

class Cos: public Observable{

private:
    vector<Medicament> CosMedicamente;

    /**
     * Return true if exists a med in wishlist with the same name
     */
    bool exist(const string&);

public:

    /**
     * Defaul constructor of the class wishlist
     */
    Cos() = default;

    /**
     * Add a movie in wishlist
     */
    void addMedToCos(const Medicament& med);

    /**
     * Remove all the meds from the wishlist
     */
    void emptyCos();

    /**
     * Add a number of random meds in wishlist
     */
    int addRandomMeds(vector<Medicament> theSourceofMeds, int howmany);

    /**
     * Returns a vector with all movies from Wishlist
     */
    const vector<Medicament>& getAllMedsFromCos() const;

    /**
     * Return the number of meds from wishlist
     */
    int sizeOfCos() const;

    /**
     * Save all meds from Wishlist to file
     */
    void saveCosToFile(const string& fileName) const;

};
