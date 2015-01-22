#ifndef BRACKETTABLEMODEL_H
#define BRACKETTABLEMODEL_H

#include <QAbstractTableModel>

class Bracket;
class JMDataObj;

class BracketTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit BracketTableModel(QObject *parent = 0);

    // Overrides
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

signals:

public slots:
    void addBracket(Bracket *bracket);
    void addTest(JMDataObj *obj);

};

#endif // BRACKETTABLEMODEL_H
