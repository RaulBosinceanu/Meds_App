#include "medicament.h"
#include "repoAbstract.h"

class UndoAction {
public:
    UndoAction() = default;

    virtual ~UndoAction() = default;

    virtual void doUndo() = 0;
};


class AddUndo : public UndoAction {
private:
    Medicament medAdded;
    AbstractRepository& repo;

public:
    AddUndo(AbstractRepository& repo, const Medicament& medicamentAdded) : UndoAction(),
                                                                           repo { repo }, medAdded { medicamentAdded } {}

    ~AddUndo() override =default;

    void doUndo() override;
};


class DeleteUndo : public UndoAction {
private:
    Medicament medDeleted;
    AbstractRepository &repo;

public:
    DeleteUndo(AbstractRepository& repo, const Medicament& medDeleted) : UndoAction(),
                                                                         repo { repo }, medDeleted { medDeleted } {}

    ~DeleteUndo() override =default;

    void doUndo() override;
};

class ModifyUndo : public UndoAction {
private:
    Medicament medToModify;
    AbstractRepository&repo;

public:
    ModifyUndo (AbstractRepository& repo, const Medicament& medToModify) : UndoAction(),
                                                                           repo { repo }, medToModify { medToModify }{}

    ~ ModifyUndo () override =default;

    void doUndo() override;
};
