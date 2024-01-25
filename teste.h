#include "medicament.h"
#include "validari.h"
#include "repo.h"
#include "repoLab.h"
#include "service.h"
#include "exceptii.h"

class Teste{

private:

    /**
     * Ruleaza testele pentru toate functionalitatile din domain
     */
    static void Ruleaza_teste_domain();

    /**
    * Ruleaza testele pentru toate functionalitatile din validator
    */
    static void Ruleaza_teste_validator();

    /**
     * Ruleaza testele pentru toate functionalitatile din repository
     */
    static void Ruleaza_teste_repo();
    static void Ruleaza_teste_adauga_repo();
    static void Ruleaza_teste_cauta_repo();
    static void Ruleaza_teste_modifica_repo();
    static void Ruleaza_teste_sterge_repo();

    /**
     * Ruleaza testele pentru toate functionalitatile din repository
     */
    static void Ruleaza_teste_lab_repo();
    static void Ruleaza_teste_adauga_lab_repo();
    static void Ruleaza_teste_cauta_lab_repo();
    static void Ruleaza_teste_modifica_lab_repo();
    static void Ruleaza_teste_sterge_lab_repo();

    /**
     * Ruleaza testele pentru toate functionalitatile din service
     */
    static void Ruleaza_teste_service();
    static void Ruleaza_teste_adauga_service();
    static void Ruleaza_teste_cauta_service();
    static void Ruleaza_teste_modifica_service();
    static void Ruleaza_teste_sterge_service();
    static void Ruleaza_teste_filtrare_service();
    static void Ruleaza_teste_sortare_service();
    static void Ruleaza_teste_adauga_cos();
    static void Ruleaza_teste_goleste_cos();
    static void Ruleaza_teste_adauga_random_cos();
    static void Ruleaza_teste_salveaza_cos_in_fisier();
    static void Ruleaza_teste_pretStatistic();

    /**
    * Ruleaza testele pentru Undo
    */
    static void Ruleaza_teste_undo();



    /**
     * Ruleaza testele pentru exceptii
     */
    static void Ruleaza_teste_exceptii();

public:
    /**
     * Constructorul
     */
    Teste() = default;

    /**
     * Ruleaza toate testele pentru toate functionalitatile
     */
    static void Ruleaza_toate_testele() ;
};