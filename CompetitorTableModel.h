#ifndef COMPETITORTABLEMODEL_H
#define COMPETITORTABLEMODEL_H

#include <QAbstractTableModel>

class Competitor;

class CompetitorTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit CompetitorTableModel(QObject *parent = 0);

    void setClubId(int id);

    // Overrides
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

signals:

public slots:
    void addCompetitor(Competitor *competitor);

private:
    int m_clubId;   // If the model is for competitors for a club
};

#endif // COMPETITORTABLEMODEL_H
