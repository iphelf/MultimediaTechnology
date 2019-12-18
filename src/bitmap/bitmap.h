#ifndef BITMAP_H
#define BITMAP_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

namespace Ui {
class Bitmap;
}

class ModeGrayscale;
class AdjustBC;

class Bitmap : public QMainWindow {
    Q_OBJECT

  public:
    explicit Bitmap(QWidget *parent = nullptr);
    ~Bitmap();
    void clearBitmap();
    void showBitmap();
    void acceptChange();

  public slots:
    void startPreview();
    void stopPreview();
    void updateModeGrayscale(int method, double *w);
    void updateAdjustBC(double b,double c);

  private slots:
    void on_actionOpen_triggered();
    void on_actionModeGrayscale_triggered();
    void on_actionAdjustBrightnessContrast_triggered();
    void on_actionSaveAs_triggered();
    void on_actionClose_triggered();

  private:
    Ui::Bitmap *ui;
    cv::Mat mat;
    QPixmap pix;
    QImage img;
    bool preview;
    cv::Mat pmat;
    QPixmap ppix;
    QImage pimg;
    ModeGrayscale *modeGrayscale;
    AdjustBC *adjustBC;
};

#endif // BITMAP_H
