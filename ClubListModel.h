#ifndef CLUBLISTMODEL_H
#define CLUBLISTMODEL_H

#include "Club.h"

#include <QAbstractListModel>
#include <QVariant>

class ClubListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ClubListModel(QObject *parent = 0);

    Club* club(const QModelIndex &index);

    // Overrides
    int rowCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;


signals:

public slots:
    void clubAdded(JMDataObj *club);
    void clubRemoved(JMDataObj *club);


    // QAbstractItemModel interface
public:
//    virtual QStringList mimeTypes() const;
//    virtual QMimeData *mimeData(const QModelIndexList &indexes) const;
    virtual bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    virtual Qt::DropActions supportedDropActions() const;
    virtual Qt::DropActions supportedDragActions() const;
};

#endif // CLUBLISTMODEL_H
