#include "settings.h"

Settings::Settings(const QString& namefile)
{
    fsettings = new QSettings(namefile, QSettings::IniFormat);

    is_sound  = fsettings->value("interface/is_playsound", true).toBool();
    interval  = fsettings->value("interface/interval", 10000).toUInt();
    urlrss    = fsettings->value("interface/urlrss", "http://www.cyberforum.ru/external.php?type=RSS2").toString();

    unsigned size = fsettings->beginReadArray("AllowCat");

    for(unsigned i = 0; i < size; ++i)
    {
        fsettings->setArrayIndex(i);
        allow_cat.push_back(fsettings->value("Category").toString());
    }

    fsettings->endArray();

}

void Settings::setPlaymusic(const bool enable)
{
    is_sound = enable;

    fsettings->setValue("interface/is_playsound", enable);

    fsettings->sync();
}

void Settings::setInterval(const unsigned interval)
{
    this->interval = interval;

    fsettings->setValue("interface/interval", interval);

    fsettings->sync();
}

void Settings::setUrlRss(const QString url)
{
    this->urlrss = url;

    fsettings->setValue("interface/urlrss", url);

    fsettings->sync();
}

void Settings::setAllowCategory(QVector<QString> allow_cat)
{
    this->allow_cat = allow_cat;

    fsettings->beginWriteArray("AllowCat");

    for(unsigned int i = 0; i < (unsigned)allow_cat.size(); i++)
    {
        fsettings->setArrayIndex(i);
        fsettings->setValue("Category", allow_cat.at(i));
    }

    fsettings->endArray();

    fsettings->sync();

}

bool Settings::getPlaymusic() const
{
    return is_sound;
}

unsigned Settings::getInterval() const
{
    return interval;
}

QString Settings::getUrlRss() const
{
    return urlrss;
}

QVector<QString> Settings::getAllowCategory() const
{
    return allow_cat;
}

