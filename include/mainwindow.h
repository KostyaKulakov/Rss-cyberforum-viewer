#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "xmlparser.h"
#include "wsetting.h"
#include "wabout.h"
#include "settings.h"
#include <QMainWindow>
#include <QtConcurrent/QtConcurrent>
#include <QSystemTrayIcon>
#include <QFuture>
#include <QSound>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void updateTable();
    void updateTimer();
    void showHide(QSystemTrayIcon::ActivationReason r);

private:
    Ui::MainWindow *ui;
    QSystemTrayIcon *trIcon;
    Settings* msettings;
    WAbout wabout;
    WSetting* wsetting;
    Xmlparser* parser;
    QTimer timer;
    QSound* sound;
    bool    is_first;
};

#endif // MAINWINDOW_H
