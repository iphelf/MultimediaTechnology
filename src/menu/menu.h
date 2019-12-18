#ifndef MENU_H
#define MENU_H

#include <QDialog>

namespace Ui {
class Menu;
}

class QListWidgetItem;

class Menu : public QDialog {
    Q_OBJECT

  public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    void initFeature();
    void openFeature(QString featureName);

  private slots:
    void on_btnOpen_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

  private:
    Ui::Menu *ui;
    QStringList *featureList;
};

#endif // MENU_H
