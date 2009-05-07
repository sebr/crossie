#include "CrosswordCell.h"

CrossWordCell::CrossWordCell (QWidget* parent)
    : QWidget(parent)
{
    _colLabel   = 0;
    _rowLabel   = 0;
    _solution   = '.';
    _guess      = ' ';

    revealSolution(false);
    setShowCorrectness (false);
    setNumber(0);
    showNumber(false);
    hilite(false);
}

CrossWordCell::~CrossWordCell () {
}

QSize CrossWordCell::sizeHint () const {
    return QSize(20,20);
}

QSizePolicy CrossWordCell::sizePolicy () const {
    return QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred, true);
}

void CrossWordCell::setSolution (const char letter) {
    _solution = letter;

    update();
}

void CrossWordCell::setColRowLabel (const int col, const int row) {
    _colLabel = col;
    _rowLabel = row;
}

int CrossWordCell::colLabel () const {
    return _colLabel;
}

int CrossWordCell::rowLabel () const {
    return _rowLabel;
}

void CrossWordCell::setGuess (const char letter) {

    setShowCorrectness(false);

    // Don't change guess if cell is revealed.
    if (isSolutionRevealed()) return;

    _guess = letter;

    update();
}

char CrossWordCell::solution () const {
    return _solution;
}

char CrossWordCell::guess () const {
    return _guess;
}

void CrossWordCell::revealSolution (const bool flag) {
    _isSolutionRevealed = flag;

    if (flag == true) {
        setShowCorrectness(false);
    }

    if (flag == false) {
        _guess = ' ';
    }else{
        _guess = solution();
    }

    update();
}

bool CrossWordCell::isSolutionRevealed () const {
    return _isSolutionRevealed;
}

bool CrossWordCell::showCorrectness () const {
    return _showCorrectness;
}

void CrossWordCell::setShowCorrectness (const bool flag) {
    _showCorrectness = flag;

    update ();
}

bool CrossWordCell::isSolutionCorrect () const {
    return (solution() == guess());
}

void CrossWordCell::setNumber (const int number) {
    _number = number;

    if (_number == 0) showNumber(false);

    update();
}

int CrossWordCell::number () const {
    return _number;
}

void CrossWordCell::showNumber (const bool flag) {
    if (number() == 0) {
        _isNumberShown = false;
        return;
    }

    _isNumberShown = flag;

    update();
}

bool CrossWordCell::isNumberShown () const {
    return _isNumberShown;
}

void CrossWordCell::hilite (const bool flag) {
    _isHilited = flag;

    update ();
}

bool CrossWordCell::isHilited () const {
    return _isHilited;
}

void CrossWordCell::paintEvent (QPaintEvent*) {
    QPainter p(this);
    p.setPen(QPen(QColor("black")));

    if (solution() == '.') {
        paintBlock(p);
    }else{
        if (hasFocus()) {
            p.fillRect(rect(), QColor("yellow"));
        }else{
            if (isHilited()) {
                p.fillRect(rect(), QColor(200,200,200));
            }else{
                p.fillRect(rect(), QColor("white"));
            }
        }

        paintFrame(p);

        if (isNumberShown()) {
            paintNumber(p);
        }

        paintLetter(p);
    }
}

void CrossWordCell::paintBlock (QPainter& p) {
    p.fillRect(rect(), QColor("black"));
}

void CrossWordCell::paintFrame (QPainter& p) {
    p.setPen(QPen(QColor("black"),1));
    p.drawRect(rect());
}

void CrossWordCell::paintNumber (QPainter& p) {
    QRect r = rect();
    r.setHeight( 12 );
    r.moveBy( 3,0 );

    // Resize the font to the size of the cell.
    QFont f = p.font();
    QFontMetrics fm (f);
    while (fm.height() < r.height()) {
        f.setPointSize( f.pointSize() + 2 );
        fm = QFontMetrics(f);
    }
    p.setFont(f);

    QString text;
    text.setNum(number());

    p.drawText(r, Qt::AlignLeft, text);
}

void CrossWordCell::paintLetter (QPainter& p) {
    QRect r = rect();
    int deltaY = r.height() - (int)((float)r.height() * .70);

    r.setHeight( r.height() - deltaY );
    r.moveBy( 0, deltaY );

    // Resize the font to the size of the cell.
    QFont f = p.font();
    QFontMetrics fm (f);
    while (fm.height() < r.height()) {
        f.setPointSize( f.pointSize() + 2 );
        fm = QFontMetrics(f);
    }
    p.setFont(f);

    QString letter;
    if (isSolutionRevealed() == false) {
        letter = QString(QChar(guess()));
    }else{
        letter = QString(QChar(solution()));
    }

    p.drawText(r, Qt::AlignCenter, letter, 1);

    if (showCorrectness() == true && isSolutionRevealed() == false && guess() != ' ' && isSolutionCorrect() == false) {
        p.drawLine (rect().width(),0, 0,rect().height());
    }
}

