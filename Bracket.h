#ifndef BRACKET_H
#define BRACKET_H

#include "JMDataObj.h"
#include "JMUtil.h"


#include <QJsonObject>
#include <QList>
#include <QString>

class Competitor;

/**
 * @brief The Bracket class
 *
 * Brackets are either age and weight based or simply weight based. Additionally,
 * weight brackets can be absolule weight or a weight type (Light, Medium, Heavy)
 */
class Bracket : public JMDataObj
{
public:
    Bracket();
    Bracket(int id);
    Bracket(const Bracket& src);
    Bracket(const QJsonObject &json);

    enum WeightType
    {
        Light,
        Medium,
        Heavy,
        SuperHeavy,
        IJF
    };

    void read(const QJsonObject& json, const QList<Competitor *> competitors);

    void write(QJsonObject& json) const override;

    void setName(QString name) {m_name = name;}
    QString name() const {return m_name;}
    void setGender(JM::Gender gender);
    JM::Gender gender() const;
    void setWeightType(Bracket::WeightType weightType) {m_weightType = weightType;}
    Bracket::WeightType weightType() const {return m_weightType;}
    void setMinAge(int minAge) {m_minAge = minAge;}
    int minAge() const {return m_minAge;}
    void setMaxAge(int maxAge) {m_maxAge = maxAge;}
    int maxAge() const {return m_maxAge;}
    void setMaxWeight(double maxWeight) {m_maxWeight = maxWeight;}
    double maxWeight() const {return m_maxWeight;}
    void setChokesAllowed(bool allowed) {m_chokesAllowed = allowed;}
    bool chokesAllowed() const {return m_chokesAllowed;}
    void setArmbarsAllowed(bool allowed) {m_armbarsAllowed = allowed;}
    bool armbarsAllowed() const {return m_armbarsAllowed;}
    void setMatNumber(int number) {m_matNumber = number;}
    int matNumber() const {return m_matNumber;}
    void setFirstPlace(const QString& firstPlace) {m_firstPlace = firstPlace;}
    QString firstPlace() const {return m_firstPlace;}
    void setSecondPlace(const QString& place) {m_secondPlace = place;}
    QString secondPlace() const{return m_secondPlace;}
    void setThirdPlace1(const QString& place) {m_thirdPlace_1 = place;}
    QString thirdPlace1() const {return m_thirdPlace_1;}
    void setThirdPlace2(const QString& place) {m_thirdPlace_2 = place;}
    QString thirdPlace2() const {return m_thirdPlace_2;}

    const QList< Competitor *> competitors() const;
    bool addCompetitor(Competitor *competitor, int location = -1);
    void moveCompetitor(int srcRow, int destRow);

private:
    QString m_name;
    JM::Gender m_gender;
    WeightType m_weightType;

    int m_minAge;
    int m_maxAge;
    bool m_chokesAllowed;
    bool m_armbarsAllowed;
    int m_matNumber;
    QString m_firstPlace;
    QString m_secondPlace;
    QString m_thirdPlace_1;
    QString m_thirdPlace_2;

    double m_maxWeight;

    QList<Competitor *> m_competitors;
};

namespace bracket
{
    QString weightTypeToStr(Bracket::WeightType type);
    Bracket::WeightType weightTypeFromStr(QString typeStr);
}

#endif // BRACKET_H
