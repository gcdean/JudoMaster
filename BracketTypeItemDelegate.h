#ifndef BRACKETTYPEITEMDELEGATE_H
#define BRACKETTYPEITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class BracketTypeItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    BracketTypeItemDelegate(QObject *parent = 0);
    ~BracketTypeItemDelegate();

    // QAbstractItemDelegate interface
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

signals:
    void matNumberChanged() const;
};

#endif // BRACKETTYPEITEMDELEGATE_H
