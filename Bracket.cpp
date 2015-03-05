#include "Bracket.h"

#include "JMUtil.h"

#include "Competitor.h"
#include "CompetitorController.h"
#include "JudoMasterApplication.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>


namespace
{
    const QString AbsoluteStr("IJF");
    const QString LightMedHeavyStr("LightMedHeavy");
    QString weightTypeToStr(Bracket::WeightType type)
    {
        if(type == Bracket::IJF)
            return AbsoluteStr;
        return LightMedHeavyStr;
    }

    Bracket::WeightType weightTypeFromStr(QString typeStr)
    {
        if(typeStr.compare(AbsoluteStr, Qt::CaseInsensitive) == 0)
            return Bracket::IJF;

        return Bracket::LightMediumHeavy;
    }
}

Bracket::Bracket()
    : JMDataObj(-1)
    , m_name("")
    , m_gender(JM::Male)
    , m_weightType(Bracket::LightMediumHeavy)
    , m_minAge(0)
    , m_maxAge(0)
    , m_maxWeight(0.0)
{    
}

Bracket::Bracket(int id)
    : JMDataObj(id)
    , m_name("")
    , m_gender(JM::Male)
    , m_weightType(Bracket::LightMediumHeavy)
    , m_minAge(0)
    , m_maxAge(0)
    , m_maxWeight(0.0)
{

}

Bracket::Bracket(const Bracket &src)
    : JMDataObj(src)
{
    m_name = src.name();
    m_gender = src.gender();
    m_weightType = src.weightType();
    m_minAge = src.minAge();
    m_maxAge = src.maxAge();
    m_maxWeight = src.maxWeight();
}

Bracket::Bracket(const QJsonObject &json)
    : JMDataObj(json)
{
    // The base class constructor will call read
}

void Bracket::read(const QJsonObject &json, const QList<Competitor *>competitors)
{
    JMDataObj::read(json);
    m_name = json["name"].toString();
    m_gender = genderFromString(json["gender"].toString());
    m_weightType = weightTypeFromStr(json["weightType"].toString());
    m_minAge = json["minAge"].toInt();
    m_maxAge = json["maxAge"].toInt();
    m_maxWeight = json["maxWeight"].toDouble();

    QJsonArray bracketMembers = json["bracketMembers"].toArray();

    for(int x = 0; x < bracketMembers.size(); x++)
    {
        int id = bracketMembers[x].toInt();
        // Now, find the competitor with the specified id.
        foreach(Competitor *competitor, competitors)
        {
            if(id == competitor->id())
            {
                addCompetitor(competitor);
                break;
            }
        }

    }
}

void Bracket::write(QJsonObject &json) const
{
    JMDataObj::write(json);
    json["name"] = m_name;
    json["gender"] = genderToString(m_gender);
    json["weightType"] = weightTypeToStr(m_weightType);
    json["minAge"] = m_minAge;
    json["maxAge"] = m_maxAge;
    json["maxWeight"] = m_maxWeight;

    // Write out the list of competitor ids.
    QJsonArray bracketMembers;
    foreach(const Competitor* competitor, m_competitors)
    {
        QJsonValue id(competitor->id());

        bracketMembers.append(id);
    }

    json["bracketMembers"] = bracketMembers;

}

void Bracket::setGender(JM::Gender gender)
{
    m_gender = gender;
}

JM::Gender Bracket::gender() const
{
    return m_gender;
}

const QList<Competitor *> Bracket::competitors() const
{
    return m_competitors;
}

/**
 * @brief Bracket::addCompetitor - Add a competitor to the bracket
 * @param competitor - The competitor to add
 * @param location - The location within the list. -1 is append.
 * @return
 */
bool Bracket::addCompetitor(Competitor *competitor, int location)
{
    if(0 == competitor)
        return false;

    if(m_competitors.indexOf(competitor) < 0)
    {
        // We can add the competitor, now find out where.
        if(location == -1 || location > m_competitors.size())
        {
            m_competitors.append(competitor);
        }
        else
        {
            m_competitors.insert(location, competitor);
        }
        return true;
    }
    return false;
}
