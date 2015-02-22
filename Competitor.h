#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <QChar>
#include <QJsonObject>
#include <QObject>
#include <QString>

#include "JMDataObj.h"
#include "JMUtil.h"

class Competitor : public JMDataObj
{

public:

    explicit Competitor(int id, QString firstName, QString lastName, JM::Gender gender, int age , double weight, JM::Rank rank, int clubId);
    Competitor(const Competitor& src);
    Competitor();
//    Competitor(QJsonObject &json);

//    int id() const {return m_id;}
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

    virtual void read(const QJsonObject& json);
\
    void write(QJsonObject& json) const override;
//    void read(QJsonObject& json) override;
//    void write(QJsonObject& json) const override;

private:
//    int m_id;
    QString m_firstName;
    QString m_lastName;
    JM::Gender m_gender;
    int m_age;
    double m_weight;
    JM::Rank m_rank;
    int m_clubId;
};


#endif // COMPETITOR_H
