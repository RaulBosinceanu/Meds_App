#include "undo.h"

void AddUndo::doUndo() {
    repo.sterge_repo(medAdded);
}

void DeleteUndo::doUndo() {
    repo.adauga_repo(medDeleted);
}

void ModifyUndo::doUndo() {
    repo.modifica_repo(medToModify);
}
