#pragma once
#include "medicament.h"
#include "exceptii.h"

class MedicamentValidator {
public:
    /**
     * Valideaza un medicament
     */
    static void valideaza(const Medicament& medicament) ;
};
