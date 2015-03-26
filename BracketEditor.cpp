#include "BracketEditor.h"
#include "ui_BracketEditor.h"

#include "Bracket.h"
#include "Competitor.h"
#include "JMUtil.h"
#include "JudoMasterApplication.h"
#include "MatchItemDelegate.h"
#include "MatchTableModel.h"

#include <QDebug>

BracketEditor::BracketEditor(Bracket *bracket, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BracketEditor)
    , m_bracket(bracket)
{
    ui->setupUi(this);

    ui->bracketNameLbl->setText(bracket->name());
    ui->typeLbl->setText(Bracket::weightTypeToStr(bracket->weightType()));
    ui->genderLbl->setText(genderToString(bracket->gender()));

    ui->firstPlaceCombo->addItem(QString("<None>"), QVariant(-1));
    ui->secondPlaceCombo->addItem(QString("<None>"), QVariant(-1));
    ui->thirdPlace1Combo->addItem(QString("<None>"), QVariant(-1));
    int index = 1;
    foreach(Competitor *competitor, bracket->competitors())
    {
        ui->firstPlaceCombo->addItem(QString("%1, %2").arg(competitor->lastName()).arg(competitor->firstName()), QVariant(competitor->id()));
        if(bracket->firstPlace() == competitor->id())
            ui->firstPlaceCombo->setCurrentIndex(index);
        ui->secondPlaceCombo->addItem(QString("%1, %2").arg(competitor->lastName()).arg(competitor->firstName()), QVariant(competitor->id()));
        if(bracket->secondPlace() == competitor->id())
            ui->secondPlaceCombo->setCurrentIndex(index);
        ui->thirdPlace1Combo->addItem(QString("%1, %2").arg(competitor->lastName()).arg(competitor->firstName()), QVariant(competitor->id()));
        if(bracket->thirdPlace1() == competitor->id())
            ui->thirdPlace1Combo->setCurrentIndex(index);
        index++;
    }

    m_matchTableModel = new MatchTableModel(ui->matchesTable);
    m_matchTableModel->setBracketId(bracket->id());
    ui->matchesTable->setModel(m_matchTableModel);
    ui->matchesTable->setItemDelegate(new MatchItemDelegate(m_bracket, ui->matchesTable));

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(ui->addMatchBtn, &QPushButton::clicked, this, &BracketEditor::addMatch);
    connect(ui->removeMatchBtn, &QPushButton::clicked, this, &BracketEditor::removeMatch);
}

BracketEditor::~BracketEditor()
{
    delete ui;
}


void BracketEditor::accept()
{
    // Let's get the place competitors.

    m_bracket->setFirstPlace(ui->firstPlaceCombo->currentData().toInt());
    m_bracket->setSecondPlace(ui->secondPlaceCombo->currentData().toInt());
    m_bracket->setThirdPlace1(ui->thirdPlace1Combo->currentData().toInt());
    QDialog::accept();
}

void BracketEditor::addMatch()
{
    qDebug() << "Add New Match";
    JMApp()->matchController()->add(m_bracket->id());
}

void BracketEditor::removeMatch()
{
    qDebug() << "Remove Selected Match.";
}
