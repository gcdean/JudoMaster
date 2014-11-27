#include "Competitor.h"

Competitor::Competitor(int id, QString firstName, QString lastName, QString gender, int age , double weight, Rank rank, int clubId) :
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

void Competitor::read(QJsonObject &json)
{
    m_id = json["id"].toInt();
    m_firstName = json["fname"].toString();
    m_lastName = json["lname"].toString();
    m_gender = json["gender"].toString();
    m_weight = json["weight"].toDouble();

    int rval = json["rank"].toInt();
    switch(rval)
    {
        case 0:
            m_rank = White;
        break;

        case 1:
            m_rank = Yellow;
        break;

        case 2:
            m_rank = Orange;
        break;

        case 3:
            m_rank = Green;
        break;

        case 4:
            m_rank = Blue;
        break;

        case 5:
            m_rank = Purple;
        break;

        case 6:
            m_rank = Brown;
        break;

        case 7:
            m_rank = Black;
        break;

        default:
            m_rank = Unknown;
    }

    m_clubId = json["clubid"].toInt();

}

void Competitor::write(QJsonObject &json) const
{
    json["id"] = m_id;
    json["fname"] = m_firstName;
    json["lname"] = m_lastName;
    json["gender"] = m_gender;
    json["weight"] = m_weight;

    int rval = 0;
    switch(m_rank)
    {
        case White:
            rval = 0;
        break;

        case Yellow:
            rval = 1;
        break;

        case Orange:
            rval = 2;
        break;

        case Green:
            rval = 3;
        break;

        case Blue:
            rval = 4;
        break;

        case Purple:
            rval = 5;
        break;

        case Brown:
            rval = 6;
        break;

        case Black:
            rval = 7;
        break;

        default:
            rval = 8;
    }

    json["rank"] = rval;
    json["clubid"] = m_clubId;
}
