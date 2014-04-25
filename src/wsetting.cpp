#include "wsetting.h"
#include "ui_wsetting.h"

WSetting::WSetting(QWidget *parent, Settings *msettings) :
    QDialog(parent),
    ui(new Ui::WSetting)
{
    this->msettings = msettings;

    ui->setupUi(this);
    ui->spinBox->setValue(msettings->getInterval()/1000);
    ui->checkBox->setChecked(msettings->getPlaymusic());
    ui->lineEdit->setText(msettings->getUrlRss());

    for(auto &v : msettings->getAllowCategory())
        ui->onlinelist->addItem(v);
}

WSetting::~WSetting()
{
    delete ui;
}

bool WSetting::is_allow(QString catname)
{
    for(size_t i = 0; i < get_count(); ++i)
        if(ui->onlinelist->item(i)->text() == catname)
            return true;

    return false;
}

unsigned WSetting::get_count()
{
    return ui->onlinelist->count();
}

void WSetting::on_addButton_clicked()
{
    if(is_allow(ui->catlist->currentItem()->text()))
        return;

    ui->onlinelist->addItem(ui->catlist->currentItem()->text());
}


void WSetting::on_removeButton_clicked()
{
    ui->onlinelist->takeItem(ui->onlinelist->currentRow());
}


void WSetting::on_buttonBox_accepted()
{
    msettings->setInterval(ui->spinBox->value()*1000);
    msettings->setPlaymusic(ui->checkBox->isChecked());
    msettings->setUrlRss(ui->lineEdit->text());

    QVector<QString> mallow_cat;

    for(size_t i = 0; i < get_count(); ++i)
        mallow_cat.push_back(ui->onlinelist->item(i)->text());

    msettings->setAllowCategory(mallow_cat);
}
