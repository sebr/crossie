#include "CrosswordClueList.h"

CrosswordClueList::CrosswordClueList( QWidget* parent, char* name ) : QListBox( parent, name )
{
    m_puzzle   = 0;
    m_clueList = AcrossLiteClue::Unknown;

    QObject::connect( this, SIGNAL( pressed( QListBoxItem* ) ), this, SLOT( _selected( QListBoxItem* ) ) );
}

CrosswordClueList::CrosswordClueList( AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList, QWidget* parent, char* name ) : QListBox( parent, name )
{
    m_puzzle   = 0;
    m_clueList = AcrossLiteClue::Unknown;

    setPuzzle( puzzle, clueList );
}

CrosswordClueList::~CrosswordClueList()
{
}

void CrosswordClueList::setPuzzle( AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList )
{
    m_puzzle   = puzzle;
    m_clueList = clueList;

    clear();

    if ( _clueList == AcrossLiteClue::Across )
    {
        AcrossLiteClues::const_iterator b = m_puzzle->beginAcrossClue();
        AcrossLiteClues::const_iterator e = m_puzzle->endAcrossClue();
        while ( b != e )
        {
            CrosswordClue* clue = new CrosswordClue(( *b ).number(), QString(( *b ).clue().c_str() ) );
            insertItem( clue );

            b++;
        }

    }
    else if ( _clueList == AcrossLiteClue::Down )
    {
        AcrossLiteClues::const_iterator b = m_puzzle->beginDownClue();
        AcrossLiteClues::const_iterator e = m_puzzle->endDownClue();
        while ( b != e )
        {
            CrosswordClue* clue = new CrosswordClue(( *b ).number(), QString(( *b ).clue().c_str() ) );
            insertItem( clue );

            b++;
        }
    }
}

AcrossLitePuzzleBase* CrosswordClueList::puzzle()
{
    return m_puzzle;
}

AcrossLiteClue::Orientation CrosswordClueList::clueList()
{
    return m_clueList;
}

void CrosswordClueList::clueSelected( int n )
{
    for ( unsigned int i = 0; i < count(); i++ )
    {
        CrosswordClue* clue = ( CrosswordClue* ) item( i );
        if ( clue->number() == n )
        {
            setSelected( i, true );
            break;
        }
    }

    ensureCurrentVisible();
}

void CrosswordClueList::_selected( QListBoxItem* item )
{
    CrosswordClue* clue = ( CrosswordClue* ) item;

    if ( clue )
    {
        emit clueSelected( clueList(), clue->number() );
    }
}

