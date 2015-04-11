#include "JMUtil.h"

namespace
{
    const QString WhiteStr("White");
    const QString YellowStr("Yellow");
    const QString OrangeStr("Orange");
    const QString GreenStr("Green");
    const QString BlueStr("Blue");
    const QString PurpleStr("Purple");
    const QString BrownStr("Brown");
    const QString BlackStr("Black");
    const QString UnknownStr("Unknown");

    const QString FemaleStr("Female");
    const QString MaleStr("Male");
    const QString NotApplicableStr("Not Applicable");

}

using namespace JM;

QString rankToString(Rank rank)
{
    switch(rank)
    {
        case White:
            return WhiteStr;
        break;

        case Yellow:
            return YellowStr;
            break;

        case Orange:
            return OrangeStr;
            break;

        case Green:
            return GreenStr;
            break;

        case Blue:
            return BlueStr;
            break;

        case Purple:
            return PurpleStr;
            break;

        case Brown:
            return BrownStr;
            break;

        case Black:
            return BlackStr;
            break;

        case Unknown:
            return UnknownStr;
            break;

    }

    return QString("Unknown");
}

Rank rankFromString(QString rankStr)
{
    Rank rank(Unknown);

    if(rankStr.compare(WhiteStr, Qt::CaseInsensitive) == 0 )
        rank = White;
    else if(rankStr.compare(YellowStr, Qt::CaseInsensitive) == 0 )
        rank = Yellow;
    else if (rankStr.compare(OrangeStr, Qt::CaseInsensitive) == 0 )
        rank = Orange;
    else if(rankStr.compare(GreenStr, Qt::CaseInsensitive) == 0 )
        rank = Green;
    else if(rankStr.compare(BlueStr, Qt::CaseInsensitive) == 0 )
        rank = Blue;
    else if(rankStr.compare(PurpleStr, Qt::CaseInsensitive) == 0 )
        rank = Purple;
    else if(rankStr.compare(BrownStr, Qt::CaseInsensitive) == 0 )
        rank = Brown;
    else if(rankStr.compare(BlackStr, Qt::CaseInsensitive) == 0 )
        rank = Black;
    else
        rank = Unknown;

    return rank;
}

QColor rankToColor(Rank rank)
{
    switch(rank)
    {
        case White:
            return QColor(Qt::white);
        break;

        case Yellow:
            return QColor(255, 252, 0);
            break;

        case Orange:
              return QColor(234, 134, 16);
            break;

        case Green:
            return QColor(51, 119, 42);
            break;

        case Blue:
            return QColor(Qt::blue);
            break;

        case Purple:
            return QColor(194, 56,215);
            break;

        case Brown:
            return QColor(116, 19, 35);
            break;

        case Black:
            return QColor(Qt::black);
            break;

       case Unknown:
            return QColor(Qt::darkRed);
            break;
    }

    return QColor(Qt::red); // Unknown
}

QString genderToString(Gender gender)
{
    switch(gender)
    {
        case Female:
            return FemaleStr;

        case Male:
            return MaleStr;
    }

    return NotApplicableStr;
}

Gender genderFromString(QString genderStr)
{
    if(genderStr.compare(FemaleStr, Qt::CaseInsensitive) == 0 )
        return Female;
    else if(genderStr.compare(MaleStr, Qt::CaseInsensitive) == 0 )
        return Male;

    return NotApplicable;
}


QString prepareStringForCSV(QString str)
{
    return str.replace(QString(","), QString(";"));
}
