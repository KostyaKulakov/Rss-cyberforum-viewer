#include "xmlparser.h"

Xmlparser::Xmlparser()
{}

Xmlparser::Xmlparser(const QUrl urltorss)
    :
      urlrss(urltorss)
{}

bool Xmlparser::parse(const QUrl &urlrss)
{
    QNetworkAccessManager* m_NetworkMngr = new QNetworkAccessManager(0);
    QNetworkReply *reply= m_NetworkMngr->get(QNetworkRequest(urlrss));
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);

    loop.exec();

    QXmlStreamReader xml(reply->readAll());

    while(!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();

        if(token == QXmlStreamReader::StartDocument)
            continue;

        if(token == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "rss")
                continue;

            if(xml.name() == "channel")
                continue;

            if(xml.name() == "item")
                itemparse(xml);
        }
    }

    xml.clear();

    if(xml.hasError())
        return false;

    first_start = false;

    return true;
}

bool Xmlparser::parse()
{
    return parse(this->urlrss);
}

void Xmlparser::seturlrss(const QUrl urlrss)
{
    this->urlrss = urlrss;
}

QUrl Xmlparser::geturlrss() const
{
    return this->urlrss;
}

QVector<Item> &Xmlparser::getitems()
{
    return this->items;
}

void Xmlparser::itemparse(QXmlStreamReader &xml)
{
    Item newitem;


    while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "item"))
    {
        if(xml.tokenType() == QXmlStreamReader::StartElement)
        {
            if(xml.name() == "title")
                newitem.title = xml.readElementText();
            else if(xml.name() == "link")
                newitem.link = QUrl(xml.readElementText());
            else if(xml.name() == "description")
                newitem.description = xml.readElementText();
            else if(xml.name() == "category")
                newitem.category = xml.readElementText();
            else if(xml.name() == "pubDate")
                newitem.pubDate = xml.readElementText();
        }

        xml.readNext();
    }

    newitem.is_ready = false;

    if(items.indexOf(newitem) != -1)
        return;

    if(first_start)
        this->items.push_back(newitem);
    else
        this->items.push_front(newitem);
}
