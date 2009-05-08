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
#include "CrosswordClue.h"

CrosswordClueList::CrosswordClueList( QWidget* parent )
    : QListWidget( parent )
    , m_puzzle( 0 )
    , m_clueList( AcrossLiteClue::Unknown )
{
    setSortingEnabled( false );
    setSelectionMode( QAbstractItemView::SingleSelection );

    connect( this, SIGNAL( currentItemChanged(QListWidgetItem*, QListWidgetItem*) ),
             this, SLOT  ( currentClueChanged(QListWidgetItem*, QListWidgetItem*) ) );
}


CrosswordClueList::~CrosswordClueList()
{
}

void CrosswordClueList::setPuzzle( AcrossLitePuzzle* puzzle, AcrossLiteClue::Orientation clueList )
{
    m_puzzle   = puzzle;
    m_clueList = clueList;

    clear();

    AcrossLiteClues::const_iterator it;
    AcrossLiteClues::const_iterator end;

    if ( m_clueList == AcrossLiteClue::Across )
    {
        it = m_puzzle->beginAcrossClue();
        end = m_puzzle->endAcrossClue();
    }
    else if ( m_clueList == AcrossLiteClue::Down )
    {
        it = m_puzzle->beginDownClue();
        end = m_puzzle->endDownClue();
    }

    while( it != end )
    {
        const AcrossLiteClue alClue = *it;
        const QString question = QString( alClue.clue().c_str() );
        CrosswordClue* clue = new CrosswordClue( alClue.number(), question, this );
        addItem( clue );

        it++;
    }
}

AcrossLitePuzzle* CrosswordClueList::puzzle()
{
    return m_puzzle;
}

AcrossLiteClue::Orientation CrosswordClueList::clueList()
{
    return m_clueList;
}

void CrosswordClueList::clueSelected( int n )
{
    clearSelection();
    for( int i = 0; i < count(); i++ )
    {
        CrosswordClue* clue = static_cast<CrosswordClue*>( item( i ) );
        if( clue->number() == n )
        {
            blockSignals(true);
            clue->setSelected( true );
            blockSignals(false);
            scrollToItem( clue, EnsureVisible );
            break;
        }
    }
}

void CrosswordClueList::currentClueChanged( QListWidgetItem *current, QListWidgetItem *previous )
{
    Q_UNUSED( previous )

    CrosswordClue* clue = static_cast<CrosswordClue*>(current);

    if( clue )
        emit clueSelected( clueList(), clue->number() );
}


