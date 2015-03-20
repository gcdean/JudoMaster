#include "JudoMasterMainWindow.h"
#include "ui_JudoMasterMainWindow.h"

#include "Bracket.h"
#include "CompetitorController.h"
#include "JudoMasterApplication.h"
#include "Tournament.h"
#include "actions/PrintBracketsAction.h"
#include "commands/ImportDataCommand.h"
#include "commands/PrintBrancketsCommand.h"
#include "commands/PrintRegistrationCommand.h"

#include <QDate>
#include <QFileDialog>
#include <QFileInfo>
#include <QJsonDocument>
#include <QHash>
#include <QJsonObject>
#include <QStringList>
#include <QTextStream>

#include <QDebug>



JudoMasterMainWindow::JudoMasterMainWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::JudoMasterMainWindow)
    , m_printBracketsAction(0)
    , m_tournament(0)
{
    ui->setupUi(this                                            );

    m_saveDir = QDir::home();


    ui->mainToolBar->setVisible(false);

    ui->tabWidget->setTabText(0, QString("General"));
    ui->tabWidget->setTabText(1, QString("Brackets"));

    m_printBracketsAction = new PrintBracketsAction(this);
    ui->menuPrint->addAction(m_printBracketsAction);

    connect(ui->actionNew, &QAction::triggered, this, &JudoMasterMainWindow::newTournament);
    connect(ui->actionSave_As, &QAction::triggered, this, &JudoMasterMainWindow::saveAs);
    connect(ui->actionSave, &QAction::triggered, this, &JudoMasterMainWindow::save);
    connect(ui->actionClose, &QAction::triggered, this, &JudoMasterMainWindow::close);
    connect(ui->actionOpen, &QAction::triggered, this, &JudoMasterMainWindow::open);
    connect(ui->actionPrint_Registration, &QAction::triggered, this, &JudoMasterMainWindow::printRegistration);
    connect(m_printBracketsAction, &QAction::triggered, this, &JudoMasterMainWindow::printBrackets);
    connect(ui->actionImport, &QAction::triggered, this, &JudoMasterMainWindow::import);

    connect(ui->tournamentName, &QLineEdit::editingFinished, this, &JudoMasterMainWindow::nameChanged);
    connect(ui->tournamentDate, &QDateTimeEdit::dateChanged, this, &JudoMasterMainWindow::dateChanged);
    connect(ui->startTime, &QDateTimeEdit::timeChanged, this, &JudoMasterMainWindow::timeChanged);

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

void JudoMasterMainWindow::dateChanged(const QDate &date)
{
    if(!m_tournament)
    {
        return;
    }

    m_tournament->setDate(date);
}

void JudoMasterMainWindow::timeChanged(const QTime &time)
{
    if(!m_tournament)
    {
        return;
    }

    m_tournament->setStartTime(time);
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

    resetTitle();
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
    JMApp()->setTournament(m_tournament);
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

void JudoMasterMainWindow::printBrackets()
{
   PrintBracketsCommand cmd(m_tournament->name());
   cmd.run();
}

void JudoMasterMainWindow::printRegistration()
{
    PrintRegistrationCommand cmd(this);
    cmd.run();
}

void JudoMasterMainWindow::import()
{
    QString openFileName = QFileDialog::getOpenFileName(this, "Import CSV File", m_saveDir.absolutePath(), "CSV Files (*.csv)");

    if(openFileName.isEmpty())
    {
        return;
    }

    importFile(openFileName);
    resetTitle();
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

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    m_tournament = new Tournament();
    JMApp()->setTournament(m_tournament);
    m_tournament->setFileName(filename);


    QJsonObject jobj = loadDoc.object();
    m_tournament->read(jobj);

    JMApp()->clubController()->setTournament(m_tournament);
    JMApp()->competitorController()->setTournament(m_tournament);
    JMApp()->bracketController()->setTournament(m_tournament);

    resetTitle();

}

void JudoMasterMainWindow::importFile(QString filename)
{
    ImportDataCommand importCmd(filename);
    importCmd.run();

    const QList<Competitor *> imported = importCmd.importedCompetitors();
    const QList<Competitor *> skipped = importCmd.skippedCompetitors();

    qDebug() << "Imported Competitors:";
    foreach(Competitor *comp, imported)
    {
        qDebug() << comp->lastName() << ", " << comp->firstName() << ", " << dynamic_cast<Club *>(JMApp()->clubController()->find(comp->clubId()))->clubName();
    }

    qDebug() << "\n\nSkipped Competitors:";
    foreach(Competitor *comp, skipped)
    {
        qDebug() << comp->lastName() << ", " << comp->firstName();

    }

}

void JudoMasterMainWindow::resetTitle()
{
    if(m_tournament && !m_tournament->fileName().isEmpty())
    {
        QFileInfo fi(m_tournament->fileName());
        setWindowTitle(QString("Judo Master (%1.%2)").arg(fi.completeBaseName()).arg(fi.completeSuffix()));
    }
    else
    {
        setWindowTitle("Judo Master");
    }
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

    resetTitle();
}
