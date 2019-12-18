#ifndef ADJUSTBC_H
#define ADJUSTBC_H

#include <QDialog>

namespace Ui {
class AdjustBC;
}

class AdjustBC : public QDialog {
    Q_OBJECT

  public:
    explicit AdjustBC(QWidget *parent = nullptr);
    ~AdjustBC();

  signals:
    void startPreview();
    void stopPreview();
    void updateAdjustBC(double b,double c);

  public slots:
    void adjusted();

  private slots:
    void on_checkBox_stateChanged(int state);
    void on_AdjustBC_finished(int result);

  private:
    Ui::AdjustBC *ui;
    int lastB;
    int lastC;
};

#endif // ADJUSTBC_H
