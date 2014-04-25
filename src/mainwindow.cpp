#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    is_first(true)
{
    ui->setupUi(this);
    msettings = new Settings("config.conf");

    wsetting = new WSetting(this, msettings);

    parser = new Xmlparser;

    parser->seturlrss(QUrl(msettings->getUrlRss())); // Default

    sound = new QSound(":/music/sirena.wav");

    trIcon = new QSystemTrayIcon();
    trIcon->setIcon(QIcon(":/icon/rss_orb_2121.ico"));
    trIcon->show();

    connect(ui->setting,&QAction::triggered,    this->wsetting,    &WSetting::show);
    connect(ui->about,  &QAction::triggered,    &this->wabout,     &WAbout::show);
    connect(ui->exit,   &QAction::triggered,    this,   &QApplication::quit);
    connect(&timer,     &QTimer::timeout,       this,   &MainWindow::updateTable);
    connect(this->wsetting, &QDialog::close, this,  &MainWindow::updateTimer);
    connect(trIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(showHide(QSystemTrayIcon::ActivationReason)));

    timer.start(msettings->getInterval());

    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 200);

    QtConcurrent::run(this, &MainWindow::updateTable);

    trIcon->showMessage("Cyberforum rss", "Привет, программа запущена в трей. Обнаружение новой темы будет сопровождаться звуковым сигналом и сообщением.");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateTable()
{
    parser->parse();

    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);

    for(auto &item : (parser->getitems()))
    {
       if((msettings->getAllowCategory().indexOf(item.category) != -1) || msettings->getAllowCategory().size() == 0)
       {
            if(!item.is_ready && !is_first)
            {
                QApplication::alert(this);

                if(msettings->getPlaymusic())
                    this->sound->play();

                trIcon->showMessage("Новая тема", item.title);
            }

            ui->tableWidget->insertRow(ui->tableWidget->rowCount());

            QTableWidgetItem *title = new QTableWidgetItem(item.title);
            QTableWidgetItem *link = new QTableWidgetItem(item.link.toString());
            QTableWidgetItem *description = new QTableWidgetItem(item.description);
            QTableWidgetItem *category = new QTableWidgetItem(item.category);
            QTableWidgetItem *pubDate = new QTableWidgetItem(item.pubDate);


            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0, title);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, link);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, description);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, category);
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, pubDate);

            item.is_ready = true;
        }
    }

    ui->tableWidget->resizeColumnToContents(3);
    ui->tableWidget->resizeColumnToContents(4);

    is_first = false;
}

void MainWindow::updateTimer()
{
    timer.setInterval(msettings->getInterval());
    parser->seturlrss(QUrl(msettings->getUrlRss()));
    updateTable();
}

void MainWindow::showHide(QSystemTrayIcon::ActivationReason r)
{
    if (r == QSystemTrayIcon::Trigger)
    {
       if (!this->isVisible())
       {
           this->show();
           this->activateWindow();
       }
       else
           this->hide();
    }
}
