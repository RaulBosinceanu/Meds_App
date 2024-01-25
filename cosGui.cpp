#include "cosGui.h"

//===============================CosCRUD==============================
void CosCRUD::initializeComponents() {
    this->setLayout(lyMain);

    lyLeft->addWidget(btnAddWishlist);
    lyLeft->addWidget(btnAddRandomWishlist);
    lyLeft->addWidget(btnEmptyWishlist);
    lyLeft->addWidget(btnExportWishlist);

    tableWishlist->setHorizontalHeaderLabels(QStringList() <<"Nume" << "Pret" << "Producator" << "Substanta activa");
    lyRight->addWidget(tableWishlist);

    lyMain->addLayout(lyLeft);
    lyMain->addLayout(lyRight);
}


void CosCRUD::connectSignalSlot() {
    QObject::connect(btnAddWishlist, &QPushButton::clicked, this, &CosCRUD::WishlistGUI_add);
    QObject::connect(btnAddRandomWishlist, &QPushButton::clicked, this, &CosCRUD::WishlistGUI_addRandom);
    QObject::connect(btnEmptyWishlist, &QPushButton::clicked, this, [=]() {
        service.emptyCos();
        reloadTableWishlist(tableWishlist, service.getCos());
        QMessageBox::information(this, "Info", QString::fromStdString("Cosul a fost golit cu succes"));
    });
    QObject::connect(btnExportWishlist, &QPushButton::clicked, this, &CosCRUD::WishlistGUI_export);

}


void CosCRUD::reloadTableWishlist(QTableWidget* tbl, const vector<Medicament>& vec) {
    tbl->clearContents();
    tbl->setRowCount((int)vec.size());
    tbl->setColumnCount(4);

    tbl->clear();

    int lineNumber = 0;
    for (const auto& mov : vec) {
        tbl->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(mov.getNume())));
        tbl->setItem(lineNumber, 1, new QTableWidgetItem(QString::number(mov.getPret())));
        tbl->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(mov.getProducator())));
        tbl->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(mov.getSubstActiva())));
        lineNumber++;
    }
}


void CosCRUD::WishlistGUI_add() {
    AddWindow->setWindowTitle("Adauga medicament in cos");
    AddWindow->setStyleSheet("background-color: lightBlue;");
    AddWindow->setLayout(lyAddWishlist);

    lyAddWishlist->addRow(lblNume, editTitle);
    lyAddWishlist->addRow(lblYear, editYear);
    lyAddWishlist->addWidget(btnAdd1);
    AddWindow->show();
    QObject::connect(btnAdd1, &QPushButton::clicked, this, [=]() {
        string title = editTitle->text().toStdString();
        try {
            service.addtoCos(title);
            reloadTableWishlist(tableWishlist, service.getCos());
        }
        catch (CosException& we) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(we.getMesajDeEroare()));
        }
        AddWindow->close();
    });
}


void CosCRUD::WishlistGUI_addRandom() {
    AddRandomWindow->setWindowTitle("Adauga medicament random");
    AddRandomWindow->setStyleSheet("background-color: lightBlue;");
    AddRandomWindow->setLayout(lyAddRandomWindow);

    spinBoxHowMany->setMinimum(0);
    spinBoxHowMany->setMaximum(service.size() - service.sizeOfCos());
    lyAddRandomWindow->addRow(lblHowMany, spinBoxHowMany);
    lyAddRandomWindow->addWidget(btnAdd2);
    AddRandomWindow->show();

    QObject::connect(btnAdd2, &QPushButton::clicked, this, [=]() {
        int howMany = spinBoxHowMany->value();
        service.addRandomMedsToCos(howMany);
        QMessageBox::information(this, "Info", QString::fromStdString(std::to_string(howMany) +
                                                                      " medicamentul a fost adaugat cu succes"));
        reloadTableWishlist(tableWishlist, service.getCos());
        AddRandomWindow->close();
    });
}

void CosCRUD::WishlistGUI_export() {
    ExportWishlistWindow->setWindowTitle("Exporto cos in fisier");
    ExportWishlistWindow->setStyleSheet("background-color: lightBlue;");
    ExportWishlistWindow->setLayout(lyExportWishlistWindow);

    lyExportWishlistWindow->addRow(lblFile, editFile);

    QObject::connect(btnExport, &QPushButton::clicked, this, [=]() {
        string filePath = editFile->text().toStdString();
        editFile->clear();
        service.saveCosToFile(filePath);
        QMessageBox::information(this, "Info", QString::fromStdString("Cos salvat cu succes!"));
        ExportWishlistWindow->close();
    });
    lyExportWishlistWindow->addWidget(btnExport);
    ExportWishlistWindow->show();
}


//===============================CosDRAW==============================

void CosDRAW::paintEvent(QPaintEvent* event) {
    QPainter p{ this };
    int x = rand() % 400 + 1;
    int y = rand() % 400 + 1;
    for (auto med : cos.getAllMedsFromCos()) {
        p.drawRect(x, y, 100, 100);
        QRectF target(x, y, 100, 100);
        QRectF source(0, 0, 1200, 1200);
        QImage image("../th.jpg");

        p.drawImage(target,image, source);

        x += 40;

        x= rand() % 400 + 1;
        y = rand() % 400 + 1;

    }
}
