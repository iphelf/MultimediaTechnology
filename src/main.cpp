#include <QApplication>
#include "src/menu/menu.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Menu menu;
    menu.show();
    return a.exec();
}
