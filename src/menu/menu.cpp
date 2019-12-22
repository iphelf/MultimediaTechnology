#include "menu.h"
#include "ui_menu.h"
#include "src/bitmap/bitmap.h"
#include "src/tts/tts.h"

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
    featureList->push_back("Lab 2.1: Text to Speech");
    ui->listWidget->addItems(*featureList);
}

void Menu::openFeature(QString featureName) {
    if(!featureList->contains(featureName)) return;
    int id=featureList->indexOf(featureName);
    if(id==0) {
        Bitmap *bitmap=new Bitmap();
        bitmap->show();
    } else if(id==1) {
        TTS *tts=new TTS();
        tts->show();
    }
}

void Menu::on_btnOpen_clicked() {
    if(ui->listWidget->selectedItems().size()==0) return;
    openFeature(ui->listWidget->selectedItems()[0]->text());
}

void Menu::on_listWidget_itemDoubleClicked(QListWidgetItem *item) {
    openFeature(item->text());
}
