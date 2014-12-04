#include "Competitor.h"

Competitor::Competitor(int id, QString firstName, QString lastName, JM::Gender gender, int age , double weight, JM::Rank rank, int clubId) :
     m_id(id)
    , m_firstName(firstName)
    , m_lastName(lastName)
    , m_gender(gender)
    , m_age(age)
    , m_weight(weight)
    , m_rank(rank)
    , m_clubId(clubId)
{
}

Competitor::Competitor(const Competitor &src)
{
    m_id = src.id();
    m_firstName = src.firstName();
    m_lastName = src.lastName();
    m_gender = src.gender();
    m_age = src.age();
    m_weight = src.weight();
    m_rank = src.rank();
    m_clubId = src.clubId();
}

Competitor::Competitor(QJsonObject &json)
{
    read(json);
}

void Competitor::read(QJsonObject &json)
{
    m_id = json["id"].toInt();
    m_firstName = json["fname"].toString();
    m_lastName = json["lname"].toString();
    m_gender = genderFromString(json["gender"].toString());
    m_age = json["age"].toInt();
    m_weight = json["weight"].toDouble();

    m_rank = rankFromString(json["rank"].toString());

    m_clubId = json["clubid"].toInt();

}

void Competitor::write(QJsonObject &json) const
{
    json["id"] = m_id;
    json["fname"] = m_firstName;
    json["lname"] = m_lastName;
    json["gender"] = genderToString(m_gender);
    json["age"] = m_age;
    json["weight"] = m_weight;

    json["rank"] = rankToString(m_rank);
    json["clubid"] = m_clubId;
}
