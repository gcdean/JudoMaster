#ifndef PRINTCONTROLLER_H
#define PRINTCONTROLLER_H

#include <QPainter>
#include <QPrinter>

class Tournament;
class Bracket;
class Competitor;
class Club;

#define PRINT_DEBUG

class PrintController : public QObject
{
    Q_OBJECT
public:
    PrintController(Tournament * tournament);
    bool prepare(const QString &title);
    void printBracket(const Bracket *bracket);
    void nextPage();
    void endPrint();

private:
    void printDoubleEliminationBracket(const Bracket *bracket);
    void printRoundRobinBracket(const Bracket *bracket);
    void printRoundRobinTwo(const Bracket *bracket);
    void printRoundRobinThree(const Bracket *bracket);
    void printRoundRobinFour(const Bracket *bracket);
    void printCompetitor(float y, float height, Competitor *comp, QVector<bool> &boxes);
    Club * getClub(int clubId);
    void joinMatch(float baseY, float height, int comp1, int comp2, int match);
    void printHeader(const Bracket *bracket);
    void drawBox(float x, float y, float width, float height, float weight);
    void drawLightBox(float x, float y, float width, float height);
    void drawHeavyBox(float x, float y, float width, float height);
    void drawHorizontalLine(float x, float y, float length, float weight=0.01);
    void drawVerticalLine(float x, float y, float length, float weight=0.01);
    void drawOpenRectLeft(float x, float y, float width, float height);
    void drawOpenRectRight(float x, float y, float width, float height);
    void drawNormalText(float x, float y, const QString & text);
    void drawUnderlinedText(float x, float y, const QString & text);
    void drawCenteredText(float x, float y, const QString & text, float size=12.0, bool underlined=false);
    void drawRightAlignedText(float x, float y, const QString & text, float size=12.0, bool underlined=false);
    void drawText(float x, float y, const QString & text, float size=12.0, bool underlined=false, int color = Qt::black);
    void drawPlace(float x, float y, const QString &text);
    void drawChokeArmbar(float x, float y, bool choke, bool armbar);
    int m_timerId;
    int m_page;
    Tournament * m_tournament;
    QTransform t;
    QPainter p;
#ifndef PRINT_DEBUG
    QPrinter *printer;
#else
    QImage *image;
#endif
    float dpi;
};


#endif // PRINTCONTROLLER_H
