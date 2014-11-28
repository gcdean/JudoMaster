#ifndef CLUB_H
#define CLUB_H

#include <QJsonObject>
#include <QList>
#include <QObject>
#include <QString>

#include "Competitor.h"

class Club
{
//    Q_OBJECT
//    Q_PROPERTY(int id READ id)
//    Q_PROPERTY(QString clubName READ clubName)
//    Q_PROPERTY(QString coachName READ coachName)
//    Q_PROPERTY(QString address1 READ address1)
//    Q_PROPERTY(QString address2 READ address2)
//    Q_PROPERTY(QString country READ country)
//    Q_PROPERTY(QString city READ city)
//    Q_PROPERTY(QString state READ state)
//    Q_PROPERTY(QString zip READ zip)

public:
    Club(){}
    explicit Club(int id, QString clubName, QString coachName, QString addr1 = QString(), QString addr2 = QString(), QString country = QString(), QString city = QString(), QString state = QString(), QString zip = QString());
    Club(const Club& src);

    int id() const {return m_id;}
    QString clubName() const {return m_clubName;}
    void setClubName(QString name) {m_clubName = name;}
    QString coachName() const {return m_coachName;}
    void setCoachName(QString name) {m_coachName = name;}
    QString address1() const {return m_address1;}
    void setAddress1(QString address1) {m_address1 = address1;}
    QString address2() const {return m_address2;}
    void setAddress2(QString address2) {m_address2 = address2;}
    QString country() const {return m_country;}
    void setCountry(QString country) {m_country = country;}
    QString city() const {return m_city;}
    void setCity(QString city) {m_city = city;}
    QString state() const {return m_state;}
    void setState(QString state) {m_state = state;}
    QString zip() const {return m_zip;}
    void setZip(QString zip) {m_zip = zip;}

    const QList<Competitor> competitors() const;

    void addCompetitor(Competitor competitor);

    void read(QJsonObject &json);
    void write(QJsonObject &json) const;

private:
    int m_id;
    QString m_clubName;
    QString m_coachName;
    QString m_address1;
    QString m_address2;
    QString m_country;
    QString m_city;
    QString m_state;
    QString m_zip;

    QList<Competitor> m_competitors;
};

#endif // CLUB_H
