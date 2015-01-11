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

};

#endif // CLUBLISTMODEL_H
