#include "BracketEditor.h"
#include "ui_BracketEditor.h"

BracketEditor::BracketEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BracketEditor)
{
    ui->setupUi(this);
}

BracketEditor::~BracketEditor()
{
    delete ui;
}
