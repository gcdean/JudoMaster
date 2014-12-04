#ifndef BRACKET_H
#define BRACKET_H

#include <QJsonObject>
#include <QString>

/**
 * @brief The Bracket class
 *
 * Brackets are either age and weight based or simply weight based. Additionally,
 * weight brackets can be absolule weight or a weight type (Light, Medium, Heavy)
 */
class Bracket
{
public:
    Bracket();
    Bracket(QJsonObject jobj);

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
        Absolute,
        LightMediumHeavy
    };

    void read(QJsonObject& json);
    void write(QJsonObject& json) const;

private:
    int m_id;
    QString m_name;
    BracketType m_bracketType;
    WeightType m_weightType;

    int m_minAge;
    int m_maxAge;

    double m_maxWeight;
};

#endif // BRACKET_H
