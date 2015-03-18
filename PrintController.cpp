#include "PrintController.h"

#include "Tournament.h"
#include "Bracket.h"
#include "Competitor.h"
#include "Club.h"
#include "JudoMasterApplication.h"

#include <QDebug>
#include <QtGui>

//#include <QFontMetrics>
//#include <QList>
//#include <QtPrintSupport>
#include <QPrintDialog>
//#include <QRect>
//#include <QString>
//#include <QWidget>

namespace
{
    const QRectF nameRect(0.5, 2.0, 3.5, 0.2);
    const QRectF genderRect(4.0, 2.0, 1.0, 0.2);
    const QRectF ageRect(5.0, 2.0, 0.5, 0.2);
    const QRectF numDivsRect(5.5, 2.0, 0.5, 0.2);
    const QRectF regWeightRect(5.5, 2.0, 1.0, 0.2);
    const QRectF actWeightRect(6.5, 2.0, 1.0, 0.2);

    bool compareCompetitorNames(Competitor* competitor1, Competitor* competitor2)
    {
        int lastNameCompare = competitor1->lastName().compare(competitor2->lastName());
        if( lastNameCompare < 0)
        {
            return true;
        }

        if(lastNameCompare == 0)
        {
            // Last names are the same, compare the first name.
            return competitor1->firstName().compare(competitor2->firstName()) < 0;
        }

        return false;
    }

}

PrintController::PrintController(QString tournament, QPrinter::Orientation orientation)
    : QObject()
    , m_tournament(tournament)
    , m_page(1)
    , m_orientation(orientation)
{
}

bool PrintController::prepare(const QString &title)
{
#ifndef PRINT_DEBUG
    printer = new QPrinter();
    printer->setFullPage(true);
    printer->setOrientation(m_orientation);
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

bool PrintController::printBracket(const Bracket *bracket)
{
    if(bracket->competitors().size() == 0)
    {
        // Don't print a bracket with now competitors.
        return false;
    }
    else if (bracket->competitors().size() > 8)
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

    return true;
}

bool PrintController::printClubRegistration(const Club *club)
{
    qDebug() << "Printing Registration for Club: " << club->clubName();

    printClubHeader(club);

    float y = 2.2;
    QList<Competitor *> clubCompetitors(club->competitors());
    std::sort(clubCompetitors.begin(), clubCompetitors.end(), compareCompetitorNames);
    foreach(Competitor *competitor, clubCompetitors)
    {
        y = printCompetitorRegistration(y, competitor);
    }

    return true;
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
    QList<QString> clubNames;
    const QList<Competitor *> comps = bracket->competitors();
    QString bye("BYE");
    compNames << bye << bye << bye << bye << bye << bye << bye << bye;
    clubNames << "" << "" << "" << "" << "" << "" << "" << "";
    int indices[8] = { 0, 1, 2, 4, 6, 5, 3, 7 };
    for (int i=0; i < comps.size(); i++)
    {
        compNames[indices[i]] = comps[i]->firstName() + " " + comps[i]->lastName()[0];
        Club * club = getClub(comps[i]->clubId());
        if (club)
        {
            clubNames[indices[i]] = QString(club->clubName());
        }
    }

    float startY = 2.8125;
    for (int i=0; i < 4; i++)
    {
        drawNormalText(6.0625, startY, compNames[i*2]);
        drawText(6.125, startY + 0.1875, clubNames[i*2], 10.0, false, Qt::gray);
        drawNormalText(6.0625, startY + 0.4375, compNames[i*2+1]);
        drawText(6.125, startY + 0.625, clubNames[i*2+1], 10.0, false, Qt::gray);
        startY += 1.0;
    }


    drawNormalText(10.125, 4.6875, "#1");
    drawRightAlignedText(0.75, 5.9375, "#2");
}

void PrintController::printClubHeader(const Club *club)
{
    // TODO Below Code should be refactored, maybe to prepare()?
    p.setRenderHint(QPainter::Antialiasing);
    dpi = qMin(p.viewport().width()/pageWidth(), p.viewport().height()/pageHeight());
    p.save();
    p.scale(dpi, dpi);
    t = p.combinedTransform();
    p.restore();
    // END OF CODE TO BE REFACTORED

    drawCenteredText(pageWidth() / 2/*5.5*/, 1.0, m_tournament, 16, true);
    drawCenteredText(pageWidth() / 2/*5.5*/, 1.5, club->clubName(), 16.0, true);

    // | Name                       | Gender  | Age | #Divs |  Reg Weight | Actual Weight |
    //            4"                    1"      .5"      .5"          1"           1"

    drawText(nameRect, "Name");
    drawText(genderRect, "Gender", Qt::AlignCenter);
    drawText(ageRect, "Age", Qt::AlignCenter);
//    drawText(numDivsRect, "# Divs", Qt::AlignCenter);
    drawText(regWeightRect, "Reg Weight", Qt::AlignCenter);
    drawText(actWeightRect, "Act Weight", Qt::AlignCenter);

}


void PrintController::printHeader(const Bracket *bracket)
{
    p.setRenderHint(QPainter::Antialiasing);
    dpi = qMin(p.viewport().width()/pageWidth(), p.viewport().height()/pageHeight());
    p.save();
    p.scale(dpi, dpi);
    t = p.combinedTransform();
    p.restore();

    drawCenteredText(pageWidth() / 2/*5.5*/, 1.0, m_tournament, 16, true);
    drawCenteredText(pageWidth() / 2/*5.5*/, 1.5, bracket->name(), 16.0, true);

    drawChokeArmbar(9.75, 1.25, bracket->chokesAllowed(), bracket->armbarsAllowed());

}

void PrintController::printRoundRobinBracket(const Bracket *bracket)
{
    printHeader(bracket);

    drawPlace(0.5, 1.8125, "First:");
    drawPlace(0.5, 2.1875, "Second:");
    drawPlace(0.5, 2.5625, "Third:");

    float y = 3.125;
    float x = 8.625;

    drawCenteredText(x+0.5, y-0.25, "TOTAL", 12.0, true);
    drawCenteredText(x, y, "WINS", 12.0, true);
    drawCenteredText(x+1.0, y, "POINTS", 12.0, true);


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

    y = 7.5;
    x = 10.0;
    drawRightAlignedText(x, y, "Ippon / Hansoku Make:", 10.0);
    drawRightAlignedText(x+0.25, y, "10", 10.0);
    drawRightAlignedText(x, y+0.25, "Waza-ari / Shido #3:", 10.0);
    drawRightAlignedText(x+0.25, y+0.25, "7", 10.0);
    drawRightAlignedText(x, y+0.125, "Yuko / Shido #2:", 10.0);
    drawRightAlignedText(x+0.25, y+0.125, "5", 10.0);
    drawRightAlignedText(x, y+0.375, "Judges Decision:", 10.0);
    drawRightAlignedText(x+0.25, y+0.375, "1", 10.0);
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
    float boxesWidth = x + 2.0 + 5*(height + 0.25) + 0.5;
    drawHeavyBox(boxesWidth, y, height, height);
    drawHeavyBox(boxesWidth + height + 0.25, y, height, height);

    float tempx = x+2.25;
    foreach (bool box, boxes)
    {
        if (box)
        {
            drawLightBox(tempx, y, height, height);
        }
        tempx += height + 0.25;
    }
    QString compName(comp->firstName());
    compName += " " + comp->lastName()[0];
    drawNormalText(x+0.0625, y+0.25, compName);

    Club * club = getClub(comp->clubId());
    if (club)
    {
        drawText(x+0.125, y+0.625, club->clubName(), 10.0);
    }
}

float PrintController::printCompetitorRegistration(float y, Competitor *competitor)
{
    float top = y;
    drawLightBox(0.5, top, pageWidth() - 1.0, 0.20);
    QRectF rect(nameRect.left(), top, nameRect.width(), nameRect.height());
    drawText(rect, QString("%1, %2").arg(competitor->lastName()).arg(competitor->firstName()));
    drawText(QRectF(genderRect.left(), top, genderRect.width(), genderRect.height()), genderToString(competitor->gender()), Qt::AlignCenter);
    drawText(QRectF(ageRect.left(), top, ageRect.width(), ageRect.height()), QString("%1").arg(competitor->age()), Qt::AlignCenter);
//    int numDivs = JMApp()->bracketController()->competitorBrackets(competitor->id()).size();
//    int registeredDivs = competitor->numBrackets();
//    QColor color = numDivs == registeredDivs ? QColor(Qt::black) : QColor(Qt::red);
//    drawText(QRectF(numDivsRect.left(), top, numDivsRect.width(), numDivsRect.height()), QString("%1/%2").arg(numDivs).arg(registeredDivs), Qt::AlignCenter, 12.0, false, color);
    drawText(QRectF(regWeightRect.left(), top, regWeightRect.width(), regWeightRect.height()), QString("%1").arg(competitor->weight()), Qt::AlignCenter);

    //    drawText(0.7, top + 0.15, QString("%1, %2").arg(competitor->lastName()).arg(competitor->firstName()), 12.0);

    qDebug() << "Printing Competitor " << competitor->firstName() << " " << competitor->lastName();
    top += 0.20;
    return top;
}

Club * PrintController::getClub(int clubId)
{
    return dynamic_cast<Club *>(JMApp()->clubController()->find(clubId));
}

void PrintController::joinMatch(float baseY, float height, int comp1, int comp2, int match)
{
    float y = baseY + height + (comp1-1)*(height + 0.25);
    float length = 0.25 + (comp2-comp1-1)*(height + 0.25);
    float x = 3.0 + height/2 + ((match-1) * (height + 0.25));
    drawVerticalLine(x, y, length);
}

void PrintController::drawChokeArmbar(float x, float y, bool choke, bool armbar)
{
    drawRightAlignedText(x, y, QString("Chokes:"));
    drawText(x+0.125, y, (choke?"Yes":"No"));
    drawRightAlignedText(x, y+0.25, QString("Arm Bars:"));
    drawText(x+0.125, y+0.25, (armbar?"Yes":"No"));
}

float PrintController::pageWidth()
{
    if(m_orientation == QPrinter::Portrait)
        return 8.5;

    return 11.0;
}

float PrintController::pageHeight()
{
    if(m_orientation == QPrinter::Portrait)
        return 11.0;

    return 8.5;
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

void PrintController::drawText(float x, float y, const QString & text, float size, bool underlined, int color)
{
    QPointF point(x, y);
    float points_to_inches = 1/72.0;

    QFont f("Arial");
    f.setPixelSize(dpi*points_to_inches*size);
    f.setUnderline(underlined);

    p.setFont(f);
    p.setPen(color);
    p.drawText( t.map( point ), text );
}

void PrintController::drawText(QRectF rect, const QString &text, int flags, float size, bool underlined, QColor color)
{
    float points_to_inches = 1/72.0;

    QFont f("Arial");
    f.setPixelSize(dpi*points_to_inches*size);
    f.setUnderline(underlined);

    p.setFont(f);
    p.setPen(color);

    p.drawText(t.mapRect(rect), flags|Qt::TextSingleLine, text);

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

void PrintController::drawRightAlignedText(float x, float y, const QString & text, float size, bool underlined)
{
    QPointF point(x, y);
    QPointF mapped_point(t.map(point));
    float points_to_inches = 1/72.0;

    QFont f("Arial");
    f.setPixelSize(dpi*points_to_inches*size);
    f.setUnderline(underlined);
    p.setFont(f);

    int width = p.fontMetrics().width(text);
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
