#ifndef WSETTING_H
#define WSETTING_H

#include <QDialog>
#include <QVector>
#include "settings.h"

namespace Ui {
class WSetting;
}

class WSetting : public QDialog
{
    Q_OBJECT

public:
    explicit WSetting(QWidget *parent = 0, Settings *msettings = 0);
    ~WSetting();
    bool is_allow(QString catname);
    unsigned get_count();

private slots:
    void on_addButton_clicked();

    void on_removeButton_clicked();

public slots:
    void on_buttonBox_accepted();

private:
    Ui::WSetting *ui;
    Settings* msettings;
};

#endif // WSETTING_H
