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
   return MAX_BRACKET_ITEMS;
}

QVariant BracketTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
    {
        if(role == Qt::DisplayRole)
        {
            return QVariant(section);
        }
//        return QVariant();
    }

    if(role == Qt::DisplayRole)
    {

        switch(section)
        {
            case Name:
                return QVariant("Name");

            case Gender:
                return QVariant("Gender");

            case Type://1:
                return QVariant("Type");

            case MinAge://2:
                return QVariant("Min Age");

            case MaxAge://3:
                return QVariant("Max Age");

           case MaxWeight://4:
                return QVariant("Max Weight");

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
                case Name: // Name
                    return QVariant(selectedBracket->name());
                break;

                case Gender:
                    return QVariant(genderToString(selectedBracket->gender()));
                    break;

                case Type: // Type
                    switch(selectedBracket->weightType())
                    {
                        case Bracket::IJF:
                            return QVariant("IJF");

                        case Bracket::LightMediumHeavy:
                            return QVariant("Light/Med/Hvy");

                        default:
                            return QVariant("Unknown Type");
                    }

                break;

                case MinAge: // Min Age
                    return QVariant(selectedBracket->minAge());
                break;

                case MaxAge: // Max Age
                    return QVariant(selectedBracket->maxAge());
                break;

                case MaxWeight: // Max Weight
                    return QVariant(selectedBracket->maxWeight());
                break;

                default:
                    return QVariant("Unknown");
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

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
//    int col = index.column();
//    if(col == 0)
    {
        flags |= Qt::ItemIsEditable;
    }

    return flags;
}

bool BracketTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    bool updated = true;
    const QList<Bracket *> *brackets = JMApp()->bracketController()->brackets();
    Bracket *bracket = brackets->at(index.row());

    switch(index.column())
    {
        case Name: // First Name
            bracket->setName(value.toString());
        break;

        case Gender:
            bracket->setGender(genderFromString(value.toString()));
            break;

        case Type: // Weight Type
        {
            int t = value.toInt();
            if(t == 0)
                bracket->setWeightType(Bracket::IJF);
            else if(t == 1)
                bracket->setWeightType(Bracket::LightMediumHeavy);
            break;
        }

        case MinAge: // Min Age
            bracket->setMinAge(value.toInt());
            break;

        case MaxAge: // Max Age
            bracket->setMaxAge(value.toInt());
            break;

        case MaxWeight: // Max Weight
            bracket->setMaxWeight(value.toDouble());
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
