#include "CompetitorEditor.h"
#include "ui_CompetitorEditor.h"

#include "Bracket.h"
#include "Club.h"
#include "Competitor.h"
#include "JudoMasterApplication.h"

#include <QList>

CompetitorEditor::CompetitorEditor(Competitor *competitor, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CompetitorEditor)
  , m_competitor(competitor)
{
    ui->setupUi(this);

    ui->firstNameEdit->setText(m_competitor->firstName());
    ui->lastNameEdit->setText(m_competitor->lastName());
    ui->age->setValue(m_competitor->age());
    ui->weight->setValue(m_competitor->weight());
    ui->numDivs->setValue(m_competitor->numBrackets());

    // Fill in the Rank.
    ui->rankCombo->addItem(QIcon(":/images/white.png"), "White");
    ui->rankCombo->addItem(QIcon(":/images/yellow.png"), "Yellow");
    ui->rankCombo->addItem(QIcon(":/images/orange.png"), "Orange");
    ui->rankCombo->addItem(QIcon(":/images/green.png"), "Green");
    ui->rankCombo->addItem(QIcon(":/images/blue.png"), "Blue");
    ui->rankCombo->addItem(QIcon(":/images/purple.png"), "Purple");
    ui->rankCombo->addItem(QIcon(":/images/brown.png"), "Brown");
    ui->rankCombo->addItem(QIcon(":/images/black.png"), "Black");
    ui->rankCombo->setCurrentIndex(competitor->rank());

    // Fill in the Club combo
    int index = 0;
    foreach(Club *club, *JMApp()->clubController()->clubs())
    {
        ui->clubCombo->addItem(club->clubName(), QVariant(club->id()));
        if(club->id() == competitor->clubId())
            ui->clubCombo->setCurrentIndex(index);
        index++;
    }

    // Gender
    ui->genderCombo->addItem("Female");
    ui->genderCombo->addItem("Male");
    ui->genderCombo->setCurrentIndex(competitor->gender());

    // Notes
    ui->notes->setText(competitor->notes());

    // Fill in the brackets.
    const QList<Bracket *> brackets = JMApp()->bracketController()->competitorBrackets(competitor->id());
    foreach(Bracket *bracket, brackets)
    {
        ui->bracketList->addItem(QString("%1 %2 %3").arg(bracket->name()).arg(Bracket::weightTypeToStr(bracket->weightType())).arg(genderToString(bracket->gender())));
    }

}

CompetitorEditor::~CompetitorEditor()
{
    delete ui;
}


void CompetitorEditor::accept()
{
    m_competitor->setFirstName(ui->firstNameEdit->text());
    m_competitor->setLastName(ui->lastNameEdit->text());
    m_competitor->setAge(ui->age->value());
    m_competitor->setWeight(ui->weight->value());
    m_competitor->setNumBrackets(ui->numDivs->value());
    m_competitor->setRank(rankFromString(ui->rankCombo->currentText()));
    m_competitor->setGender(genderFromString(ui->genderCombo->currentText()));
    m_competitor->setClubId(ui->clubCombo->currentData().toInt());
    m_competitor->setNotes(ui->notes->toPlainText());

    QDialog::accept();
}
