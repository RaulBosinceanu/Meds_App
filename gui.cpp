#include "GUI.h"

void GUI::initializeGuiComponents() {
    this->setWindowTitle("Med App");
    this->setStyleSheet("background-color: lightGreen");
    /*
     * black (negru)
     * white (alb)
     * red (roșu)
     * green (verde)
     * blue (albastru)
     * cyan (cyan)
     * magenta (magenta)
     * yellow (galben)
     * gray (gri)
     * darkGray (gri închis)
     * lightGray (gri deschis)
     * transparent (transparent)
     */

    //main layout-------------------------------------------------------------------------------------------------------
    lyMain = new QHBoxLayout;
    this->setLayout(lyMain);


    //left part of the widow--------------------------------------------------------------------------------------------
    //Partea din stanga e impartita in 5 subparti
    //left1 = optiunile de gestiune a medicamentelor
    //left2 = sortarea medicamentelor
    //left3 = filtrarea medicamentelor
    //left4 = gestiunea cosului
    //left5 = butonul de reload data
    lyLeft = new QVBoxLayout;

    //left1 = optiunile de gestiune a medicamentelor
    QHBoxLayout* lyLeft1 = new QHBoxLayout;
    QHBoxLayout* ly_options = new QHBoxLayout;
    GroupBoxOptions->setLayout(ly_options);
    btnAddMed = new QPushButton("Adauga Med");
    btnModifyMed = new QPushButton("Modifica Med");
    btnFindMed = new QPushButton("Cauta Med");
    btnDeleteMed = new QPushButton("Sterge Med");
    ly_options->addWidget(btnAddMed);
    ly_options->addWidget(btnModifyMed);
    ly_options->addWidget(btnFindMed);
    ly_options->addWidget(btnDeleteMed);
    lyLeft1->addWidget(GroupBoxOptions);
    lyLeft->addWidget(GroupBoxOptions);


    //left2 = sortarea medicamentelor
    //casuta de sortare trebuie impartita in inca doua casute (criteriu + ordine)
    QVBoxLayout* ly_sort = new QVBoxLayout;
    GroupBoxSort->setLayout(ly_sort);

    //
    QHBoxLayout* ly_sort1 = new QHBoxLayout;

    //criteriu
    QVBoxLayout* ly_sort_by = new QVBoxLayout;
    GroupBoxSortCriteria->setLayout(ly_sort_by);
    ly_sort_by->addWidget(radioSortByNume);
    ly_sort_by->addWidget(radioSortByProducator);
    ly_sort_by->addWidget(radioSortBySubstantaPret);
    //ordine
    QVBoxLayout* ly_sort_order = new QVBoxLayout;
    GroupBoxSortOrder->setLayout(ly_sort_order);
    ly_sort_order->addWidget(radioSortAscending);
    ly_sort_order->addWidget(radioSortDescending);
    //buton de sortare
    btnSort = new QPushButton("Sorteaza medicamentele");

    ly_sort1->addWidget(GroupBoxSortCriteria);
    ly_sort1->addWidget(GroupBoxSortOrder);

    ly_sort->addLayout(ly_sort1);
    ly_sort->addWidget(btnSort);

    lyLeft->addWidget(GroupBoxSort);


    //left3 = filtrarea filmelor
    QVBoxLayout* lyFilter = new QVBoxLayout;
    GroupBoxFilter->setLayout(lyFilter);
    QVBoxLayout* ly_filter_criteria = new QVBoxLayout;
    //criterii
    GroupBoxFilterCriteria->setLayout(ly_filter_criteria);
    ly_filter_criteria->addWidget(radioFilterPret);
    ly_filter_criteria->addWidget(radioFilterSubst_activa);
    //buton filtrare
    btnFilterWindow = new QPushButton("Filtreaza medicamentele");

    lyFilter->addWidget(GroupBoxFilterCriteria);
    lyFilter->addWidget(btnFilterWindow);
    lyLeft->addWidget(GroupBoxFilter);


    //left4 = gestiunea wishlistului
    QHBoxLayout* ly_Wishlist = new QHBoxLayout;
    GroupBoxCos->setLayout(ly_Wishlist);
    btnAddCos = new QPushButton("Adauga Med in Cos");
    btnEmptyCos = new QPushButton("Goleste Cos");
    btnAddRandomCos = new QPushButton("Adauga med random");
    btnExportCos = new QPushButton("Exporta Cos in fisier");
    ly_Wishlist->addWidget(btnAddCos);
    ly_Wishlist->addWidget(btnEmptyCos);
    ly_Wishlist->addWidget(btnAddRandomCos);
    ly_Wishlist->addWidget(btnExportCos);
    lyLeft->addWidget(GroupBoxCos);
    GroupBoxWindowsCos->setLayout(ly_WindowsCos);
    ly_WindowsCos->addWidget(btnCrudCos);
    ly_WindowsCos->addWidget(btnDrawCos);
    lyLeft->addWidget(GroupBoxWindowsCos);



    //left5 = butonul de reload data si butonul de undo
    QWidget* left5_btns = new QWidget;
    QHBoxLayout* ly_buttons_reload_undo = new QHBoxLayout;
    left5_btns->setLayout(ly_buttons_reload_undo);
    btnReloadData = new QPushButton("Reload data");
    btnUndo = new QPushButton("Undo");
    ly_buttons_reload_undo->addWidget(btnReloadData);
    ly_buttons_reload_undo->addWidget(btnUndo);
    lyLeft->addWidget(left5_btns);


    //right part of the window-------------------------------------------------------------------------------------------
    //partea drepata e imaprtita in doua pe verticala
    //right1 = tabel cu toate medicamentele
    //right2 = tabel cu medicamentele din wishlist
    lyRight = new QVBoxLayout;


    //right1 = tabel cu toate filmele
    tableMed = new QTableWidget{200, 4};
    tableMed->setObjectName("Med List");
    tableMed->setHorizontalHeaderLabels(QStringList() << "Nume" << "Pret" << "Producator" << "Substanta Activa");
    //tableMovies->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableMed->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableMed->setSelectionBehavior(QAbstractItemView::SelectRows);


    tableCos = new QTableWidget{100, 4};
    tableCos->setObjectName("Cos");
    tableCos->setHorizontalHeaderLabels(QStringList() << "Nume" << "Pret" << "Producator" << "Substanta Activa");
    //tableWishlist->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableCos->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    listMeds = new QListWidget{};

    lyRight->addWidget(tableMed, 5);
    lyRight->addWidget(listMeds, 2);
    lyRight->addWidget(tableCos, 2);


    //Statistic part of the widow-------------------------------------------------------------------------------------------
    lyStatistic = new QVBoxLayout;
    ReloadDynamicButtons();


    //add to the main layout the left and right part--------------------------------------------------------------------
    lyMain->addLayout(lyLeft, 3);
    lyMain->addLayout(lyRight, 2);
    lyMain->addLayout(lyStatistic, 1);

}


void GUI::connectSignalsSlots() {
    //butoanele care deschid fereastra de citit date pt adaugare, modificare, cautare si stergere
    QObject::connect(btnAddMed, &QPushButton::clicked, this, &GUI::GuiAddMedWindow);
    QObject::connect(btnModifyMed, &QPushButton::clicked, this, &GUI::GuiModifyMedWindow);
    QObject::connect(btnFindMed, &QPushButton::clicked, this, &GUI::GuiFindMedWindow);
    QObject::connect(btnDeleteMed, &QPushButton::clicked, this, &GUI::GuiDeleteMedWindow);

    //butonul de sortare
    QObject::connect(btnSort, &QPushButton::clicked, this, &GUI::GuiSort);

    //butonul de filtrare
    QObject::connect(btnFilterWindow, &QPushButton::clicked, this, &GUI::GuiFilter);

    //butonul de reload data
    QObject::connect(btnReloadData, &QPushButton::clicked, this, [=]() {
        reloadMedsTabel(tableMed, service.getAllMeds());
    });

    QObject::connect(btnAddCos, &QPushButton::clicked, this, &GUI::GuiAddCos);
    QObject::connect(btnAddRandomCos, &QPushButton::clicked, this, &GUI::GuiAddRandomCosWindow);
    QObject::connect(btnExportCos, &QPushButton::clicked, this, &GUI::GuiExportCosWindow);
    QObject::connect(btnEmptyCos, &QPushButton::clicked, this, [=]() {
        service.emptyCos();
        reloadMedsTabel(tableCos, service.getCos());
        QMessageBox::information(this, "Info", QString::fromStdString("Cosul a fost golit cu succes!"));
    });

    //ferestre Cos
    QObject::connect(btnCrudCos, &QPushButton::clicked, this, [=]() {
        CosCRUD* window = new CosCRUD{service};
        service.getCurrentCos().addObserver(window);
        window->show();
    });
    QObject::connect(btnDrawCos, &QPushButton::clicked, this, [=]() {
        CosDRAW* window = new CosDRAW{service.getCurrentCos()};
        window->show();
    });


    //butonul de reload data
    QObject::connect(btnReloadData, &QPushButton::clicked, this, [=]() {
        reloadMedsTabel(tableMed, service.getAllMeds());
    });

    //butonul de undo
    QObject::connect(btnUndo, &QPushButton::clicked, this, [=]() {
        try {
            service.undo();
        }
        catch (UndoException& ue) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(ue.getMesajDeEroare()));
        }
        reloadMedsTabel(tableMed, service.getAllMeds());
    });

}


void GUI::reloadMedsTabel(QTableWidget* tbl, const vector<Medicament>& meds) {
    tbl->clearContents();
    tbl->setRowCount((int)meds.size());

    int lineNumber = 0;
    for (auto& mov : meds) {
        tbl->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(mov.getNume())));
        tbl->setItem(lineNumber, 1, new QTableWidgetItem(QString::number(mov.getPret())));
        tbl->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(mov.getProducator())));
        tbl->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(mov.getSubstActiva())));
        lineNumber++;
    }
}

void GUI::reloadMedsList(QListWidget* list, const vector<Medicament>& medicamente) {
    list->clear();

    int lineNumber = 0;
    for (const auto& mov : medicamente) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(mov.getNume() + " " + std::to_string(mov.getPret()) + " " +
                                                                           mov.getProducator() + " " + mov.getSubstActiva()));
        list->addItem(item);
    }
}

void GUI::DynamicButtons() {
    map<int, Med_DTO> pret_st = service.pretStatistic();
    for (const auto& pair: pret_st) {
        int pret = pair.first;
        QPushButton* btn = new QPushButton{QString::fromStdString(std::to_string(pret))};
        lyStatistic->addWidget(btn);
        QObject::connect(btn, &QPushButton::clicked, this, [=]() {
            QMessageBox::information(this, "Numarul Medicamentelor", QString::fromStdString(std::to_string(pair.second.get_count()) + " medicamente"));
        });
    }
}

void GUI::ReloadDynamicButtons() {
    QLayoutItem *item;
    while((item = lyStatistic->takeAt(0))) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
    DynamicButtons();
    lyStatistic->addStretch();
}

void GUI::GuiAddMedWindow() {
    QWidget *AddWindow = new QWidget;
    AddWindow->setWindowTitle("Adauga medicament");
    AddWindow->setStyleSheet("background-color: lightBlue;");

    QFormLayout* lyAddWindow = new QFormLayout;
    AddWindow->setLayout(lyAddWindow);

    QLabel* lblTitle = new QLabel("Nume: ");
    QLabel* lblGenre = new QLabel("Pret: ");
    QLabel* lblYear = new QLabel("Producator: ");
    QLabel* lblActor = new QLabel("Substanta activa: ");
    editNume = new QLineEdit;
    editPret = new QLineEdit;
    editProducator = new QLineEdit;
    editSubst_activa = new QLineEdit;
    lyAddWindow->addRow(lblTitle, editNume);
    lyAddWindow->addRow(lblGenre, editPret);
    lyAddWindow->addRow(lblYear, editProducator);
    lyAddWindow->addRow(lblActor, editSubst_activa);
    btnAdd = new QPushButton("Adauga medicament");
    QObject::connect(btnAdd, &QPushButton::clicked, this, &GUI::GuiAddMed);
    lyAddWindow->addWidget(btnAdd);
    AddWindow->show();
}

void GUI::GuiAddMed() {
    string nume = editNume->text().toStdString();
    int pret = editPret->text().toInt();
    string producator = editProducator->text().toStdString();
    string subst_activa = editSubst_activa->text().toStdString();

    editNume->clear();
    editPret->clear();
    editProducator->clear();
    editSubst_activa->clear();

    try {
        service.adauga_service(nume, pret, producator, subst_activa);
        reloadMedsTabel(tableMed, service.getAllMeds());
        ReloadDynamicButtons();
        reloadMedsList(listMeds, service.getAllMeds());

        //afisam un mesaj ca adaugarea s-a efectual cu succes
        QMessageBox::information(this, "Succes", QString::fromStdString("Medicamentul a fost adaugat cu succes"));
    }
    catch (RepoException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMesajDeEroare()));
    }
    catch (ValidatorException& ve) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMesajDeEroare()));
    }
}


void GUI::GuiModifyMedWindow() {
    QWidget *ModifyWindow = new QWidget;
    ModifyWindow->setWindowTitle("Modifica medicament");
    ModifyWindow->setStyleSheet("background-color: lightBlue;");

    QFormLayout* lyModifyWindow = new QFormLayout;
    ModifyWindow->setLayout(lyModifyWindow);

    QLabel* lblTitle = new QLabel("Numele medicamentului de modificat: ");
    QLabel* lblGenre = new QLabel("Noul pret: ");
    QLabel* lblYear = new QLabel("Noul producator: ");
    QLabel* lblActor = new QLabel("Noua substanta activa: ");
    editNume = new QLineEdit;
    editPret = new QLineEdit;
    editProducator = new QLineEdit;
    editSubst_activa = new QLineEdit;
    lyModifyWindow->addRow(lblTitle, editNume);
    lyModifyWindow->addRow(lblGenre, editPret);
    lyModifyWindow->addRow(lblYear, editProducator);
    lyModifyWindow->addRow(lblActor, editSubst_activa);
    btnModify= new QPushButton("Modify Med");
    QObject::connect(btnModify, &QPushButton::clicked, this, &GUI::GuiModifyMed);
    lyModifyWindow->addWidget(btnModify);
    ModifyWindow->show();
}


void GUI::GuiModifyMed() {
    string nume = editNume->text().toStdString();
    int pret = editPret->text().toInt();
    string producator = editProducator->text().toStdString();

    editNume->clear();
    editPret->clear();
    editProducator->clear();

    try {
        service.modifica_service(nume, pret, producator);
        reloadMedsTabel(tableMed, service.getAllMeds());
        reloadMedsList(listMeds, service.getAllMeds());

        //afisam un mesaj ca adaugarea s-a efectual cu succes
        QMessageBox::information(this, "Succes", QString::fromStdString("Medicamentul a fost modificat cu succes"));
    }
    catch (RepoException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMesajDeEroare()));
    }
    catch (ValidatorException& ve) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMesajDeEroare()));
    }
}


void GUI::GuiFindMedWindow() {
    QWidget *FindWindow = new QWidget;
    FindWindow->setWindowTitle("Gaseste medicament");
    FindWindow->setStyleSheet("background-color: lightBlue;");

    QFormLayout* lyFindWindow = new QFormLayout;
    FindWindow->setLayout(lyFindWindow);

    QLabel* lblTitle = new QLabel("Numele filmului cautat: ");
    editNume = new QLineEdit;
    lyFindWindow->addRow(lblTitle, editNume);
    btnFind = new QPushButton("Cauta medicament");
    QObject::connect(btnFind, &QPushButton::clicked, this, &GUI::GuiFindMed);
    lyFindWindow->addWidget(btnFind);
    FindWindow->show();
}


void GUI::GuiFindMed() {
    string nume = editNume->text().toStdString();

    editNume->clear();

    try {
        Medicament find_med = service.cauta_service(nume);
        reloadMedsTabel(tableMed, service.getAllMeds());
        reloadMedsList(listMeds, service.getAllMeds());

        //afisam un mesaj ca adaugarea s-a efectual cu succes
        QMessageBox::information(this, "Succes", QString::fromStdString("Medicamentul cautat este:\n Nume: "
                                                                        + find_med.getNume() + "\n"
                                                                        + "Pret: " + std::to_string(find_med.getPret()) + "\n"
                                                                        + "Producator: " + find_med.getProducator() + "\n"
                                                                        + "Substanta activa:  " + find_med.getSubstActiva()));
    }
    catch (RepoException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMesajDeEroare()));
    }
    catch (ValidatorException& ve) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMesajDeEroare()));
    }
}


void GUI::GuiDeleteMedWindow()  {
    QWidget *DeleteWindow = new QWidget;
    DeleteWindow->setWindowTitle("Sterge medicament");
    DeleteWindow->setStyleSheet("background-color: lightBlue;");

    QFormLayout* lyDeleteWindow = new QFormLayout;
    DeleteWindow->setLayout(lyDeleteWindow);

    QLabel* lblTitle = new QLabel("Numele medicamentului pe care doresti sa il stergi: ");
    editNume = new QLineEdit;
    lyDeleteWindow->addRow(lblTitle, editNume);
    btnDelete = new QPushButton("Sterge medicament");
    QObject::connect(btnDelete, &QPushButton::clicked, this, &GUI::GuiDeleteMed);
    lyDeleteWindow->addWidget(btnDelete);
    DeleteWindow->show();
}


void GUI::GuiDeleteMed() {
    string nume = editNume->text().toStdString();

    editNume->clear();

    try {
        Medicament delete_med = service.sterge_service(nume);
        reloadMedsTabel(tableMed, service.getAllMeds());
        ReloadDynamicButtons();
        reloadMedsList(listMeds, service.getAllMeds());

        //afisam un mesaj ca adaugarea s-a efectual cu succes
        QMessageBox::information(this, "Succes", QString::fromStdString("Medicamentul a fost sters cu succes"));
    }
    catch (RepoException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMesajDeEroare()));
    }
    catch (ValidatorException& ve) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMesajDeEroare()));
    }
}



void GUI::GuiSort() {
    vector<Medicament> MedsSorted;
    //verificam sa avem optiuni alese
    if ((!radioSortByNume->isChecked() &&
         !radioSortByProducator->isChecked() &&
         !radioSortBySubstantaPret->isChecked()) ||
        (!radioSortAscending->isChecked() &&
         !radioSortDescending->isChecked())) {
        QMessageBox::warning(this, "Warning", "Selecteaza optiunea de sortare");

    }

    if (radioSortByNume->isChecked()) {
        if (radioSortAscending->isChecked()) {
            MedsSorted = service.GenericSort(service.cmpNume, false);
        }
        else {
            MedsSorted = service.GenericSort(service.cmpNume, true);
        }
    }

    if (radioSortByProducator->isChecked()) {
        if (radioSortAscending->isChecked()) {
            MedsSorted = service.GenericSort(service.cmpProducator, false);
        }
        else {
            MedsSorted = service.GenericSort(service.cmpProducator, true);
        }
    }

    if (radioSortBySubstantaPret->isChecked()) {
        if (radioSortAscending->isChecked()) {
            MedsSorted = service.GenericSort(service.cmpSubstantaPret, false);
        }
        else {
            MedsSorted = service.GenericSort(service.cmpSubstantaPret, true);
        }
    }

    reloadMedsTabel(tableMed, MedsSorted);
    reloadMedsList(listMeds, MedsSorted);
}

void GUI::GuiFilter() {
    if (!radioFilterSubst_activa->isChecked() && !radioFilterPret->isChecked()) {
        QMessageBox::warning(this, "Warning", "Selecteaza optiune de filtrare");
    }

    if (radioFilterPret->isChecked()) {
        QWidget* ReadTileWindow = new QWidget;
        ReadTileWindow->setWindowTitle("Filtreaza dupa pret: ");
        ReadTileWindow->setStyleSheet("background-color: lightBlue;");

        QFormLayout *ly_read_title = new QFormLayout;
        ReadTileWindow->setLayout(ly_read_title);

        QLabel *lblTitle = new QLabel("Pret: ");
        editPret = new QLineEdit;
        ly_read_title->addRow(lblTitle, editPret);
        btnFilter1 = new QPushButton("Filtreaza medicamentele");
        ly_read_title->addWidget(btnFilter1);
        QObject::connect(btnFilter1, &QPushButton::clicked, this, [=]() {
            int pret = editPret->text().toInt();
            editPret->clear();
            vector<Medicament> MedsFiltered = service.FiltrarePret(pret);
            if (MedsFiltered.empty()) {
                QMessageBox::warning(this, "Warning", QString::fromStdString("Nu sunt medicamente cu pretul "
                                                                              + std::to_string(pret) + " in lista "));
            }
            else {
                reloadMedsTabel(tableMed, MedsFiltered);
            }
        });
        radioFilterPret->setChecked(false);
        ReadTileWindow->show();
    }

    if (radioFilterSubst_activa->isChecked()) {
        QWidget *ReadGenreWindow = new QWidget;
        ReadGenreWindow->setWindowTitle("Filtreaza dupa substanta activa");
        ReadGenreWindow->setStyleSheet("background-color: lightBlue;");

        QFormLayout *ly_read_year = new QFormLayout;
        ReadGenreWindow->setLayout(ly_read_year);

        QLabel *lblYear = new QLabel("Substanta activa: ");
        editSubst_activa = new QLineEdit;
        ly_read_year->addRow(lblYear, editSubst_activa);
        btnFilter2 = new QPushButton("Filtreaza medicamentele");
        ly_read_year->addWidget(btnFilter2);
        QObject::connect(btnFilter2, &QPushButton::clicked, this, [=]() {
            string subst = editSubst_activa->text().toStdString();
            editSubst_activa->clear();
            vector<Medicament> MedsFiltered = service.FiltrareSubstActiva(subst);
            if (MedsFiltered.empty()) {
                QMessageBox::warning(this, "Warning", QString::fromStdString("Nu sunt medicamente cu substanta activa "
                                                                             + subst + " in lista"));
            }
            else {
                reloadMedsTabel(tableMed, MedsFiltered);
                reloadMedsList(listMeds, service.getAllMeds());
            }
        });
        radioFilterSubst_activa->setChecked(false);
        ReadGenreWindow->show();
    }
}

void GUI::GuiAddCos() {
    QList selectedMeds = tableMed->selectedItems();
    if (selectedMeds.empty()) {
        QMessageBox::warning(this, "Warning", QString::fromStdString("Selecteaza medicamentul pe care "
                                                                     "doresti sa il adaugi in cos"));
    }
    else {
        while (!selectedMeds.empty()) {
            string nume = selectedMeds[0]->text().toStdString();
            try {
                service.addtoCos(nume);
                QMessageBox::information(this, "Info",
                                         QString::fromStdString("Medicamentul a fost adaugat cu succes in cos"));
                reloadMedsTabel(tableCos, service.getCos());
                reloadMedsList(listMeds, service.getAllMeds());
            }
            catch (RepoException &re) {
                QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMesajDeEroare()));
            }
            for (int i = 0; i < 4; i++) {
                selectedMeds.pop_front();
            }
        }
    }
}

void GUI::GuiAddRandomCosWindow() {
    AddRandomWindow = new QWidget;
    AddRandomWindow->setWindowTitle("Adauga medicamente random");
    AddRandomWindow->setStyleSheet("background-color: lightBlue;");

    QFormLayout* lyAddRandomWindow = new QFormLayout;
    AddRandomWindow->setLayout(lyAddRandomWindow);

    QLabel* lblHowMany = new QLabel ("Selecteaza numarul de medicamente: ");
    spinBoxHowMany = new QSpinBox;
    spinBoxHowMany->setMinimum(0);
    spinBoxHowMany->setMaximum(service.size()-service.sizeOfCos());
    btnAddRandom = new QPushButton("Adauga medicament in cos");
    lyAddRandomWindow->addRow(lblHowMany, spinBoxHowMany);
    lyAddRandomWindow->addWidget(btnAddRandom);

    QObject::connect(btnAddRandom, &QPushButton::clicked, this, [=]() {
        int howMany = spinBoxHowMany->value();
        service.addRandomMedsToCos(howMany);
        QMessageBox::information(this, "Info", QString::fromStdString(std::to_string(howMany) +
                                                                      " medicamente au fost adaugata in cos"));
        reloadMedsTabel(tableCos, service.getCos());
        reloadMedsList(listMeds, service.getAllMeds());
        AddRandomWindow->close();
    });
    AddRandomWindow->show();
}

void GUI::GuiExportCosWindow() {
    ExportWishlistWindow = new QWidget;
    ExportWishlistWindow->setWindowTitle("Export Cos in fisier");
    ExportWishlistWindow->setStyleSheet("background-color: lightBlue;");

    QFormLayout* lyExportWishlistWindow = new QFormLayout;
    ExportWishlistWindow->setLayout(lyExportWishlistWindow);

    QLabel* lblFile = new QLabel("calea catre fisierul unde vrei sa salvezi cosul: ");
    editFile= new QLineEdit;
    lyExportWishlistWindow->addRow(lblFile, editFile);

    btnExport = new QPushButton("Salveaza Cos");
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



