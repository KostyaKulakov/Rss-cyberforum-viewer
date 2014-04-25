#include "wabout.h"
#include "ui_wabout.h"

WAbout::WAbout(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WAbout)
{
    ui->setupUi(this);
}

WAbout::~WAbout()
{
    delete ui;
}
