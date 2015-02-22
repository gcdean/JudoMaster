#include "CompetitorItemDelegate.h"

#include "Competitor.h"

#include <QComboBox>

CompetitorItemDelegate::CompetitorItemDelegate()
    : m_genderCombo(0)
    , m_rankCombo(0)
{
    m_genderCombo = new QComboBox();
    m_genderCombo->addItem("Male");
    m_genderCombo->addItem("Female");

    m_rankCombo = new QComboBox();
    m_rankCombo->addItem(QIcon(":/images/white.png"), "White");
    m_rankCombo->addItem(QIcon(":/images/yellow.png"), "Yellow");
    m_rankCombo->addItem(QIcon(":/images/orange.png"), "Orange");
    m_rankCombo->addItem(QIcon(":/images/green.png"), "Green");
    m_rankCombo->addItem(QIcon(":/images/blue.png"), "Blue");
    m_rankCombo->addItem(QIcon(":/images/purple.png"), "Purple");
    m_rankCombo->addItem(QIcon(":/images/brown.png"), "Brown");
    m_rankCombo->addItem(QIcon(":/images/black.png"), "Black");
}

CompetitorItemDelegate::~CompetitorItemDelegate()
{
    if(m_genderCombo)
        delete m_genderCombo;
    if(m_rankCombo)
        delete m_rankCombo;
}

QWidget *CompetitorItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    switch(index.column())
    {
        case competitor::Gender:
            m_genderCombo->setParent(parent);
            return m_genderCombo;
            break;

        case competitor::Rank:
            m_rankCombo->setParent(parent);
            return m_rankCombo;

    }

    return QStyledItemDelegate::createEditor(parent, option, index);
}

void CompetitorItemDelegate::destroyEditor(QWidget *editor, const QModelIndex &index) const
{

    switch(index.column())
    {
        case competitor::Gender:
        case competitor::Rank:
            return;
            break;
    }

    return QStyledItemDelegate::destroyEditor(editor, index);
}

void CompetitorItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    switch(index.column())
    {
        case competitor::Gender:
        {
            // Need to select the right one.
            QVariant var = index.model()->data(index);
            if(genderFromString(var.toString()) == JM::Male)
                m_genderCombo->setCurrentIndex(0);
            else
                m_genderCombo->setCurrentIndex(1);

            break;
        }
        case competitor::Rank:
        {
            QVariant var = index.model()->data(index);

            m_rankCombo->setCurrentIndex(rankFromString(var.toString()));

            break;
        }
    }

    return QStyledItemDelegate::setEditorData(editor, index);
}

void CompetitorItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    switch(index.column())
    {
        case competitor::Gender:
            model->setData(index, QVariant(m_genderCombo->currentText()));
            break;

        case competitor::Rank:
            model->setData(index, QVariant(m_rankCombo->currentText()));
            break;

        default:
           QStyledItemDelegate::setModelData(editor, model, index);
    }

    return;

}

QComboBox *CompetitorItemDelegate::genderCombo()
{
    if(!m_genderCombo)
    {
        m_genderCombo = new QComboBox();
        m_genderCombo->addItem("Male");
        m_genderCombo->addItem("Female");
    }

    return m_genderCombo;
}
