#include "ClubEditor.h"
#include "ui_ClubEditor.h"

namespace
{
    QString states = "AL,AK,AZ,AR,CA,CO,CT,DE,FL,GA,HI,ID,IL,IN,IA,KS,KY,LA,ME,MD,MA,MI,MN,MS,MO,MT,NE,NV,NH,NJ,NM,NY,NC,ND,OH,OK,OR,PA,RI,SC,SD,TN,TX,UT,VT,VA,WA,WV,WI,WY";

    QString provinces = "AB,BC,MB,NB,NL,NS,NT,NU,ON,PE,QC,SK,YT";
}

ClubEditor::ClubEditor(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClubEditor)
    , m_club(0)
{
    ui->setupUi(this);

//    connect(ui->clubNameEdit, &QLineEdit::editingFinished, this, &ClubEditor::updateClubName);
//    connect(ui->coachNameEdit, &QLineEdit::editingFinished, this, &ClubEditor::updateCoachName);
    connect(ui->usaBtn, &QPushButton::toggled, this, &ClubEditor::updateStateList);
    connect(ui->canadaBtn, &QPushButton::toggled, this, &ClubEditor::updateStateList);
    connect(ui->otherCountryBtn, &QPushButton::toggled, this, &ClubEditor::updateStateList);
    connect(ui->saveBtn, &QPushButton::pressed, this, &ClubEditor::updateClub);
    connect(ui->revertBtn, &QPushButton::pressed, this, &ClubEditor::revertClub);
}

ClubEditor::~ClubEditor()
{
    delete ui;
}

void ClubEditor::editClub(Club *club)
{
    m_club = club;

    updateControls();
}

void ClubEditor::updateClubName()
{
    m_club->setClubName(ui->clubNameEdit->text());
}

void ClubEditor::updateControls()
{
    ui->clubNameEdit->setText(m_club->clubName());
    ui->coachNameEdit->setText(m_club->coachName());
    ui->address1Edit->setText(m_club->address1());
    ui->address2Edit->setText(m_club->address2());
    ui->cityEdit->setText(m_club->city());
    ui->zipEdit->setText(m_club->zip());
    ui->stateCombo->clear();
    if(m_club->country().isEmpty() || m_club->country().compare("usa", Qt::CaseInsensitive) == 0)
    {
        ui->usaBtn->setChecked(true);
//        ui->stateCombo->addItems(states.split(","));
//        ui->stateCombo->setCurrentText(m_club->state().toUpper());
//        ui->otherCountryEdit->setText("");
    }
    else if(m_club->country().compare("canada", Qt::CaseInsensitive) == 0)
    {
        ui->canadaBtn->setChecked(true);
//        ui->stateCombo->addItems(provinces.split(","));
//        ui->stateCombo->setCurrentText(m_club->state().toUpper());
//        ui->otherCountryEdit->setText("");
    }
    else
    {
        ui->otherCountryBtn->setChecked(true);
//        ui->otherCountryEdit->setText(m_club->country());
    }
    updateStateList();
}

void ClubEditor::updateCoachName()
{
    m_club->setCoachName(ui->coachNameEdit->text());
}

void ClubEditor::updateClub()
{
    // This should be done with a controller
    m_club->setClubName(ui->clubNameEdit->text());
    m_club->setCoachName(ui->coachNameEdit->text());
    m_club->setAddress1(ui->address1Edit->text());
    m_club->setAddress2(ui->address2Edit->text());
    m_club->setCity(ui->cityEdit->text());
    m_club->setState(ui->stateCombo->currentText());
    QString country;
    if(ui->usaBtn->isChecked())
    {
        country = "USA";
    }
    else if(ui->canadaBtn->isChecked())
    {
        country = "Canada";
    }
    else
    {
        country = ui->otherCountryEdit->text();
    }
    m_club->setCountry(country);
    m_club->setZip(ui->zipEdit->text());

}

void ClubEditor::revertClub()
{
    updateControls();
}

void ClubEditor::updateStateList()
{
    ui->stateCombo->clear();
    ui->otherCountryEdit->setText("");
    if(ui->usaBtn->isChecked())
    {
        // US States
        ui->stateCombo->addItems(states.split(","));
    }
    else if(ui->canadaBtn->isChecked())
    {
        // Canadian Provinces
        ui->stateCombo->addItems(provinces.split(","));
    }
    else
    {
        ui->otherCountryEdit->setText(m_club->country());

    }
    ui->stateCombo->setCurrentText(m_club->state().toUpper());
}
