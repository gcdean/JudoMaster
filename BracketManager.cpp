#include "BracketManager.h"
#include "ui_BracketManager.h"

BracketManager::BracketManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BracketManager)
{
    ui->setupUi(this);
}

BracketManager::~BracketManager()
{
    delete ui;
}
