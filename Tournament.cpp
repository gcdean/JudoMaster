#include "Tournament.h"

#include "Bracket.h"

#include <QJsonArray>
#include <QJsonObject>

Tournament::Tournament(QObject *parent) :
    QObject(parent)
{
}

void Tournament::read(QJsonObject &json)
{
    m_name = json["name"].toString();
    m_date = QDate::fromString(json["date"].toString(), "dd.MM.yyyy");
    m_startTime = QTime::fromString(json["starttime"].toString(), "HH.mm");

    // Read the clubs
    QJsonArray clubs = json["clubs"].toArray();
    for(int x = 0; x < clubs.size(); x++)
    {
        QJsonObject jobj = clubs[x].toObject();
        Club *club = new Club();
        club->read(jobj);
        m_clubs.append(club);
    }

    // Read the competitors
    QJsonArray competitors = json["competitors"].toArray();
    for(int x = 0; x < competitors.size(); x++)
    {
        QJsonObject jobj = competitors[x].toObject();
        Competitor *competitor = new Competitor();
        competitor->read(jobj);
        m_competitors.append(competitor);

    }

    // Read the brackets
    QJsonArray brackets = json["brackets"].toArray();
    for(int x = 0; x < brackets.size(); x++)
    {
        QJsonObject jobj = brackets[x].toObject();
        Bracket *bracket = new Bracket();
        bracket->read(jobj, m_competitors);
        m_brackets.append(bracket);
    }
}

void Tournament::write(QJsonObject &json) const
{
    json["name"] = m_name;
    QString temp = m_date.toString("dd.MM.yyyy");
    json["date"] = temp;
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

    // Brackets
    QJsonArray brackets;
    foreach(Bracket *bracket, m_brackets)
    {
        QJsonObject jobj;
        bracket->write(jobj);
        brackets.append(jobj);
    }

    json["brackets"] = brackets;
}

