#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QObject>
#include <QBuffer>
#include <QXmlStreamReader>
#include <QEventLoop>
#include <QMessageBox>

struct Item
{
    QString title;
    QUrl link;
    QString description;
    QString category;
    QString pubDate;
    bool    is_ready;

    bool operator ==(const Item& b)
    {
        return(title == b.title && link == b.link && pubDate == b.pubDate);
    }
};



class Xmlparser : QObject
{
    Q_OBJECT
public:
    Xmlparser();
    Xmlparser(const QUrl urltorss);

    bool parse(const QUrl& urlrss);
    bool parse();

    void seturlrss(const QUrl urlrss);

    QUrl geturlrss() const;
    QVector<Item> &getitems();

private:
    void itemparse(QXmlStreamReader& xml);

    QUrl urlrss;
    bool first_start = true;
    QVector<Item> items;
};
