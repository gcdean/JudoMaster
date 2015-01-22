#include "BracketManager.h"
#include "ui_BracketManager.h"

#include "BracketTableModel.h"
#include "JudoMasterApplication.h"

#include <QDebug>

BracketManager::BracketManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BracketManager)
{
    ui->setupUi(this);

    ui->bracketList->setModel(new BracketTableModel());

    ui->bracketList->setController(JMApp()->bracketController());
}

BracketManager::~BracketManager()
{
    delete ui;
}

void BracketManager::addBracket()
{
    qDebug() << "ADD A BRACKET";
}
