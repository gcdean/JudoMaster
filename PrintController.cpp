#include "PrintController.h"

#include "Tournament.h"
#include "Bracket.h"
#include "Competitor.h"
#include "Club.h"

#include <QtGui>

//#include <QFontMetrics>
//#include <QList>
//#include <QtPrintSupport>
#include <QPrintDialog>
//#include <QRect>
//#include <QString>
//#include <QWidget>

PrintController::PrintController(Tournament * tournament)
    : QObject()
    , m_tournament(tournament)
    , m_page(1)
{
}

bool PrintController::prepare(const QString &title)
{
#ifndef PRINT_DEBUG
    printer = new QPrinter();
    printer->setFullPage(true);
    printer->setOrientation(QPrinter::Landscape);
    QPrintDialog *dialog = new QPrintDialog(printer);
    dialog->setWindowTitle(title);
    if (dialog->exec() != QDialog::Accepted)
        return false;
    p.begin(printer);
#else
    image = new QImage(110 * 30, 85 * 30, QImage::Format_RGB32);
    p.begin(image);
    p.fillRect(0, 0, image->width(), image->height(), Qt::white);
#endif

    return true;
}

void PrintController::nextPage()
{
#ifndef PRINT_DEBUG
    printer->newPage();
#else
    p.end();
    QString fileName = QString("bracket_%1.png").arg(m_page);
    image->save(fileName);
    m_page++;
    p.begin(image);
    p.fillRect(0, 0, image->width(), image->height(), Qt::white);
#endif
}

void PrintController::endPrint()
{
    p.end();
#ifndef PRINT_DEBUG
    delete printer;
#else
    QString fileName = QString("bracket_%1.png").arg(m_page);
    image->save(fileName);
    delete image;
#endif
}

void PrintController::printBracket(const Bracket *bracket)
{
    if (bracket->competitors().size() > 8)
    {
        // Not sure what to do here
    }
    else if (bracket->competitors().size() > 4)
    {
        printDoubleEliminationBracket(bracket);
    }
    else if (bracket->competitors().size() > 1)
    {
        printRoundRobinBracket(bracket);
    }

}

void PrintController::printDoubleEliminationBracket(const Bracket *bracket)
{

    //drawHeavyBox(0.0, 0.0, 11.0, 8.5);
    printHeader(bracket);

    drawCenteredText(6.8125, 2.375, "FIRST MATCH", 12.0, true);
    drawCenteredText(8.5, 2.5, "WINNERS >>>>>>");
    drawCenteredText(5.25, 2.5, "<<<<<< LOSERS");

    drawHeavyBox(6.0, 2.625, 1.625, 0.875);
    drawHeavyBox(6.0, 3.625, 1.625, 0.875);
    drawHeavyBox(6.0, 4.625, 1.625, 0.875);
    drawHeavyBox(6.0, 5.625, 1.625, 0.875);

    // Loser's Bracket
    drawOpenRectLeft(4.75, 3.125, 1.25, 1.0);
    drawOpenRectLeft(4.75, 5.125, 1.25, 1.0);
    drawOpenRectLeft(3.5, 3.625, 1.25, 1.0);
    drawText(3.5, 4.75, "Loser of A2", 10.0);
    drawOpenRectLeft(3.5, 5.625, 1.25, 1.0);
    drawText(3.5, 6.75, "Loser of A1", 10.0);
    drawOpenRectLeft(2.25, 4.125, 1.25, 2.0);
    drawOpenRectLeft(1.0, 5.125, 1.25, 1.5);
    drawText(1.0, 6.75, "Loser of B1", 10.0);
    drawHorizontalLine(0.75, 5.875, 0.25);

    // Winner's Bracket
    drawOpenRectRight(7.625, 3.125, 1.25, 1.0);
    drawOpenRectRight(7.625, 5.125, 1.25, 1.0);
    drawOpenRectRight(8.875, 3.625, 1.0, 2.0);
    drawHorizontalLine(9.875, 4.625, 0.25);
    drawCenteredText(8.25, 3.625, "A1");
    drawCenteredText(8.25, 5.625, "A2");
    drawCenteredText(9.25, 4.625, "B1");

    // Winners

    drawPlace(0.5, 1.8125, "First:");
    drawPlace(0.5, 2.1875, "Second:");
    drawPlace(0.5, 2.5625, "Third:");

    QList<QString> compNames;
    const QList<Competitor *> comps = bracket->competitors();
    QString bye("BYE");
    compNames << bye << bye << bye << bye << bye << bye << bye << bye;
    int indices[8] = { 0, 1, 2, 4, 6, 5, 3, 7 };
    for (int i=0; i < comps.size(); i++)
    {
        compNames[indices[i]] = comps[i]->firstName() + " " + comps[i]->lastName()[0];
    }

    float startY = 2.875;
    for (int i=0; i < 4; i++)
    {
        drawNormalText(6.125, startY, compNames[i*2]);
        drawNormalText(6.125, startY + 0.5, compNames[i*2+1]);
        startY += 1.0;
    }


    drawNormalText(10.125, 4.75, "#1");
    drawNormalText(0.75, 6.125, "#2");
}


void PrintController::printHeader(const Bracket *bracket)
{
    p.setRenderHint(QPainter::Antialiasing);
    dpi = qMin(p.viewport().width()/11.0, p.viewport().height()/8.5);
    p.save();
    p.scale(dpi, dpi);
    t = p.combinedTransform();
    p.restore();

    drawCenteredText(5.5, 1.0, m_tournament->name(), 16, true);
    drawCenteredText(5.5, 1.5, bracket->name(), 16.0, true);

    drawChokeArmbar(9.0, 1.25, bracket->chokesAllowed(), bracket->armbarsAllowed());

}

void PrintController::printRoundRobinBracket(const Bracket *bracket)
{
    printHeader(bracket);

    drawPlace(0.5, 1.8125, "First:");
    drawPlace(0.5, 2.1875, "Second:");
    drawPlace(0.5, 2.5625, "Third:");


    switch (bracket->competitors().size())
    {
    case 2:
        printRoundRobinTwo(bracket);
        break;
    case 3:
        printRoundRobinThree(bracket);
        break;
    case 4:
        printRoundRobinFour(bracket);
        break;
    }
}

void PrintController::printRoundRobinTwo(const Bracket *bracket)
{
    float y = 3.25;
    QVector<bool> boxes(5, true);
    boxes[3] = false; boxes[4] = false;
    printCompetitor(y, 0.75, bracket->competitors()[0], boxes);
    printCompetitor(y+1.0, 0.75, bracket->competitors()[1], boxes);
    joinMatch(y, 0.75, 1, 2, 1);
    joinMatch(y, 0.75, 1, 2, 2);
    joinMatch(y, 0.75, 1, 2, 3);
}

void PrintController::printRoundRobinThree(const Bracket *bracket)
{
    float y = 3.25;
    QVector<bool> boxes(5, true);
    boxes[1] = false; boxes[3] = false; boxes[4] = false;
    printCompetitor(y, 0.75, bracket->competitors()[0], boxes);
    boxes[1] = true; boxes[2] = false;
    printCompetitor(y+1.0, 0.75, bracket->competitors()[1], boxes);
    boxes[0] = false; boxes[2] = true;
    printCompetitor(y+2.0, 0.75, bracket->competitors()[2], boxes);
    joinMatch(y, 0.75, 1, 2, 1);
    joinMatch(y, 0.75, 2, 3, 2);
    joinMatch(y, 0.75, 1, 3, 3);
}

void PrintController::printRoundRobinFour(const Bracket *bracket)
{
    float y = 3.25;
    QVector<bool> boxes(5, true);
    boxes[1] = false; boxes[2] = true; boxes[3] = false; boxes[4] = true;
    printCompetitor(y, 0.75, bracket->competitors()[0], boxes);
    boxes[1] = true; boxes[2] = false; boxes[3] = true; boxes[4] = false;
    printCompetitor(y+1.0, 0.75, bracket->competitors()[1], boxes);
    boxes[1] = false; boxes[2] = true; boxes[3] = true; boxes[4] = false;
    printCompetitor(y+2.0, 0.75, bracket->competitors()[2], boxes);
    boxes[1] = true; boxes[2] = false; boxes[3] = false; boxes[4] = true;
    printCompetitor(y+3.0, 0.75, bracket->competitors()[3], boxes);
    joinMatch(y, 0.75, 1, 2, 1);
    joinMatch(y, 0.75, 3, 4, 1);
    joinMatch(y, 0.75, 2, 4, 2);
    joinMatch(y, 0.75, 1, 3, 3);
    joinMatch(y, 0.75, 2, 3, 4);
    joinMatch(y, 0.75, 1, 4, 5);
}

void PrintController::printCompetitor(float y, float height, Competitor *comp, QVector<bool> &boxes)
{
    float x = 0.75;
    drawHeavyBox(x, y, 2.0, height);
    drawHeavyBox(x+6.25, y, 0.5, height);
    drawHeavyBox(x+7.0, y, 0.5, height);

    float tempx = x+2.25;
    foreach (bool box, boxes)
    {
        if (box)
        {
            drawLightBox(tempx, y, 0.5, height);
        }
        tempx += 0.75;
    }
    QString compName(comp->firstName());
    compName += " " + comp->lastName()[0];
    drawNormalText(x+0.125, y+0.25, compName);

    Club * club = m_tournament->clubs()[comp->clubId()];
    QString clubName(club->clubName());
    drawNormalText(x+0.25, y+0.625, clubName);

}

void PrintController::joinMatch(float baseY, float height, int comp1, int comp2, int match)
{
    float y = baseY + height + (comp1-1)*(height + 0.25);
    float length = 0.25 + (comp2-comp1-1)*(height + 0.25);
    float x = 3.25 + ((match-1) * 0.75);
    drawVerticalLine(x, y, length);
}

void PrintController::drawChokeArmbar(float x, float y, bool choke, bool armbar)
{
    drawNormalText(x, y, QString("Chokes: ") + (choke?"Yes":"No"));
    drawNormalText(x, y+0.25, QString("Arm Bars: ") + (armbar?"Yes":"No"));
}

void PrintController::drawPlace(float x, float y, const QString &text)
{
    drawHeavyBox(x, y - 0.1875, 0.1875, 0.1875);
    drawNormalText(x + 0.25, y, text);
    drawHorizontalLine(x + 0.8875, y, 2.75);
}

void PrintController::drawBox(float x, float y, float width, float height, float weight)
{
    QBrush brush(Qt::black);
    float mapped_weight = dpi * weight;
    QPen pen(brush, mapped_weight);

    p.setPen(pen);

    //p->setBrush(hourColor);
    QRectF rect(t.mapRect(QRectF(x, y, width, height)));
    p.drawRect(rect);
}


void PrintController::drawLightBox(float x, float y, float width, float height)
{
    drawBox(x, y, width, height, 0.01);
}

void PrintController::drawHeavyBox(float x, float y, float width, float height)
{
    drawBox(x, y, width, height, 0.03);
}

void PrintController::drawOpenRectLeft(float x, float y, float width, float height)
{
    const QPointF points[4] = {
        t.map(QPointF(x+width, y)),
        t.map(QPointF(x, y)),
        t.map(QPointF(x, y+height)),
        t.map(QPointF(x+width, y+height))
    };

    QBrush brush(Qt::black);
    QPen pen(brush, 0.01*dpi);

    p.setPen(pen);

    p.drawPolyline(points, 4);
}

void PrintController::drawHorizontalLine(float x, float y, float length, float weight)
{
    QLineF line(t.map(QPointF(x, y)), t.map(QPointF(x+length, y)));

    QBrush brush(Qt::black);
    QPen pen(brush, weight*dpi);

    p.setPen(pen);

    p.drawLine(line);
}

void PrintController::drawVerticalLine(float x, float y, float length, float weight)
{
    QLineF line(t.map(QPointF(x, y)), t.map(QPointF(x, y+length)));

    QBrush brush(Qt::black);
    QPen pen(brush, weight*dpi);

    p.setPen(pen);

    p.drawLine(line);
}

void PrintController::drawOpenRectRight(float x, float y, float width, float height)
{
    const QPointF points[4] = {
        t.map(QPointF(x, y)),
        t.map(QPointF(x+width, y)),
        t.map(QPointF(x+width, y+height)),
        t.map(QPointF(x, y+height))
    };

    QBrush brush(Qt::black);
    QPen pen(brush, 0.01*dpi);

    p.setPen(pen);

    p.drawPolyline(points, 4);
}

void PrintController::drawText(float x, float y, const QString & text, float size, bool underlined)
{
    QPointF point(x, y);
    float points_to_inches = 1/72.0;

    QFont f("Arial");
    f.setPixelSize(dpi*points_to_inches*size);
    f.setUnderline(underlined);

    p.setFont(f);
    p.drawText( t.map( point ), text );
}

void PrintController::drawCenteredText(float x, float y, const QString & text, float size, bool underlined)
{
    QPointF point(x, y);
    QPointF mapped_point(t.map(point));
    float points_to_inches = 1/72.0;

    QFont f("Arial");
    f.setPixelSize(dpi*points_to_inches*size);
    f.setUnderline(underlined);
    p.setFont(f);

    int width = p.fontMetrics().width(text)/2;
    mapped_point.setX(mapped_point.x() - width);

    p.drawText( mapped_point, text );
}

void PrintController::drawNormalText(float x, float y, const QString & text)
{
    drawText(x, y, text, 12, false);
}

void PrintController::drawUnderlinedText(float x, float y, const QString & text)
{
    drawText(x, y, text, 12, true);
}
