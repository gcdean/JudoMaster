#include "JudoMasterMainWindow.h"
#include "ui_JudoMasterMainWindow.h"

#include <QDate>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>

#include <QDebug>

#include "JudoMasterApplication.h"
#include "CompetitorController.h"
#include "Tournament.h"

JudoMasterMainWindow::JudoMasterMainWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::JudoMasterMainWindow)
    , m_tournament(0)
{
    ui->setupUi(this                                            );

    m_saveDir = QDir::home();

    qDebug() << "There are " << ui->tabWidget->count() << " tabs.";
    for( auto i = 0; i < ui->tabWidget->count(); i++)
    {
        qDebug() << "Tab " << i << " name is: " << ui->tabWidget->tabText(i);
    }
    ui->tabWidget->setTabText(0, QString("General"));
    ui->tabWidget->setTabText(1, QString("Brackets"));
//    ui->actionSave->setEnabled(false);
//    ui->actionSave_As->setEnabled(false);

    connect(ui->actionNew, &QAction::triggered, this, &JudoMasterMainWindow::newTournament);
    connect(ui->actionSave_As, &QAction::triggered, this, &JudoMasterMainWindow::saveAs);
    connect(ui->actionSave, &QAction::triggered, this, &JudoMasterMainWindow::save);
    connect(ui->actionClose, &QAction::triggered, this, &JudoMasterMainWindow::close);
    connect(ui->actionOpen, &QAction::triggered, this, &JudoMasterMainWindow::open);

    connect(ui->tournamentName, &QLineEdit::editingFinished, this, &JudoMasterMainWindow::nameChanged);

    connect(JMApp(), &QCoreApplication::aboutToQuit, this, &JudoMasterMainWindow::close);
    updateControls();
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
    if(m_tournament->fileName().isEmpty())
//    if(m_fileName.isEmpty())
    {
        if(!getFilename())
            return;
    }

    QFile saveFile(m_tournament->fileName());

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

    JMApp()->clubController()->setTournament(m_tournament);
    JMApp()->competitorController()->setTournament(m_tournament);
    JMApp()->bracketController()->setTournament(m_tournament);

    updateControls();
}

void JudoMasterMainWindow::close()
{
    // Check to see if we need to save.

    JMApp()->clubController()->setTournament(0);
    JMApp()->competitorController()->setTournament(0);
    JMApp()->bracketController()->setTournament(0);

    delete m_tournament;
    m_tournament = 0;
    updateControls();
}

void JudoMasterMainWindow::open()
{
    QString openFileName = QFileDialog::getOpenFileName(this, "Open JudoMaster Tournament File", m_saveDir.absolutePath(), "Tournament Files (*.ecj);;JSON Files (*.json)");

    if(openFileName.isEmpty())
    {
        return;
    }

    loadFile(openFileName);
    updateControls();
}

void JudoMasterMainWindow::loadFile(QString filename)
{
    QFile tournFile(filename);

    if(!tournFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open file for reading");
        return;
    }

    QByteArray saveData = tournFile.readAll();

//    qDebug() << "Size of Save Data is: " << saveData.size();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

//    qDebug() << "Is Doc Empty: " << loadDoc.isEmpty() << "\nData:\n" << loadDoc.toJson();
    m_tournament = new Tournament();
    m_tournament->setFileName(filename);

    JMApp()->clubController()->setTournament(m_tournament);
    JMApp()->competitorController()->setTournament(m_tournament);
    JMApp()->bracketController()->setTournament(m_tournament);


    QJsonObject jobj = loadDoc.object();
//    qDebug() << "Is JObject Empty: " << jobj.isEmpty() << ", It contains " << jobj.count() << " Items.";
    m_tournament->read(jobj);


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

    m_tournament->setFileName(newfileName);
    return true;
}

void JudoMasterMainWindow::updateControls()
{
    bool enabled = m_tournament == 0 ? false : true;

    ui->detailsWidget->setEnabled(enabled);
    ui->tournamentName->setEnabled(enabled);
    ui->startTime->setEnabled(enabled);
    ui->tournamentDate->setEnabled(enabled);

    ui->actionSave->setEnabled(enabled);
    ui->actionSave_As->setEnabled(enabled);

    if(enabled)
    {
        ui->tournamentName->setText(m_tournament->name());
        ui->tournamentDate->setDate(m_tournament->date());
        ui->startTime->setTime(m_tournament->startTime());
    }
}
