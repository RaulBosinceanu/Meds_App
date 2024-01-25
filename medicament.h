#pragma once
#include <string>
#include <iostream>
#include <utility>

using std::cout;
using std::string;

class Medicament {

private:

    string nume;
    float pret{};
    string producator;
    string subst_activa;

public:
    /**
     * Constructorul default care este apelat atunci cand nu avemparametrii};
    **/
    Medicament() = default;

    /**
     * Constructorul de medicament are aributele:
     * nume, pret, producator, subst activa
     */
    Medicament(string nume, const float &pret, string producator, string subst_activa) :
            nume{(nume)}, pret{pret}, producator{(producator)}, subst_activa{(subst_activa)} {};

    /**
     * Constructor de copiere
     */
    Medicament(const Medicament &ot) : nume{ot.nume}, pret{ot.pret}, producator{ot.producator},
                                       subst_activa{ot.subst_activa} {};

    /**
     * Returneaza numele unui medicament
     */
    string getNume() const;

    /**
     * Returneaza pretul unui medicament
     */
    float getPret() const;

    /**
     * Returneaza producatorul unui medicament
     */
    string getProducator() const;

    /**
     * Returneaza substanta activa a unui medicament
     */
    string getSubstActiva() const;

    /**
     * Seteaza noul pret al medicamentului
     */
    void setPret(const float &pret_nou);

    /**
     * Seteaza noul producator al medicamentului
     */
    void setProducator(const string &producator_nou);

    /**
     * Returneaza true daca 2 medicamente sunt egale
     */
    bool operator==(const Medicament &f) const;
};

//---------------------------------------------------------DTO--------------------------------------------------------

    class Med_DTO {
    private:
        int pret;
        int count;
    public:
        /**
         * Constructor for Med_DTO class
         * @param year
         * @param count
         */
        Med_DTO() = default;

        Med_DTO(int pret, int count) : pret{pret}, count{count} {};

        /**
         * Increment the count with 1
         */
        void increment_count() {
            count++;

        }

        /**
         * Return the count of the DTO object
         */
        int get_count() const {
            return count;
        }
    };

