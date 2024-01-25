#include "validari.h"
#include <vector>

using std::vector;

void MedicamentValidator::valideaza(const Medicament &medicament) {
    string errors;
    if (medicament.getNume().length() < 1)
        errors += "Medicamentul introdus este invalid!\n";
    if (medicament.getPret() <= 0)
        errors += "Pretul introdus este invalid!\n";
    if (medicament.getProducator().length() < 1)
        errors += "Producatorul introdus este invalid!\n";
    if (medicament.getSubstActiva().length() < 1)
        errors += "Substanta activa introdusa este invalida!\n";

    if (errors.length() > 0)
        throw ValidatorException(errors);

}