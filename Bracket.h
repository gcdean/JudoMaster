#ifndef BRACKET_H
#define BRACKET_H

#include "JMDataObj.h"
#include "JMUtil.h"


#include <QJsonObject>
#include <QList>
#include <QString>

class Competitor;

void writeBracketHeader(QTextStream &stream);
void writeBracketCompetitorHeader(QTextStream &stream);
void writeBracketPlaceHeader(QTextStream &stream);

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

    void read(const QJsonObject &json ) override;
    void read(const QJsonObject& json, const QList<Competitor *> competitors);

    void write(QJsonObject& json) const override;
    void write(QTextStream &stream) const override;
    void writeCompetitors(QTextStream &stream) const;
    void writePlaces(QTextStream &stream) const;

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
    int time() const {return m_time;}
    void setTime(int time) {m_time = time;}
    void setMaxWeight(double maxWeight) {m_maxWeight = maxWeight;}
    double maxWeight() const {return m_maxWeight;}
    void setChokesAllowed(bool allowed) {m_chokesAllowed = allowed;}
    bool chokesAllowed() const {return m_chokesAllowed;}
    void setArmbarsAllowed(bool allowed) {m_armbarsAllowed = allowed;}
    bool armbarsAllowed() const {return m_armbarsAllowed;}
    void setMatNumber(int number) {m_matNumber = number;}
    int matNumber() const {return m_matNumber;}
    void setFirstPlace(const int firstPlace) {m_firstPlace = firstPlace;}
    int firstPlace() const {return m_firstPlace;}
    void setSecondPlace(const int place) {m_secondPlace = place;}
    int secondPlace() const{return m_secondPlace;}
    void setThirdPlace1(const int place) {m_thirdPlace_1 = place;}
    int thirdPlace1() const {return m_thirdPlace_1;}
    void setThirdPlace2(const int place) {m_thirdPlace_2 = place;}
    int thirdPlace2() const {return m_thirdPlace_2;}

    const QList< Competitor *> competitors() const;
    bool addCompetitor(Competitor *competitor, int location = -1);
    void removeCompetitor(int index);
    void moveCompetitor(int srcRow, int destRow);


    static QString weightTypeToStr(Bracket::WeightType type);
    static Bracket::WeightType weightTypeFromStr(QString typeStr);

private:
    QString m_name;
    JM::Gender m_gender;
    WeightType m_weightType;

    int m_minAge;
    int m_maxAge;
    int m_time;
    bool m_chokesAllowed;
    bool m_armbarsAllowed;
    int m_matNumber;
    int m_firstPlace;
    int m_secondPlace;
    int m_thirdPlace_1;
    int m_thirdPlace_2;

    double m_maxWeight;

    QList<Competitor *> m_competitors;
};

namespace bracket
{
    QString weightTypeToStr(Bracket::WeightType type);
    Bracket::WeightType weightTypeFromStr(QString typeStr);
}

#endif // BRACKET_H
