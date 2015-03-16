#include "BracketTypeItemDelegate.h"

#include "Bracket.h"
#include "BracketTableModel.h"

#include <QComboBox>
#include <QDebug>

BracketTypeItemDelegate::BracketTypeItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{

}

BracketTypeItemDelegate::~BracketTypeItemDelegate()
{

}



QWidget *BracketTypeItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget *widget = 0;
    switch(index.column())
    {
        case bracket::Gender:
        case bracket::Type:
            widget =  new QComboBox(parent);
            break;

        default:
           widget = QStyledItemDelegate::createEditor(parent, option, index);
    }


    return widget;
}

void BracketTypeItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch(index.column())
    {
        case bracket::Gender:
        {
            QComboBox *combo = dynamic_cast<QComboBox *>(editor);
            if(combo)
            {
                combo->addItem("Male");
                combo->addItem("Female");

                // Need to select the right one.
                QVariant var = index.model()->data(index);
                if(genderFromString(var.toString()) == JM::Male)
                    combo->setCurrentIndex(0);
                else
                    combo->setCurrentIndex(1);
            }
            break;
        }
        case bracket::Type:
        {
            QComboBox *combo = dynamic_cast<QComboBox *>(editor);
            if(combo)
            {
                combo->addItem("Light");
                combo->addItem("Medium");
                combo->addItem("Heavy");
                combo->addItem("Super Heavy");
                combo->addItem("IFJ");

                // Need to select the right one.
                QVariant var = index.model()->data(index);
                combo->setCurrentIndex(Bracket::weightTypeFromStr(var.toString()));
            }
            break;
        }

        default:
            QStyledItemDelegate::setEditorData(editor, index);
    }
}

void BracketTypeItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch(index.column())
    {
        case bracket::Gender:
        {
            QComboBox *combo = dynamic_cast<QComboBox *>(editor);
            if(combo)
            {
                model->setData(index, QVariant(combo->currentText()));
            }
            break;
        }
        case bracket::Type:
        {
            QComboBox *combo = dynamic_cast<QComboBox *>(editor);
            if(combo)
            {
                model->setData(index, QVariant(combo->currentIndex()));
            }
            break;
        }

        default:
            QStyledItemDelegate::setModelData(editor, model, index);
    }

    if(index.column() == bracket::MatNum)
    {
        emit matNumberChanged();
    }
}
