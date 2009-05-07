/***************************************************************************
 *   Copyright (C) 2009 by Seb Ruiz <ruiz@kde.org>                         *
 *                                                                         *
 *   Parts of this code are Copyright (C) 2003 Ernie Pasveer               *
 *   <EPasveer@houston.rr.com> from krosswordplayer                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "CrosswordClueList.h"

CrosswordClueList::CrosswordClueList( QWidget* parent, char* name )
    : QListBox( parent, name )
{
    m_puzzle   = 0;
    m_clueList = AcrossLiteClue::Unknown;

    QObject::connect( this, SIGNAL( pressed( QListBoxItem* ) ), this, SLOT( m_selected( QListBoxItem* ) ) );
}

CrosswordClueList::CrosswordClueList( AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList, QWidget* parent )
    : QListBox( parent )
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

    if ( m_clueList == AcrossLiteClue::Across )
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
    else if ( m_clueList == AcrossLiteClue::Down )
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

