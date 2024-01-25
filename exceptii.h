#pragma once
#include <string>
#include <utility>

using std::string;

/**
 * Clasa de exceptii pentru Repository
 */
class RepoException{
private:
    string mesaj_de_eroare;
public:
    /**
     * Constructorul
     * @param mesaj_de_eroarre
     */
    explicit RepoException(string mesaj_de_eroarre): mesaj_de_eroare{( mesaj_de_eroarre )}{}

    /**
     * Returneaza mesajul de eroare
     */
    string getMesajDeEroare() const;
};


/**
 * Clasa de exceptii pentru Validator
 */
class ValidatorException{
private:
    string mesaj_de_eroare;
public:
    /**
     * Constructor
     * @param mesaj_de_eroaree
     */
    explicit ValidatorException(string mesaj_de_eroaree): mesaj_de_eroare{( mesaj_de_eroaree )}{}

    /**
     * Returneaza mesaju de eroare
     * @return
     */
    string getMesajDeEroare() const;
};

/**
 * Clasa de exceptii pentru cos
 */
class CosException{
private:
    string mesaj_de_eroare;
public:
    /**
     * Constructor
     * @param mesaj_de_eroaree
     */
    explicit CosException(string mesaj_de_eroaree): mesaj_de_eroare{( mesaj_de_eroaree )}{}

    /**
     * Returneaza mesaju de eroare
     * @return
     */
    string getMesajDeEroare() const;
};

class UndoException{
private:
    string mesaj_de_eroare;
public:
    /**
     * Constructor
     * @param mesaj_de_eroaree
     */
    explicit UndoException(string mesaj_de_eroaree): mesaj_de_eroare{( mesaj_de_eroaree )}{}

    /**
     * Returneaza mesaju de eroare
     * @return
     */
    string getMesajDeEroare() const;

};