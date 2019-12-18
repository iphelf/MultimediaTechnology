#include "menu.h"
#include "ui_menu.h"
#include "src/bitmap/bitmap.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu) {
    ui->setupUi(this);
    initFeature();
}

Menu::~Menu() {
    delete ui;
}

void Menu::initFeature() {
    featureList=new QStringList;
    featureList->push_back("Lab 1.2: Fullcolor to grayscale");
    ui->listWidget->addItems(*featureList);
}

void Menu::openFeature(QString featureName) {
    if(!featureList->contains(featureName)) return;
    switch (featureList->indexOf(featureName)) {
    case 0:
        Bitmap *bitmap=new Bitmap();
        bitmap->show();
        break;
    }
}

void Menu::on_btnOpen_clicked() {
    if(ui->listWidget->selectedItems().size()==0) return;
    openFeature(ui->listWidget->selectedItems()[0]->text());
}

void Menu::on_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    openFeature(item->text());
}
