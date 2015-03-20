#include "Tournament.h"

#include "Bracket.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

namespace
{
    // TODO: Put this is a global namespace. Duplicated in the PrintBrackets command.
    bool compareClubs(Club* club1, Club* club2)
    {
        return club1->clubName().compare(club2->clubName(), Qt::CaseInsensitive) < 0;
    }

}
Tournament::Tournament(QObject *parent) :
    QObject(parent)
{
}

void Tournament::read(QJsonObject &json)
{
    m_name = json["name"].toString();
    m_date = QDate::fromString(json["date"].toString(), "dd.MM.yyyy");
    m_startTime = QTime::fromString(json["starttime"].toString(), "HH.mm");

    // Read the competitors
    QJsonArray competitors = json["competitors"].toArray();
    for(int x = 0; x < competitors.size(); x++)
    {
        QJsonObject jobj = competitors[x].toObject();
        Competitor *competitor = new Competitor();
        competitor->read(jobj);
        m_competitors.append(competitor);

    }
    qDebug() << "Total Competitors Read In: " << m_competitors.size();

    // Read the clubs
    QJsonArray clubs = json["clubs"].toArray();
    for(int x = 0; x < clubs.size(); x++)
    {
        QJsonObject jobj = clubs[x].toObject();
        Club *club = new Club();
        club->read(jobj, m_competitors);
        m_clubs.append(club);
    }

    // Let's sort the clubs by name.
    // TODO: Need to make this part of the model and not force it here.
    std::sort(m_clubs.begin(), m_clubs.end(), compareClubs);

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
        qDebug() << "Saving Competitor: " << judoka->lastName() << ", " << judoka->firstName();
        QJsonObject jobj;
        judoka->write(jobj);
        judokas.append(jobj);
    }

    qDebug() << "Total Competitors Saved: " << judokas.size();
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

