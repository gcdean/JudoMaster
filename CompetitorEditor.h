#ifndef COMPETITOREDITOR_H
#define COMPETITOREDITOR_H

#include <QDialog>

namespace Ui {
class CompetitorEditor;
}

class Competitor;

class CompetitorEditor : public QDialog
{
    Q_OBJECT

public:
    explicit CompetitorEditor(Competitor *competitor, QWidget *parent = 0);
    ~CompetitorEditor();

    // QDialog interface
public slots:
    virtual void accept();

private:
    Ui::CompetitorEditor *ui;
    Competitor *m_competitor;

};

#endif // COMPETITOREDITOR_H
