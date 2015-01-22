#include "BracketTableModel.h"

#include "Bracket.h"
#include "BracketController.h"
#include "JMDataObj.h"
#include "JudoMasterApplication.h"

#include <QDebug>

BracketTableModel::BracketTableModel(QObject *parent) :
    QAbstractTableModel(parent)
{
//    connect(JMApp()->bracketController(), &BracketController::add, this, &BracketTableModel::addBracket);
    connect(JMApp()->bracketController(), &BracketController::addedDataObj, this, &BracketTableModel::addTest);
}

int BracketTableModel::rowCount(const QModelIndex &parent) const
{
    qDebug() << "BracketTableModel - Returning " << JMApp()->bracketController()->size() << " Rows";
    return JMApp()->bracketController()->size();
}

int BracketTableModel::columnCount(const QModelIndex &parent) const
{
   return 5;
}

QVariant BracketTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Vertical)
        return QVariant();

    if(role == Qt::DisplayRole)
    {
        switch(section)
        {
            case 0:
                return QVariant("Name");

            case 1:
                return QVariant("Type");

            case 2:
                return QVariant("Min Age");

            case 3:
                return QVariant("Max Age");

           case 4:
                return QVariant("Max Weight");

           default:
            return QVariant();
        }
    }
    return QVariant();
}

QVariant BracketTableModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::DisplayRole)
    {
        const QList<Bracket *> *brackets = JMApp()->bracketController()->brackets();
        const Bracket *selectedBracket = brackets->at(index.row());

        int col = index.column();
        switch(col)
        {
            case 0: // Name
                return QVariant(selectedBracket->name());
            break;

            case 1: // Type
                switch(selectedBracket->type())
                {
                    case Bracket::IJF:
                        return QVariant("IJF");

                    case Bracket::LightMediumHeavy:
                        return QVariant("Light/Med/Hvy");

                    default:
                        return QVariant("Unknown Type");
                }

            break;

            case 2: // Min Age
                return QVariant(selectedBracket->minAge());
            break;

            case 3: // Max Age
                return QVariant(selectedBracket->maxAge());
            break;

            case 4: // Max Weight
                return QVariant(selectedBracket->maxWeight());
            break;

            default:
                return QVariant("Unknown");
        }
    }
    return QVariant();
}

Qt::ItemFlags BracketTableModel::flags(const QModelIndex &index) const
{

    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
//    int col = index.column();
//    if(col == 0 || col == 1)
//    {
//        flags |= Qt::ItemIsEditable;
//    }

    return flags;
}

bool BracketTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    return false;
}

void BracketTableModel::addBracket(Bracket *bracket)
{
    int numBrackets = JMApp()->bracketController()->size() - 1;
    beginInsertRows(QModelIndex(), numBrackets, numBrackets);
    endInsertRows();
}

void BracketTableModel::addTest(JMDataObj *obj)
{

}
