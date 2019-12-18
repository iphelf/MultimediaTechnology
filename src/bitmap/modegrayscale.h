#ifndef MODEGRAYSCALE_H
#define MODEGRAYSCALE_H

#include <QDialog>

namespace Ui {
class ModeGrayscale;
}

class ModeGrayscale : public QDialog {
    Q_OBJECT

  public:
    explicit ModeGrayscale(QWidget *parent = nullptr);
    ~ModeGrayscale();

  signals:
    void startPreview();
    void stopPreview();
    void updateModeGrayscale(int method,double *w);

  private slots:
    void on_checkBox_stateChanged(int state);
    void adjusted();
    void on_ModeGrayscale_finished(int result);

  private:
    Ui::ModeGrayscale *ui;
    int lastMethod;
    int lastR;
    int lastG;
    int lastB;
};

#endif // MODEGRAYSCALE_H
