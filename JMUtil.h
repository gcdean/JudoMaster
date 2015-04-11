#ifndef JMUTIL_H
#define JMUTIL_H

#include <QColor>
#include <QObject>
#include <QString>

namespace JM
{

/**
 * @brief The Rank enum - Used for Competitor's rank
 */
enum Rank
{
    White,
    Yellow,
    Orange,
    Green,
    Blue,
    Purple,
    Brown,
    Black,
    Unknown
};


/**
 * @brief The Gender enum - Used for both competiors and brackets.
 */
enum Gender
{
    Female,
    Male,
    NotApplicable
};



}

Q_DECLARE_METATYPE(JM::Rank)
Q_DECLARE_METATYPE(JM::Gender)

QString rankToString(JM::Rank rank);
JM::Rank rankFromString(QString rankStr);
QColor rankToColor(JM::Rank rank);

QString genderToString(JM::Gender gender);
JM::Gender genderFromString(QString genderStr);

QString prepareStringForCSV(QString str);

#endif // JMUTIL_H
