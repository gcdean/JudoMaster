#include "ClubListModel.h"



#include "commands/MergeClubsCommand.h"
#include "ClubController.h"
#include "JudoMasterApplication.h"

#include <QDebug>
#include <QMimeData>

ClubListModel::ClubListModel(QObject *parent) :
    QAbstractListModel(parent)
{
    connect(JMApp()->clubController(), &ClubController::addedDataObj, this, &ClubListModel::clubAdded);
    connect(JMApp()->clubController(), &ClubController::removedDataObj, this, &ClubListModel::clubRemoved);
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

        case Qt::UserRole:
            return QVariant(club->id());
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
    return Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}


void ClubListModel::clubAdded(JMDataObj *)
{
    // The club has already been added.
    int numClubs = JMApp()->clubController()->clubs()->size();
    beginInsertRows(QModelIndex(), numClubs - 1, numClubs);
    endInsertRows();
}

void ClubListModel::clubRemoved(JMDataObj *club)
{
    // Find the club that's being removed.
    // Find the index.
    int row = JMApp()->clubController()->indexOf(club->id());
    if(row >= 0)
    {
        beginRemoveRows(QModelIndex(), row, row);
        endRemoveRows();
    }

}

//QStringList ClubListModel::mimeTypes() const
//{
//    qDebug() << "ClubListModel::mimeTypes";
//    return QAbstractListModel::mimeTypes();
//}

//QMimeData *ClubListModel::mimeData(const QModelIndexList &indexes) const
//{
//    qDebug() << "ClubListModel::mimeData";
//    return QAbstractListModel::mimeData(indexes);
//}

bool ClubListModel::dropMimeData(const QMimeData *mimeData, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if(mimeData->hasFormat("application/x-qabstractitemmodeldatalist"))
    {
        QByteArray encoded = mimeData->data("application/x-qabstractitemmodeldatalist");
        QDataStream stream(&encoded, QIODevice::ReadOnly);

        int destRow = parent.row();
        while (!stream.atEnd())
        {
            int srcRow, srcCol;
            QMap<int,  QVariant> roleDataMap;
            stream >> srcRow >> srcCol >> roleDataMap;
            qDebug() << "Dropping " << srcRow << " Onto " << parent.row();

            QModelIndex srcIndex = index(srcRow);
            QModelIndex destIndex = index(destRow);

            int srcClubId = data(srcIndex, Qt::UserRole).toInt();
            int destClubId = data(destIndex, Qt::UserRole).toInt();

            Club *srcClub = dynamic_cast<Club *>(JMApp()->clubController()->find(srcClubId));
            Club *destClub = dynamic_cast<Club *>(JMApp()->clubController()->find(destClubId));

            MergeClubsCommand mergeCmd(srcClub, destClub);
            mergeCmd.run();
        }
    }

    return QAbstractListModel::dropMimeData(mimeData, action, row, column, parent);
}

Qt::DropActions ClubListModel::supportedDropActions() const
{
    return Qt::MoveAction;
//    return QAbstractListModel::supportedDropActions();
}

Qt::DropActions ClubListModel::supportedDragActions() const
{
    return Qt::MoveAction;
//    return QAbstractListModel::supportedDragActions();
}
