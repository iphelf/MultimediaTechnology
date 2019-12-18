#include "adjustbc.h"
#include "ui_adjustbc.h"

AdjustBC::AdjustBC(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdjustBC) {
    ui->setupUi(this);
    lastB=ui->sldrB->value();
    lastC=ui->sldrC->value();
}

AdjustBC::~AdjustBC() {
    delete ui;
}

void AdjustBC::adjusted() {
    double B=ui->sldrB->value()/100.0;
    B=(B<0?B/2:B);
    double C=ui->sldrC->value()/100.0;
    emit updateAdjustBC(B,C);
}

void AdjustBC::on_checkBox_stateChanged(int state) {
    if(state==0) emit stopPreview();
    else {
        emit startPreview();
        adjusted();
    }
}

void AdjustBC::on_AdjustBC_finished(int result) {
    ui->checkBox->setCheckState(Qt::CheckState::Unchecked);
    if(result==QDialog::Rejected) {
        ui->sldrB->setValue(lastB);
        ui->sldrC->setValue(lastC);
    } else {
        lastB=ui->sldrB->value();
        lastC=ui->sldrC->value();
    }
}
