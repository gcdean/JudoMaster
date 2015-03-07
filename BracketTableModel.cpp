#include "BracketTableModel.h"

#include "Bracket.h"
#include "BracketController.h"
#include "JMDataObj.h"
#include "JudoMasterApplication.h"

#include <QDebug>

BracketTableModel::BracketTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    connect(JMApp()->bracketController(), &BracketController::addedDataObj, this, &BracketTableModel::addBracket);
}

int BracketTableModel::rowCount(const QModelIndex &parent) const
{
    return JMApp()->bracketController()->size();
}

int BracketTableModel::columnCount(const QModelIndex &parent) const
{
   return bracket::MAX_BRACKET_ITEMS;
}

QVariant BracketTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
    {
        if(role == Qt::DisplayRole)
        {
            qDebug() << "BracketTableModel::headerData() - Returning Vertical: " << section;
            return QVariant(section);
        }
        return QVariant();
    }

    if(role == Qt::DisplayRole)
    {

        switch(section)
        {
            case bracket::Name:
                return QVariant("Name");

            case bracket::Gender:
                return QVariant("Gender");

            case bracket::Type://1:
                return QVariant("Type");

            case bracket::MinAge://2:
                return QVariant("Min Age");

            case bracket::MaxAge://3:
                return QVariant("Max Age");

           case bracket::MaxWeight://4:
                return QVariant("Max Weight");

           case bracket::AllowChokes:
                return QVariant("Chokes");

            case bracket::AllowArmBars:
                return QVariant("Armbars");

            case bracket::MatNum:
                return QVariant("Mat");
           default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant BracketTableModel::data(const QModelIndex &index, int role) const
{
    const QList<Bracket *> *brackets = JMApp()->bracketController()->brackets();
    const Bracket *selectedBracket = brackets->at(index.row());
    switch(role)
    {
        case Qt::DisplayRole:
        {

            int col = index.column();
            switch(col)
            {
                case bracket::Name: // Name
                    return QVariant(selectedBracket->name());
                break;

                case bracket::Gender:
                    return QVariant(genderToString(selectedBracket->gender()));
                    break;

                case bracket::Type: // Type
                    return QVariant(bracket::weightTypeToStr(selectedBracket->weightType()));

                break;

                case bracket::MinAge: // Min Age
                    return QVariant(selectedBracket->minAge());
                break;

                case bracket::MaxAge: // Max Age
                    return QVariant(selectedBracket->maxAge());
                break;

                case bracket::MaxWeight: // Max Weight
                    return QVariant(selectedBracket->maxWeight());
                break;

                case bracket::AllowChokes:
                    return QVariant(selectedBracket->chokesAllowed());

                case bracket::AllowArmBars:
                    return QVariant(selectedBracket->armbarsAllowed());

                case bracket::MatNum:
                    return QVariant(selectedBracket->matNumber());
                default:
                    return QVariant("Unknown");
            }
        }
            break;

        case Qt::CheckStateRole:
            switch(index.column())
            {
                case bracket::AllowChokes:
                {
                    if(selectedBracket->chokesAllowed())
                        return Qt::Checked;
                    else
                        return Qt::Unchecked;

                }
                case bracket::AllowArmBars:
                {
                    if(selectedBracket->armbarsAllowed())
                        return Qt::Checked;
                    else
                        return Qt::Unchecked;
                }
            }

            break;

        case Qt::UserRole:
            return QVariant(selectedBracket->id());
            break;

    }
    return QVariant();
}

Qt::ItemFlags BracketTableModel::flags(const QModelIndex &index) const
{

    Qt::ItemFlags flags = QAbstractTableModel::flags(index);

//    flags |= Qt::ItemIsEnabled | Qt::ItemIsSelectable;

    switch (index.column())
    {
        case bracket::AllowChokes:
        case bracket::AllowArmBars:
            flags |= Qt::ItemIsUserCheckable;
        break;
        default:
        break;
    }

    flags |= Qt::ItemIsEditable;

    return flags;
}

bool BracketTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    bool updated = true;
    const QList<Bracket *> *brackets = JMApp()->bracketController()->brackets();
    Bracket *bracket = brackets->at(index.row());

    switch(index.column())
    {
        case bracket::Name: // First Name
            bracket->setName(value.toString());
        break;

        case bracket::Gender:
            bracket->setGender(genderFromString(value.toString()));
            break;

        case bracket::Type: // Weight Type
        {
            int t = value.toInt();
            bracket->setWeightType((Bracket::WeightType)t);
            break;
        }

        case bracket::MinAge: // Min Age
            bracket->setMinAge(value.toInt());
            break;

        case bracket::MaxAge: // Max Age
            bracket->setMaxAge(value.toInt());
            break;

        case bracket::MaxWeight: // Max Weight
            bracket->setMaxWeight(value.toDouble());
            break;

        case bracket::AllowChokes:
            bracket->setChokesAllowed(value.toBool());
            break;

        case bracket::AllowArmBars:
            bracket->setArmbarsAllowed(value.toBool());
            break;

        case bracket::MatNum:
            bracket->setMatNumber(value.toInt());
            break;

        default:
            updated = false;
    }

    if(updated)
    {
        emit dataChanged(index, index);
    }
    return updated;

}

void BracketTableModel::addBracket(JMDataObj *bracket)
{
    Q_UNUSED(bracket);
    qDebug() << "BracketTableModel::addBracket() Num Brackets: " << JMApp()->bracketController()->size();
    int numBrackets = JMApp()->bracketController()->size() - 1;
    beginInsertRows(QModelIndex(), numBrackets, numBrackets);
    endInsertRows();
}
