#include "CrosswordCell.h"

CrosswordCell::CrosswordCell( QWidget* parent )
        : QWidget( parent )
{
    m_colLabel   = 0;
    m_rowLabel   = 0;
    m_solution   = '.';
    m_guess      = ' ';

    revealSolution( false );
    setShowCorrectness( false );
    setNumber( 0 );
    showNumber( false );
    hilite( false );
}

CrosswordCell::~CrosswordCell()
{
}

QSize CrosswordCell::sizeHint() const
{
    return QSize( 20, 20 );
}

QSizePolicy CrosswordCell::sizePolicy() const
{
    return QSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred, true );
}

void CrosswordCell::setSolution( const char letter )
{
    m_solution = letter;

    update();
}

void CrosswordCell::setColRowLabel( const int col, const int row )
{
    m_colLabel = col;
    m_rowLabel = row;
}

int CrosswordCell::colLabel() const
{
    return m_colLabel;
}

int CrosswordCell::rowLabel() const
{
    return m_rowLabel;
}

void CrosswordCell::setGuess( const char letter )
{

    setShowCorrectness( false );

    // Don't change guess if cell is revealed.
    if ( isSolutionRevealed() ) return;

    m_guess = letter;

    update();
}

char CrosswordCell::solution() const
{
    return m_solution;
}

char CrosswordCell::guess() const
{
    return m_guess;
}

void CrosswordCell::revealSolution( const bool flag )
{
    m_isSolutionRevealed = flag;

    if ( flag == true )
    {
        setShowCorrectness( false );
    }

    if ( flag == false )
    {
        m_guess = ' ';
    }
    else
    {
        m_guess = solution();
    }

    update();
}

bool CrosswordCell::isSolutionRevealed() const
{
    return m_isSolutionRevealed;
}

bool CrosswordCell::showCorrectness() const
{
    return m_showCorrectness;
}

void CrosswordCell::setShowCorrectness( const bool flag )
{
    m_showCorrectness = flag;

    update();
}

bool CrosswordCell::isSolutionCorrect() const
{
    return ( solution() == guess() );
}

void CrosswordCell::setNumber( const int number )
{
    m_number = number;

    if ( m_number == 0 ) showNumber( false );

    update();
}

int CrosswordCell::number() const
{
    return m_number;
}

void CrosswordCell::showNumber( const bool flag )
{
    if ( number() == 0 )
    {
        m_isNumberShown = false;
        return;
    }

    m_isNumberShown = flag;

    update();
}

bool CrosswordCell::isNumberShown() const
{
    return m_isNumberShown;
}

void CrosswordCell::hilite( const bool flag )
{
    m_isHilited = flag;

    update();
}

bool CrosswordCell::isHilited() const
{
    return m_isHilited;
}

void CrosswordCell::paintEvent( QPaintEvent* )
{
    QPainter p( this );
    p.setPen( QPen( QColor( "black" ) ) );

    if ( solution() == '.' )
    {
        paintBlock( p );
    }
    else
    {
        if ( hasFocus() )
        {
            p.fillRect( rect(), QColor( "yellow" ) );
        }
        else
        {
            if ( isHilited() )
            {
                p.fillRect( rect(), QColor( 200, 200, 200 ) );
            }
            else
            {
                p.fillRect( rect(), QColor( "white" ) );
            }
        }

        paintFrame( p );

        if ( isNumberShown() )
        {
            paintNumber( p );
        }

        paintLetter( p );
    }
}

void CrosswordCell::paintBlock( QPainter& p )
{
    p.fillRect( rect(), QColor( "black" ) );
}

void CrosswordCell::paintFrame( QPainter& p )
{
    p.setPen( QPen( QColor( "black" ), 1 ) );
    p.drawRect( rect() );
}

void CrosswordCell::paintNumber( QPainter& p )
{
    QRect r = rect();
    r.setHeight( 12 );
    r.moveBy( 3, 0 );

    // Resize the font to the size of the cell.
    QFont f = p.font();
    QFontMetrics fm( f );
    while ( fm.height() < r.height() )
    {
        f.setPointSize( f.pointSize() + 2 );
        fm = QFontMetrics( f );
    }
    p.setFont( f );

    QString text;
    text.setNum( number() );

    p.drawText( r, Qt::AlignLeft, text );
}

void CrosswordCell::paintLetter( QPainter& p )
{
    QRect r = rect();
    int deltaY = r.height() - ( int )(( float )r.height() * .70 );

    r.setHeight( r.height() - deltaY );
    r.moveBy( 0, deltaY );

    // Resize the font to the size of the cell.
    QFont f = p.font();
    QFontMetrics fm( f );
    while ( fm.height() < r.height() )
    {
        f.setPointSize( f.pointSize() + 2 );
        fm = QFontMetrics( f );
    }
    p.setFont( f );

    QString letter;
    if ( isSolutionRevealed() == false )
    {
        letter = QString( QChar( guess() ) );
    }
    else
    {
        letter = QString( QChar( solution() ) );
    }

    p.drawText( r, Qt::AlignCenter, letter, 1 );

    if ( showCorrectness() == true && isSolutionRevealed() == false && guess() != ' ' && isSolutionCorrect() == false )
    {
        p.drawLine( rect().width(), 0, 0, rect().height() );
    }
}

