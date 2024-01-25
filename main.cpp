#include <QApplication>
#include "gui.h"
#include "ui.h"
#include "teste.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Teste teste;
    teste.Ruleaza_toate_testele();

    RepoMedicamente repo{"../repo.txt"};
    MedicamentValidator val;
    Service service{repo, val};

    UI ui{service};
    //ui.runUI();

    GUI gui{service};
    //gui.setWindowState(Qt::WindowMaximized);
    gui.resize(1200,600);
    gui.show();

    return a.exec();
}
