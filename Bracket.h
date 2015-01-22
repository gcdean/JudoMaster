#ifndef BRACKET_H
#define BRACKET_H

#include "JMDataObj.h"

#include <QJsonObject>
#include <QString>

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

    /**
     * @brief The BracketType enum
     */
    enum BracketType
    {
        Age,
        Weight
    };

    enum WeightType
    {
        IJF,
        LightMediumHeavy
    };

    void read(const QJsonObject& json) override;
    void write(QJsonObject& json) const override;

    void setName(QString name) {m_name = name;}
    QString name() const {return m_name;}
    void setType(Bracket::BracketType type) {m_bracketType = type;}
    Bracket::BracketType type() const {return m_bracketType;}
    void setWeightType(Bracket::WeightType weightType) {m_weightType = weightType;}
    Bracket::WeightType weightType() const {return m_weightType;}
    void setMinAge(int minAge) {m_minAge = minAge;}
    int minAge() const {return m_minAge;}
    void setMaxAge(int maxAge) {m_maxAge = maxAge;}
    int maxAge() const {return m_maxAge;}
    void setMaxWeight(double maxWeight) {m_maxWeight = maxWeight;}
    double maxWeight() const {return m_maxWeight;}

private:
    QString m_name;
    BracketType m_bracketType;
    WeightType m_weightType;

    int m_minAge;
    int m_maxAge;

    double m_maxWeight;
};

#endif // BRACKET_H
