#include "animate.h"
#include "ui_animate.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QTimer>
#include "src/bitmap/convertor.h"

Animate::Animate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Animate) {
    ui->setupUi(this);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(updateAnimation()));
    ready1=false;
    ready2=false;
    ui->btnAnimate->setEnabled(false);
    ui->statusBar->showMessage(QString("Not Ready"));
}

Animate::~Animate() {
    delete ui;
}

void Animate::setImage1() {
    QString filename = QFileDialog::getOpenFileName(this,
                       tr("Open Image"),"", tr("Bitmap Files (*.bmp)"));
    if(filename.isEmpty()) return;
    mat1=cv::imread(filename.toStdString(),1);
    QImage img=cvtMat2QImage(mat1);
    QPixmap pix=(QPixmap::fromImage(img)).scaled(ui->image1->size(),
                Qt::KeepAspectRatio);
    ui->image1->setPixmap(pix);
    ready1=true;
    if(ready2 && mat1.size()==mat2.size()) {
        ui->btnAnimate->setEnabled(true);
        ui->statusBar->showMessage(QString("Ready"));
    } else {
        ui->btnAnimate->setEnabled(false);
        ui->statusBar->showMessage(QString("Not Ready"));
    }
}

void Animate::setImage2() {
    QString filename = QFileDialog::getOpenFileName(this,
                       tr("Open Image"),"", tr("Bitmap Files (*.bmp)"));
    if(filename.isEmpty()) return;
    mat2=cv::imread(filename.toStdString(),1);
    QImage img=cvtMat2QImage(mat2);
    QPixmap pix=(QPixmap::fromImage(img)).scaled(ui->image2->size(),
                Qt::KeepAspectRatio);
    ui->image2->setPixmap(pix);
    ready2=true;
    if(ready1 && mat1.size()==mat2.size()) {
        ui->btnAnimate->setEnabled(true);
        ui->statusBar->showMessage(QString("Ready"));
    } else {
        ui->btnAnimate->setEnabled(false);
        ui->statusBar->showMessage(QString("Not Ready"));
    }
}

void Animate::animate() {
    iFrame=0;
    tweenBefore=mat1;
    tweenAfter=mat2;
    timer->start(interval);
}

void Animate::updateAnimation() {
    if(iFrame>nFrame) {
        timer->stop();
        if(ready1&&ready2&&mat1.size()==mat2.size()) {
            ui->btnAnimate->setEnabled(true);
            ui->statusBar->showMessage(QString("Ready"));
        } else {
            ui->btnAnimate->setEnabled(false);
            ui->statusBar->showMessage(QString("Not Ready"));
        }
        return;
    }
    ui->statusBar->showMessage(QString("Play: %1/%2").arg(iFrame).arg(nFrame));
    tweenMiddle=transit(tweenBefore,tweenAfter,1.0*iFrame/nFrame);
    QImage img=cvtMat2QImage(tweenMiddle);
    QPixmap pix=(QPixmap::fromImage(img)).scaled(ui->animation->size(),
                Qt::KeepAspectRatio);
    ui->animation->setPixmap(pix);
    iFrame++;
}

void Animate::on_btnImage1_clicked() {
    setImage1();
}

void Animate::on_btnImage2_clicked() {
    setImage2();
}

void Animate::on_btnAnimate_clicked() {
    nFrame=QInputDialog::getInt(this,"Animation",
                                "Specify number of frames",
                                nFrame,1);
    animate();
}
