#ifndef MATCHITEMDELEGATE_H
#define MATCHITEMDELEGATE_H

#include <QStyledItemDelegate>

class Bracket;

class MatchItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MatchItemDelegate(Bracket *bracket, QObject *parent = 0);

    // QAbstractItemDelegate interface
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

signals:

public slots:

private:
    Bracket *m_bracket;
};

#endif // MATCHITEMDELEGATE_H
