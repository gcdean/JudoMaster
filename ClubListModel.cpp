#include "ClubListModel.h"
#include "ClubController.h"
#include "JudoMasterApplication.h"

ClubListModel::ClubListModel(QObject *parent) :
    QAbstractListModel(parent)
{
//    connect(JMApp()->clubController(), &ClubController::clubAdded, this, &ClubListModel::clubAdded);
    connect(JMApp()->clubController(), &ClubController::addedDataObj, this, &ClubListModel::clubAdded);
}

Club* ClubListModel::club(const QModelIndex &index)
{
    Club *c = JMApp()->clubController()->clubs()->at(index.row());
    return c;
}

int ClubListModel::rowCount(const QModelIndex &) const
{
    return (JMApp()->clubController()->clubs()->size());
}

QVariant ClubListModel::data(const QModelIndex &index, int role) const
{
    Club *club = JMApp()->clubController()->clubs()->at(index.row());

    switch(role)
    {
        case Qt::DisplayRole:
            return QVariant(club->clubName());
        break;

        default:
            return QVariant();
    }
}

QVariant ClubListModel::headerData(int , Qt::Orientation , int role) const
{
    switch(role)
    {
        case Qt::DisplayRole:
            return QVariant(QString("Club Name"));
    }

    return QVariant();
}

Qt::ItemFlags ClubListModel::flags(const QModelIndex &) const
{
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}


void ClubListModel::clubAdded(JMDataObj *)
{
    // The club has already been added.
    int numClubs = JMApp()->clubController()->clubs()->size();
    beginInsertRows(QModelIndex(), numClubs - 1, numClubs);
    endInsertRows();
}
