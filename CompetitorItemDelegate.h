#ifndef COMPETITORITEMDELEGATE_H
#define COMPETITORITEMDELEGATE_H

#include <QStyledItemDelegate>

class QComboBox;

class CompetitorItemDelegate : public QStyledItemDelegate
{
public:
    CompetitorItemDelegate();
    ~CompetitorItemDelegate();


    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void destroyEditor(QWidget *editor, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private:    // Methods
    QComboBox* genderCombo();

private:    // Data Members
    QComboBox* m_genderCombo;
    QComboBox* m_rankCombo;

    // QAbstractItemDelegate interface
public:
};

#endif // COMPETITORITEMDELEGATE_H
