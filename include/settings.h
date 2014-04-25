#pragma once
#include <QSettings>
#include <QVector>

class Settings
{
public:
    Settings(const QString& namefile);

    void setPlaymusic(const bool enable);
    void setInterval(const unsigned interval);
    void setUrlRss(const QString url);
    void setAllowCategory(QVector<QString> allow_cat);

    bool                getPlaymusic()      const;
    unsigned            getInterval()       const;
    QString             getUrlRss()         const;
    QVector<QString>    getAllowCategory()  const;

private:
    bool is_sound = false;
    unsigned interval;
    QString urlrss;
    QVector<QString> allow_cat;

    QSettings *fsettings;
};

