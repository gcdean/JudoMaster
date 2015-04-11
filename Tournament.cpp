#include "Tournament.h"

#include "Bracket.h"
#include "Club.h"
#include "Competitor.h"
#include "Match.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QTextStream>

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

    // Read the matches
    QJsonArray matches = json["matches"].toArray();
    for(int x = 0; x < matches.size(); x++)
    {
        QJsonObject jobj = matches[x].toObject();
        Match *match = new Match();
        match->read(jobj, m_competitors);
        m_matches.append(match);
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

    //  Matches
    QJsonArray matches;
    foreach(Match *match, m_matches)
    {
        QJsonObject jobj;
        match->write(jobj);
        matches.append(jobj);
    }
    json["matches"] = matches;
}

void Tournament::write(QString dirname) const
{
    QDir outputDir(dirname);

    QFile clubFile(outputDir.absoluteFilePath("Clubs.csv"));
    clubFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream clubStream(&clubFile);

    writeClubHeader(clubStream);
    foreach(const Club* club, m_clubs)
    {
        club->write(clubStream);
    }
    clubFile.close();

    QFile bracketFile(outputDir.absoluteFilePath("Brackets.csv"));
    bracketFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream bracketStream(&bracketFile);
    writeBracketHeader(bracketStream);

    foreach(Bracket *bracket, m_brackets)
    {
        bracket->write(bracketStream);
    }
    bracketFile.close();

    QFile bracketCompFile(outputDir.absoluteFilePath("BracketCompetitors.csv"));
    bracketCompFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream bracketCompStream(&bracketCompFile);


    writeBracketCompetitorHeader(bracketCompStream);

    foreach(Bracket *bracket, m_brackets)
    {
        bracket->writeCompetitors(bracketCompStream);
    }
    bracketCompFile.close();

    QFile bracketPlaceFile(outputDir.absoluteFilePath("BracketPlaces.csv"));
    bracketPlaceFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream bracketPlaceStream(&bracketPlaceFile);
    writeBracketPlaceHeader(bracketPlaceStream);

    foreach(Bracket *bracket, m_brackets)
    {
        bracket->writePlaces(bracketPlaceStream);
    }
    bracketPlaceFile.close();


    QFile competitorFile(outputDir.absoluteFilePath("Competitors.csv"));
    competitorFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream competitorStream(&competitorFile);
    writeCompetitorHeader(competitorStream);
    foreach (Competitor *competitor, m_competitors)
    {
        competitor->write(competitorStream);
    }
    competitorFile.close();

    QFile matchFile(outputDir.absoluteFilePath("Matches.csv"));
    matchFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream matchStream(&matchFile);
    writeMatchHeader(matchStream);
    foreach(Match *match, m_matches)
    {
        match->write(matchStream);
    }
    matchFile.close();

}

