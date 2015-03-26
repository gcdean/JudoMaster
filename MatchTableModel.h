#ifndef MATCHTABLEMODEL_H
#define MATCHTABLEMODEL_H

#include <QAbstractTableModel>

class JMDataObj;

class MatchTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum MatchData
    {
        firstCompetitor,
        secondCompetitor,
        winner,
        score,
        notes,
        MAX_COLUMNS
    };

    explicit MatchTableModel(QObject *parent = 0);

    void setBracketId(int id);
    int bracketId();

signals:

public slots:


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private slots:
    void bracketAdded(JMDataObj *data);

private:
    int m_bracketId;

};

#endif // MATCHTABLEMODEL_H
