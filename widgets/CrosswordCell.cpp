#include "CrosswordCell.h"

CrosswordCell::CrosswordCell( QWidget* parent )
    : QWidget( parent )
    , m_colLabel( 0 )
    , m_rowLabel( 0 )
    , m_solution( '.' )
    , m_guess()
    , m_isSolutionRevealed( false )
    , m_showCorrectness( false )
    , m_number( 0 )
    , m_isNumberShown( false )
    , m_isHilited( false )
{
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

void CrosswordCell::setSolution( const QChar letter )
{
    m_solution = letter;
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

void CrosswordCell::setGuess( const QChar letter )
{
    setShowCorrectness( false );

    // Don't change guess if cell is revealed.
    if ( isSolutionRevealed() )
        return;

    m_guess = letter;
}

QChar CrosswordCell::solution() const
{
    return m_solution;
}

QChar CrosswordCell::guess() const
{
    return m_guess;
}

void CrosswordCell::revealSolution( const bool flag )
{
    m_isSolutionRevealed = flag;

    if ( flag == true )
        setShowCorrectness( false );

    if ( flag == false )
        m_guess = ' ';
    else
        m_guess = m_solution;
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
}

bool CrosswordCell::isSolutionCorrect() const
{
    return m_solution == m_guess;
}

void CrosswordCell::setNumber( const int number )
{
    m_number = number;

    if ( m_number == 0 )
        showNumber( false );
}

int CrosswordCell::number() const
{
    return m_number;
}

void CrosswordCell::showNumber( const bool flag )
{
    if ( m_number == 0 )
    {
        m_isNumberShown = false;
        return;
    }

    m_isNumberShown = flag;
}

bool CrosswordCell::isNumberShown() const
{
    return m_isNumberShown;
}

void CrosswordCell::hilite( const bool flag )
{
    m_isHilited = flag;
}

bool CrosswordCell::isHilited() const
{
    return m_isHilited;
}
