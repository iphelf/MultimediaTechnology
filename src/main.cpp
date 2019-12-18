#include <QApplication>
#include "src/menu/menu.h"
#include "src/bitmap/bitmap.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Menu menu;
    menu.show();
    return a.exec();
}
