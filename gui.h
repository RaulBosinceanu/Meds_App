#pragma onc
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QSpinBox>
#include <QRadioButton>
#include <QListWidget.h>
#include "service.h"
#include "observer.h"
#include "cosGui.h"

using std::vector;

class GUI : public QWidget, public Observer {
private:
    Service& service;


    QHBoxLayout* lyMain;
    QVBoxLayout* lyLeft;
    QVBoxLayout* lyRight;
    QVBoxLayout* lyStatistic;


    //butoare pt gestiune filme
    QGroupBox* GroupBoxOptions = new QGroupBox{tr("Med management: ")};
    QPushButton* btnAddMed;
    QPushButton* btnAdd;
    QPushButton* btnModifyMed;
    QPushButton* btnModify;
    QPushButton* btnFindMed;
    QPushButton* btnFind;
    QPushButton* btnDeleteMed;
    QPushButton* btnDelete;

    //casutele de introdus date
    QLineEdit* editNume;
    QLineEdit* editPret;
    QLineEdit* editProducator;
    QLineEdit* editSubst_activa;

    //tr - traduce textul afisat in dunctie de liba selectata
    //casuta pentru criteriile de sortare
    QGroupBox* GroupBoxSort = new QGroupBox{tr("Sort Meds")};
    QGroupBox* GroupBoxSortCriteria = new QGroupBox{tr("Sort by:")};
    QRadioButton* radioSortByNume = new QRadioButton(QString::fromStdString("Nume"));
    QRadioButton* radioSortByProducator = new QRadioButton(QString::fromStdString("Producator"));
    QRadioButton* radioSortBySubstantaPret = new QRadioButton(QString::fromStdString("Substanta si pret"));
    //casuta pentru ordinea sortarii
    QGroupBox* GroupBoxSortOrder = new QGroupBox{tr("Sort in:")};
    QRadioButton* radioSortAscending = new QRadioButton(QString::fromStdString("Crescator"));
    QRadioButton* radioSortDescending = new QRadioButton(QString::fromStdString("Descrescator"));
    QPushButton* btnSort;

    //Casuta pentru filtrare
    QGroupBox* GroupBoxFilter = new QGroupBox{tr("Filter med")};
    QGroupBox* GroupBoxFilterCriteria = new QGroupBox{tr("Filter by")};
    QRadioButton* radioFilterPret = new QRadioButton(QString::fromStdString("Pret"));
    QRadioButton* radioFilterSubst_activa = new QRadioButton(QString::fromStdString("Substanta activa"));
    QPushButton* btnFilterWindow;
    QPushButton* btnFilter1;
    QPushButton* btnFilter2;

    QGroupBox* GroupBoxCos = new QGroupBox{tr("Cos:")};
    QPushButton* btnAddCos;
    QPushButton* btnEmptyCos;
    QPushButton* btnAddRandomCos;
    QWidget* AddRandomWindow;
    QPushButton* btnExportCos;
    QSpinBox* spinBoxHowMany;

    QGroupBox* GroupBoxWindowsCos = new QGroupBox{"Cos Windows"};
    QHBoxLayout* ly_WindowsCos = new QHBoxLayout;
    QPushButton* btnCrudCos = new QPushButton{"CRUD Cos"};
    QPushButton* btnDrawCos = new QPushButton{"Draw Cos"};

    QPushButton* btnAddRandom;
    QWidget* ExportWishlistWindow;
    QLineEdit* editFile;
    QPushButton* btnExport;
    QListWidget* listMeds;


    QPushButton* btnReloadData;
    QPushButton* btnUndo;


    QTableWidget* tableMed;
    QTableWidget* tableCos;


    void initializeGuiComponents();

    void connectSignalsSlots();

    static void reloadMedsTabel(QTableWidget* tbl, const vector<Medicament>& meds);
    void reloadMedsList(QListWidget* list, const vector<Medicament>& meds);
    void DynamicButtons();
    void ReloadDynamicButtons();


public:
    GUI(Service& service): service{ service } {
        initializeGuiComponents();
        connectSignalsSlots();
        service.getCurrentCos().addObserver(this);
        reloadMedsTabel(tableMed, service.getAllMeds());
        reloadMedsList(listMeds, service.getAllMeds());
    }

    void GuiAddMedWindow();
    void GuiAddMed();
    void GuiModifyMedWindow();
    void GuiModifyMed();
    void GuiFindMedWindow();
    void GuiFindMed();
    void GuiDeleteMedWindow();
    void GuiDeleteMed();

    void GuiSort();
    void GuiFilter();

    void GuiAddCos();
    void GuiAddRandomCosWindow();
    void GuiExportCosWindow();

    void update() override {
        reloadMedsTabel(tableCos, service.getCos());
    }

    char to_string(float pret);
};
