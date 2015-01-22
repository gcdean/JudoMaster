#include "Bracket.h"

#include <QString>

namespace
{
    const QString AgeTypeStr("AgeType");
    const QString WeightTypeStr("WeightType");
    QString bracketTypeToStr(Bracket::BracketType type)
    {
        switch(type)
        {
            case Bracket::Age:
                return AgeTypeStr;
            case Bracket::Weight:
                return WeightTypeStr;
            default:
                return AgeTypeStr;
        }
    }

    Bracket::BracketType bracketTypeFromString(QString typeStr)
    {
        if(typeStr.compare(WeightTypeStr, Qt::CaseInsensitive) == 0)
            return Bracket::Weight;

        return Bracket::Age;
    }

    const QString AbsoluteStr("Absolute");
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
    , m_bracketType(Bracket::Age)
    , m_weightType(Bracket::LightMediumHeavy)
    , m_minAge(0)
    , m_maxAge(0)
    , m_maxWeight(0.0)
{    
}

Bracket::Bracket(int id)
    : JMDataObj(id)
    , m_name("")
    , m_bracketType(Bracket::Age)
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
    m_bracketType = src.type();
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

void Bracket::read(const QJsonObject &json)
{
    JMDataObj::read(json);
    m_name = json["name"].toString();
    m_bracketType = bracketTypeFromString(json["bracketType"].toString());
    m_weightType = weightTypeFromStr(json["weightType"].toString());
    m_minAge = json["minAge"].toInt();
    m_maxAge = json["maxAge"].toInt();
    m_maxWeight = json["maxWeight"].toDouble();
}

void Bracket::write(QJsonObject &json) const
{
    JMDataObj::write(json);
    json["name"] = m_name;
    json["bracketType"] = bracketTypeToStr(m_bracketType);
    json["weightType"] = weightTypeToStr(m_weightType);
    json["minAge"] = m_minAge;
    json["maxAge"] = m_maxAge;
    json["maxWeight"] = m_maxWeight;
}
