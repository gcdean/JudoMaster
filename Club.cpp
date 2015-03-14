#include "Club.h"

#include "JudoMasterApplication.h"

Club::Club()
    : JMDataObj(-1)
{

}

Club::Club(int id, QString clubName, QString coachName, QString addr1, QString addr2, QString country, QString city, QString state, QString zip)
    : JMDataObj(id)
    , m_clubName(clubName)
    , m_coachName(coachName)
    , m_address1(addr1)
    , m_address2(addr2)
    , m_country(country)
    , m_city(city)
    , m_state(state)
    , m_zip(zip)
{
}

/*
 * Copy Constructor
 */
Club::Club(const Club &src)
    : JMDataObj(src)
{
    m_clubName = src.clubName();
    m_coachName = src.coachName();
    m_address1 = src.address1();
    m_address2 = src.address2();
    m_country = src.country();
    m_city = src.city();
    m_state = src.state();
    m_zip = src.zip();

    m_competitors.append(src.competitors());
}

const QList<Competitor *> Club::competitors() const
{
    return m_competitors;
}

void Club::addCompetitor(Competitor *competitor)
{
    // Validate
    competitor->setClubId(id());
    m_competitors.append(competitor);
}

void Club::read(const QJsonObject &json)
{
    JMDataObj::read(json);
    m_clubName = json["clubname"].toString();
    m_coachName = json["coachname"].toString();
    m_address1 = json["address1"].toString();
    m_address2 = json["address2"].toString();
    m_country = json["country"].toString();
    m_city = json["city"].toString();
    m_state = json["state"].toString();
    m_zip = json["zip"].toString();
}

void Club::read(const QJsonObject &json, const QList<Competitor *> competitors)
{
    read(json);

    // Now add competitors
    foreach (Competitor *competitor, competitors)
    {
        if(competitor->clubId() == id())
            m_competitors.append(competitor);
    }
}

void Club::write(QJsonObject &json) const
{
    JMDataObj::write(json);
    json["clubname"] = m_clubName;
    json["coachname"] = m_coachName;
    json["address1"] = m_address1;
    json["address2"] = m_address2;
    json["country"] = m_country;
    json["city"] = m_city;
    json["state"] = m_state;
    json["zip"] = m_zip;

    // Write out Competitors?
}
