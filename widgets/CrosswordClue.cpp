#include "CrosswordClue.h"

CrosswordClue::CrosswordClue( const int n, QListBox* listbox, const QString& text ) : QListBoxText( listbox, "" )
{
    m_number = n;

    setText( QString::number( number() ) + QString( "." ) + text );
}

CrosswordClue::CrosswordClue( const int n, const QString& text ) : QListBoxText( "" )
{
    m_number = n;

    setText( QString::number( number() ) + QString( "." ) + text );
}

CrosswordClue::CrosswordClue( const int n, QListBox* listbox, const QString& text, QListBoxItem* after ) : QListBoxText( listbox, "", after )
{
    m_number = n;

    setText( QString::number( number() ) + QString( "." ) + text );
}

CrosswordClue::~CrosswordClue()
{
}


int CrosswordClue::number() const
{
    return m_number;
}
