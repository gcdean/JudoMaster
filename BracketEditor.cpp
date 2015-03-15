#include "BracketEditor.h"
#include "ui_BracketEditor.h"

#include "Bracket.h"
#include "Competitor.h"
#include "JMUtil.h"

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
    ui->thirdPlace2Combo->addItem(QString("<None>"), QVariant(-1));
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
        ui->thirdPlace2Combo->addItem(QString("%1, %2").arg(competitor->lastName()).arg(competitor->firstName()), QVariant(competitor->id()));
        if(bracket->thirdPlace2() == competitor->id())
            ui->thirdPlace2Combo->setCurrentIndex(index);
        index++;
    }

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
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
    m_bracket->setThirdPlace2(ui->thirdPlace2Combo->currentData().toInt());
    QDialog::accept();
}
