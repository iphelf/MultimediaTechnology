#ifndef ANIMATE_H
#define ANIMATE_H

#include <QMainWindow>
#include "src/bitmap/convertor.h"
#include <opencv2/opencv.hpp>

namespace Ui {
class Animate;
}

class QTimer;

class Animate : public QMainWindow {
    Q_OBJECT

  public:
    explicit Animate(QWidget *parent = nullptr);
    ~Animate();
  private slots:
    void setImage1();
    void setImage2();
    void animate();
    void updateAnimation();
    void on_btnImage1_clicked();
    void on_btnImage2_clicked();
    void on_btnAnimate_clicked();

  private:
    Ui::Animate *ui;
    QTimer *timer;
    int interval=100; //0.1s
    int nFrame=100; //Total=100*0.1s=10s
    int iFrame;
    bool ready1;
    bool ready2;
    cv::Mat mat1;
    cv::Mat mat2;
    cv::Mat tweenBefore;
    cv::Mat tweenMiddle;
    cv::Mat tweenAfter;
};

#endif // ANIMATE_H
