#include "Bracket.h"

#include "JMUtil.h"

#include "Competitor.h"
#include "CompetitorController.h"
#include "JudoMasterApplication.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonValue>
#include <QString>


namespace bracket
{
    const QString AbsoluteStr("IJF");
    const QString LightStr("Light");
    const QString MediumStr("Medium");
    const QString HeavyStr("Heavy");
    const QString SuperHeavyStr("Super Heavy");
    const QString UnknownWeightType("Unknown");
}

using namespace bracket;

Bracket::Bracket()
    : JMDataObj(-1)
    , m_name("")
    , m_gender(JM::Male)
    , m_weightType(Bracket::Light)
    , m_minAge(0)
    , m_maxAge(0)
    , m_time(3)
    , m_chokesAllowed(false)
    , m_armbarsAllowed(false)
    , m_matNumber(0)
    , m_firstPlace(-1)
    , m_secondPlace(-1)
    , m_thirdPlace_1(-1)
    , m_thirdPlace_2(-1)
    , m_maxWeight(0.0)
{
}

Bracket::Bracket(int id)
    : JMDataObj(id)
    , m_name("")
    , m_gender(JM::Male)
    , m_weightType(Bracket::Light)
    , m_minAge(0)
    , m_maxAge(0)
    , m_time(3)
    , m_chokesAllowed(false)
    , m_armbarsAllowed(false)
    , m_matNumber(0)
    , m_firstPlace(-1)
    , m_secondPlace(-1)
    , m_thirdPlace_1(-1)
    , m_thirdPlace_2(-1)
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
    m_time = src.time();
    m_maxWeight = src.maxWeight();
    m_chokesAllowed = src.chokesAllowed();
    m_armbarsAllowed = src.armbarsAllowed();
    m_matNumber = src.matNumber();
    m_firstPlace = src.firstPlace();
    m_secondPlace = src.secondPlace();
    m_thirdPlace_1 = src.thirdPlace1();
    m_thirdPlace_2 = src.thirdPlace2();
}

Bracket::Bracket(const QJsonObject &json)
    : JMDataObj(json)
{
    // The base class constructor will call read
}

void Bracket::read(const QJsonObject &json)
{
    read(json, QList<Competitor *>());
}

void Bracket::read(const QJsonObject &json, const QList<Competitor *>competitors)
{
    JMDataObj::read(json);
    m_name = json["name"].toString();
    m_gender = genderFromString(json["gender"].toString());
    m_weightType = weightTypeFromStr(json["weightType"].toString());
    m_minAge = json["minAge"].toInt();
    m_maxAge = json["maxAge"].toInt();
    m_time = json["time"].toInt();
    if(m_time == 0)     // Default to 3 min.
        m_time = 3;
    m_maxWeight = json["maxWeight"].toDouble();
    m_chokesAllowed = json["chokesAllowed"].toBool();
    m_armbarsAllowed = json["armbarsAllowed"].toBool();
    m_matNumber = json["matNumber"].toInt();
    m_firstPlace = json["firstPlace"].toInt();
    m_secondPlace = json["secondPlace"].toInt();
    m_thirdPlace_1 = json["thirdPlace1"].toInt();
    m_thirdPlace_2 = json["thirdPlace2"].toInt();

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
    json["time"] = m_time;
    json["maxWeight"] = m_maxWeight;
    json["chokesAllowed"] = m_chokesAllowed;
    json["armbarsAllowed"] = m_armbarsAllowed;
    json["matNumber"] = m_matNumber;
    json["firstPlace"] = m_firstPlace;
    json["secondPlace"] = m_secondPlace;
    json["thirdPlace1"] = m_thirdPlace_1;
    json["thirdPlace2"] = m_thirdPlace_2;

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

void Bracket::removeCompetitor(int index)
{
    if(index < 0 || index >= m_competitors.size())
        return;

    m_competitors.removeAt(index);
}

void Bracket::moveCompetitor(int srcRow, int destRow)
{
    m_competitors.move(srcRow, destRow);
}

QString Bracket::weightTypeToStr(Bracket::WeightType type)
{

    switch(type)
    {
        case Bracket::Light:
            return LightStr;
            break;
        case Bracket::Medium:
            return MediumStr;
            break;
        case Bracket::Heavy:
            return HeavyStr;
            break;
        case Bracket::SuperHeavy:
            return SuperHeavyStr;
            break;
        case Bracket::IJF:
            return AbsoluteStr;
            break;

    default:
        return UnknownWeightType;
    }
}


Bracket::WeightType Bracket::weightTypeFromStr(QString typeStr)
{
    if(typeStr.compare(LightStr, Qt::CaseInsensitive) == 0)
        return Bracket::Light;
    if(typeStr.compare(MediumStr, Qt::CaseInsensitive) == 0)
        return Bracket::Medium;
    if(typeStr.compare(HeavyStr, Qt::CaseInsensitive) == 0)
        return Bracket::Heavy;
    if(typeStr.compare(SuperHeavyStr, Qt::CaseInsensitive) == 0)
        return Bracket::SuperHeavy;
    if(typeStr.compare(AbsoluteStr, Qt::CaseInsensitive) == 0)
        return Bracket::IJF;

    qDebug() << "WARNING!!! Unknown Weight Type Specified: [" << typeStr << "]";

    return Bracket::Light;
}
