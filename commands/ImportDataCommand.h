#ifndef IMPORTDATACOMMAND_H
#define IMPORTDATACOMMAND_H

#include "BaseCommand.h"

#include <QList>
#include <QString>

class Competitor;

class ImportDataCommand : public BaseCommand
{
public:
    ImportDataCommand(QString filename);
    ~ImportDataCommand();

    const QList<Competitor *> importedCompetitors() const;
    const QList<Competitor *> skippedCompetitors() const;

    // BaseCommand interface
    virtual bool run();

private:
    QString m_sourceFile;
    QList<Competitor *> m_importedCompetitors;
    QList<Competitor *> m_skippedCompetitors;
};

#endif // IMPORTDATACOMMAND_H
