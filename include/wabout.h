#ifndef WABOUT_H
#define WABOUT_H

#include <QWidget>

namespace Ui {
class WAbout;
}

class WAbout : public QWidget
{
    Q_OBJECT

public:
    explicit WAbout(QWidget *parent = 0);
    ~WAbout();

private:
    Ui::WAbout *ui;
};

#endif // WABOUT_H
