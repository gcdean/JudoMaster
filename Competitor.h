#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <QChar>
#include <QJsonObject>
#include <QObject>
#include <QString>

#include "JMUtil.h"

class Competitor //: public QObject
{
//    Q_OBJECT

//    Q_PROPERTY(int id READ id)
//    Q_PROPERTY(QString firstName READ firstName)
//    Q_PROPERTY(QString lastName READ lastName)
//    Q_PROPERTY(QChar gender READ gender)
//    Q_PROPERTY(int age READ age)
//    Q_PROPERTY(double weight READ weight)
//    Q_PROPERTY(Rank rank READ rank )
//    Q_PROPERTY(int clubId READ clubId)

public:

    explicit Competitor(int id, QString firstName, QString lastName, JM::Gender gender, int age , double weight, JM::Rank rank, int clubId);
    Competitor(const Competitor& src);
    Competitor(QJsonObject &json);

    int id() const {return m_id;}
    QString firstName() const {return m_firstName;}
    void setFirstName(QString name) {m_firstName = name;}
    QString lastName() const {return m_lastName;}
    void setLastName(QString name) {m_lastName = name;}
    JM::Gender gender() const {return m_gender;}
    int age() const {return m_age;}
    double weight() const {return m_weight;}
    JM::Rank rank() const {return m_rank;}
    int clubId() const {return m_clubId;}
    void setClubId(int id) {m_clubId = id;}

    void read(QJsonObject& json);
    void write(QJsonObject& json) const;

private:
    int m_id;
    QString m_firstName;
    QString m_lastName;
    JM::Gender m_gender;
    int m_age;
    double m_weight;
    JM::Rank m_rank;
    int m_clubId;
};


#endif // COMPETITOR_H
