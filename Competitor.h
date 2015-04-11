#ifndef COMPETITOR_H
#define COMPETITOR_H

#include <QChar>
#include <QJsonObject>
#include <QObject>
#include <QString>

#include "JMDataObj.h"
#include "JMUtil.h"

namespace competitor
{
    enum CompetitorProperties
    {
        FirstName,
        LastName,
        Gender,
        Age,
        Weight,
        Rank,
        NumDivs,
        Notes,
        MAX_COMPETITOR_ITEM
    };

}

void writeCompetitorHeader(QTextStream &stream);

class Competitor : public JMDataObj
{

public:

    explicit Competitor(int id, QString firstName, QString lastName, JM::Gender gender, int age , double weight, JM::Rank rank, int clubId);
    Competitor(const Competitor& src);
    Competitor();

    QString firstName() const {return m_firstName;}
    void setFirstName(QString name) {m_firstName = name;}
    QString lastName() const {return m_lastName;}
    void setLastName(QString name) {m_lastName = name;}
    JM::Gender gender() const {return m_gender;}
    void setGender(JM::Gender gender) {m_gender = gender;}
    int age() const {return m_age;}
    void setAge(int age) {m_age = age;}
    double weight() const {return m_weight;}
    void setWeight(double weight) {m_weight = weight;}
    JM::Rank rank() const {return m_rank;}
    void setRank(JM::Rank rank) {m_rank = rank;}
    int clubId() const {return m_clubId;}
    void setClubId(int id) {m_clubId = id;}
    int numBrackets() const {return m_numBrackets;}
    void setNumBrackets(int num) {m_numBrackets = num;}
    QString notes() const { return m_notes;}
    void setNotes(QString notes) {m_notes = notes;}

    virtual void read(const QJsonObject& json);

    void write(QJsonObject& json) const override;
    void write(QTextStream &stream) const override;

private:
    QString m_firstName;
    QString m_lastName;
    JM::Gender m_gender;
    int m_age;
    double m_weight;
    JM::Rank m_rank;
    int m_numBrackets;
    QString m_notes;
    int m_clubId;
};


#endif // COMPETITOR_H
