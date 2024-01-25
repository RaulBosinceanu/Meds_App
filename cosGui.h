#pragma once

#include "observer.h"
#include "cos.h"
#include "service.h"

#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QFormLayout>
#include <QTableWidget>
#include <QPainter>
#include <QLineEdit>
#include <QMessageBox>
#include <QListWidgetItem>
#include <algorithm>
#include <random>


class CosCRUD: public QWidget, public Observer {

private:
    Service& service;

    QHBoxLayout* lyMain = new QHBoxLayout;
    QVBoxLayout* lyLeft = new QVBoxLayout;
    QVBoxLayout* lyRight = new QVBoxLayout;

    //============LEFT================
    QPushButton* btnAddWishlist = new QPushButton{" Aauga medicament in cos"};
    QWidget* AddWindow = new QWidget;
    QFormLayout* lyAddWishlist = new QFormLayout;
    QLabel* lblNume = new QLabel{"Nume: "};
    QLabel* lblYear = new QLabel{"Year: "};
    QLineEdit* editTitle = new QLineEdit;
    QLineEdit* editYear = new QLineEdit;
    QPushButton* btnAdd1 = new QPushButton{"Adauga medicament"};

    QPushButton* btnEmptyWishlist = new QPushButton{" Cos gol "} ;

    QPushButton* btnAddRandomWishlist = new QPushButton{" Adauga medicament random in cos"};
    QWidget* AddRandomWindow = new QWidget;
    QFormLayout * lyAddRandomWindow = new QFormLayout;
    QPushButton* btnAddRandom = new QPushButton{" Adauga medicament"};
    QLabel* lblHowMany = new QLabel{"Selecteaza numarul de medicamente: "};
    QSpinBox* spinBoxHowMany =  new QSpinBox;
    QPushButton* btnAdd2 = new QPushButton{"Adauga medicament"};

    QPushButton* btnExportWishlist = new QPushButton{" Exporta cosul in fisier"} ;
    QWidget* ExportWishlistWindow = new QWidget;
    QFormLayout* lyExportWishlistWindow = new QFormLayout;
    QLabel* lblFile = new QLabel("calea fisierului unde doresti sa salvezi ");
    QLineEdit* editFile= new QLineEdit;
    QPushButton* btnExport = new QPushButton("Salveaza fisierul");


    //============RIGHT================
    QTableWidget* tableWishlist = new QTableWidget{};


    void initializeComponents();
    void connectSignalSlot();

    void reloadTableWishlist(QTableWidget* tbl, const vector<Medicament>& meds);
    void WishlistGUI_add();
    void WishlistGUI_addRandom();
    void WishlistGUI_export();

    void update() override {
        reloadTableWishlist(tableWishlist, service.getCos());
    }

public:
    CosCRUD(Service& service) : service {service} {
        this->setStyleSheet("background-color: lightBlue;");
        initializeComponents();
        connectSignalSlot();
    }
};



class CosDRAW: public QWidget, public Observer {
private:
    Cos& cos;


    void update() override {
        repaint();
    }

    void paintEvent(QPaintEvent* event) override;

    ~CosDRAW() {
        cos.removeObserver(this);
    }

public:
    CosDRAW(Cos& cos) : cos{cos}{
        cos.addObserver(this);
        this->setStyleSheet("background-color: lightBlue;");
    }
};
