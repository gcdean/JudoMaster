#include "CompetitorList.h"
#include "ui_CompetitorList.h"

CompetitorList::CompetitorList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CompetitorList)
{
    ui->setupUi(this);
}

CompetitorList::~CompetitorList()
{
    delete ui;
}
