#include "modegrayscale.h"
#include "ui_modegrayscale.h"

ModeGrayscale::ModeGrayscale(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModeGrayscale) {
    ui->setupUi(this);
    ui->btngrp->setId(ui->radioMean,0);
    ui->btngrp->setId(ui->radioMax,1);
    ui->btngrp->setId(ui->radioMin,2);
    ui->btngrp->setId(ui->radioWeighed,3);
    lastMethod=ui->btngrp->checkedId();
    lastR=ui->sldrR->value();
    lastG=ui->sldrG->value();
    lastB=ui->sldrB->value();
}

ModeGrayscale::~ModeGrayscale() {
    delete ui;
}

void ModeGrayscale::on_checkBox_stateChanged(int state) {
    if(state==0) emit stopPreview();
    else {
        emit startPreview();
        adjusted();
    }
}

void ModeGrayscale::adjusted() {
    int method=ui->btngrp->checkedId();
    double *w=nullptr;
    if(method==3) {
        w=new double[3];
        w[0]=ui->sldrR->value()/100.0;
        w[1]=ui->sldrG->value()/100.0;
        w[2]=ui->sldrB->value()/100.0;
    }
    emit updateModeGrayscale(method,w);
}

void ModeGrayscale::on_ModeGrayscale_finished(int result) {
    ui->checkBox->setCheckState(Qt::CheckState::Unchecked);
    if(result==QDialog::Rejected) {
        ui->btngrp->button(lastMethod)->click();
        ui->sldrR->setValue(lastR);
        ui->sldrG->setValue(lastG);
        ui->sldrB->setValue(lastB);
    } else {
        lastMethod=ui->btngrp->checkedId();
        lastR=ui->sldrR->value();
        lastG=ui->sldrG->value();
        lastB=ui->sldrB->value();
    }
}
