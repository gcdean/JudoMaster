#include "Tournament.h"

#include <QJsonArray>
#include <QJsonObject>

Tournament::Tournament(QObject *parent) :
    QObject(parent)
{
}

void Tournament::read(QJsonObject &json)
{
    m_name = json["name"].toString();
    m_date = QDate::fromString(json["date"].toString(), "dd.mm.yyyy");
    m_startTime = QTime::fromString(json["name"].toString(), "HH.mm");
}

void Tournament::write(QJsonObject &json) const
{
    json["name"] = m_name;
    json["date"] = m_date.toString("dd.mm.yyyy");
    json["starttime"] = m_startTime.toString("HH.mm");

    // Clubs
    QJsonArray clubArray;
    foreach(const Club* club, m_clubs)
    {
        QJsonObject jobj;
        club->write(jobj);
        clubArray.append(jobj);
    }

    json["clubs"] = clubArray;

    // Competitors
    QJsonArray judokas;
    foreach(Competitor *judoka, m_competitors)
    {
        QJsonObject jobj;
        judoka->write(jobj);
        judokas.append(jobj);
    }

    json["competitors"] = judokas;
}

