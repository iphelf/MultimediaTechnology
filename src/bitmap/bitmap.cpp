#include "bitmap.h"
#include "ui_bitmap.h"
#include <QFileDialog>
#include <QGraphicsScene>
#include "src/console.h"
#include "modegrayscale.h"
#include "adjustbc.h"
#include "convertor.h"

Bitmap::Bitmap(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Bitmap) {
    ui->setupUi(this);
    clearBitmap();
    preview=false;
    modeGrayscale=new ModeGrayscale(this);
    QObject::connect(modeGrayscale,SIGNAL(startPreview()),
                     this,SLOT(startPreview()));
    QObject::connect(modeGrayscale,SIGNAL(stopPreview()),
                     this,SLOT(stopPreview()));
    QObject::connect(modeGrayscale,SIGNAL(updateModeGrayscale(int,double*)),
                     this,SLOT(updateModeGrayscale(int,double*)));
    adjustBC=new AdjustBC(this);
    QObject::connect(adjustBC,SIGNAL(startPreview()),
                     this,SLOT(startPreview()));
    QObject::connect(adjustBC,SIGNAL(stopPreview()),
                     this,SLOT(stopPreview()));
    QObject::connect(adjustBC,SIGNAL(updateAdjustBC(double,double)),
                     this,SLOT(updateAdjustBC(double,double)));
}

Bitmap::~Bitmap() {
    delete ui;
}

void Bitmap::clearBitmap() {
    ui->labelBitmap->clear();
    ui->labelBitmap->setText("Please open a BMP file.\n"
                             "Ctrl+O or click File->Open... in the menu bar");
}

void Bitmap::showBitmap() {
    if(mat.empty() || (preview&&pmat.empty())) return;
    img=cvtMat2QImage(preview?pmat:mat);
    pix=(QPixmap::fromImage(img)).scaled(ui->labelBitmap->size(),
                                         Qt::KeepAspectRatio);
    ui->labelBitmap->setPixmap(pix);
}

void Bitmap::startPreview() {
    preview=true;
    showBitmap();
}

void Bitmap::stopPreview() {
    preview=false;
    showBitmap();
}

void Bitmap::updateModeGrayscale(int method, double *w) {
    pmat=toGrayscale(mat,method,w);
    if(preview) showBitmap();
}

void Bitmap::updateAdjustBC(double b, double c) {
    pmat=changeBC(mat,b,c);
    if(preview) showBitmap();
}

void Bitmap::acceptChange() {
    mat=pmat;
}

void Bitmap::on_actionOpen_triggered() {
    QString filename = QFileDialog::getOpenFileName(this,
                       tr("Open Image"),"", tr("Bitmap Files (*.bmp)"));
    if(filename.isEmpty()) return;
    mat=cv::imread(filename.toStdString(),1);
    pmat=mat.clone();
    showBitmap();
}

void Bitmap::on_actionModeGrayscale_triggered() {
    if(modeGrayscale->exec()==QDialog::Accepted) acceptChange();
    preview=false;
    showBitmap();
}

void Bitmap::on_actionAdjustBrightnessContrast_triggered() {
    if(adjustBC->exec()==QDialog::Accepted) acceptChange();
    preview=false;
    showBitmap();
}

void Bitmap::on_actionSaveAs_triggered() {
    QString filename=QFileDialog::getSaveFileName(this,
                     tr("Save as..."),"",tr("Bitmap Files (*.bmp)"));
    if(filename.isEmpty()) return;
    cv::imwrite(filename.toStdString(),mat);
}

void Bitmap::on_actionClose_triggered() {
    clearBitmap();
}
