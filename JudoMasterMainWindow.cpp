#include "JudoMasterMainWindow.h"
#include "ui_JudoMasterMainWindow.h"

#include <QDate>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>

#include "JudoMasterApplication.h"
#include "Tournament.h"

JudoMasterMainWindow::JudoMasterMainWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::JudoMasterMainWindow)
    , m_tournament(0)
{
    ui->setupUi(this);

    m_saveDir = QDir::home();

    ui->actionSave->setEnabled(false);
    ui->actionSave_As->setEnabled(false);

    connect(ui->actionNew, &QAction::triggered, this, &JudoMasterMainWindow::newTournament);
    connect(ui->actionSave_As, &QAction::triggered, this, &JudoMasterMainWindow::saveAs);
    connect(ui->actionSave, &QAction::triggered, this, &JudoMasterMainWindow::save);

    connect(ui->tournamentName, &QLineEdit::editingFinished, this, &JudoMasterMainWindow::nameChanged);
}

JudoMasterMainWindow::~JudoMasterMainWindow()
{
    delete ui;
}

void JudoMasterMainWindow::nameChanged()
{
    if(!m_tournament)
    {
        return;
    }

    m_tournament->setName(ui->tournamentName->text());
}

void JudoMasterMainWindow::save()
{
    if(m_fileName.isEmpty())
    {
        if(!getFilename())
            return;
    }

    QFile saveFile(m_fileName);

    if(!saveFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open file for writing");
    }


    QJsonObject trnObj;
    m_tournament->write(trnObj);

    QJsonDocument saveDoc(trnObj);
    saveFile.write(saveDoc.toJson());

}

void JudoMasterMainWindow::saveAs()
{
    if(!m_tournament)
        return;

    if(getFilename())
        save();
}

void JudoMasterMainWindow::newTournament()
{
    if(m_tournament)
    {
        delete m_tournament;
    }
    m_tournament = new Tournament();
    m_tournament->setName("Test");
    QDate trnDate(2015, 3, 15);
    m_tournament->setDate(trnDate);

    ui->actionSave->setEnabled(true);
    ui->actionSave_As->setEnabled(true);

    JMApp()->clubController()->setTournament(m_tournament);
    JMApp()->competitorController()->setTournament(m_tournament);
}

bool JudoMasterMainWindow::getFilename()
{
    QString newfileName = QFileDialog::getSaveFileName(this, "Save", m_saveDir.absolutePath(), "Tournament Files (*.ecj);;JSON Files (*.json)");
    if(newfileName.isEmpty())
    {
        return false;
    }

    QFileInfo finfo(newfileName);
    m_saveDir = finfo.absoluteDir();
    m_fileName = newfileName;

    return true;
}
