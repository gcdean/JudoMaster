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

    const QString USJAStr("USJA");
    const QString USJFStr("USJF");
    const QString USJIStr("USJI");
    const QString OtherStr("Other");
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
//            return QColor(Qt::yellow);
            break;

        case Orange:
              return QColor(234, 134, 16);
//            return QColor(Qt::darkYellow);
            break;

        case Green:
            return QColor(51, 119, 42);
//            return QColor(Qt::green);
            break;

        case Blue:
            return QColor(Qt::blue);
            break;

        case Purple:
            return QColor(194, 56,215);
//            return QColor(Qt::magenta);
            break;

        case Brown:
            return QColor(116, 19, 35);
//            return QColor(Qt::darkRed);
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


QString judoAssocToString(const JudoAssociation assoc)
{
    switch(assoc)
    {
        case USJA:
            return USJAStr;
        case USJF:
            return USJFStr;
        case USJI:
            return USJIStr;
        default:
            return OtherStr;
    }
}


JudoAssociation judoAssocFromString(const QString assoc)
{
    if(assoc.compare(USJAStr, Qt::CaseInsensitive) == 0)
    {
        return USJA;
    }
    else if (assoc.compare(USJFStr, Qt::CaseInsensitive) == 0)
    {
        return USJF;
    }
    else if (assoc.compare(USJIStr, Qt::CaseInsensitive) == 0)
    {
        return USJI;
    }
    else
    {
        return Other;
    }
}
