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

#include "Crossword.h"

#include <QVBoxLayout>

Crossword::Crossword( QWidget* parent )
    : QWidget( parent )
    , m_puzzle( 0 )
{
    // Create widgets
    m_puzzleGroupBox = new QGroupBox( "Puzzle", this );

    m_grid = new CrosswordGrid( m_puzzleGroupBox );
    m_grid->setMinimumSize( 500, 500 );

    // CLUES LAYOUT
    QWidget     *cluesBox       = new QWidget( this );
    QVBoxLayout *cluesBoxLayout = new QVBoxLayout( cluesBox );

    QGroupBox* acrossGroupBox = new QGroupBox( "Across", cluesBox );
    QGroupBox* downGroupBox   = new QGroupBox( "Down",   cluesBox );

    cluesBoxLayout->addWidget( acrossGroupBox );
    cluesBoxLayout->addWidget( downGroupBox );
    cluesBox->setLayout( cluesBoxLayout );

    m_acrossClues = new CrosswordClueList( acrossGroupBox );
    m_downClues   = new CrosswordClueList( downGroupBox );

    m_acrossClues->setMinimumWidth(300);
    m_downClues->setMinimumWidth(300);

    connect( m_acrossClues, SIGNAL( clueSelected(AcrossLiteClue::Orientation, int) ),
             m_grid,        SLOT  ( setFocusCell(AcrossLiteClue::Orientation, int) ) );

    connect( m_downClues,   SIGNAL( clueSelected(AcrossLiteClue::Orientation, int) ),
             m_grid,        SLOT  ( setFocusCell(AcrossLiteClue::Orientation, int) ) );

    connect( m_grid,        SIGNAL( colRowFocused(int, int) ),
             this,          SLOT  ( handleNewColRowFocused(int, int) ) );
}

Crossword::~Crossword ()
{
    delete m_puzzle;
}

void Crossword::setPuzzle (const QString& filename)
{
    if( filename.isNull() )
        return;

    delete m_puzzle;

    m_puzzle = new AcrossLitePuzzle( filename.toAscii().data() );

    m_grid->setPuzzle( m_puzzle );
    m_acrossClues->setPuzzle( m_puzzle, AcrossLiteClue::Across );
    m_downClues->setPuzzle( m_puzzle, AcrossLiteClue::Down );

    m_puzzleGroupBox->setTitle( QString( m_puzzle->puzzleName().c_str() ) );
}

void Crossword::savePuzzle( const QString& filename )
{
    m_grid->savePuzzle( filename );
}

void Crossword::clearSolution()
{
    m_grid->revealSolution( false );
    m_grid->uncheckSolution();
}

void Crossword::revealSolution( const bool flag )
{
    m_grid->revealSolution( flag );
}

void Crossword::revealWord( const bool flag )
{
    m_grid->revealWord( flag );
}

void Crossword::revealLetter( const bool flag )
{
    m_grid->revealLetter( flag );
}

void Crossword::checkSolution()
{
    m_grid->checkSolution();
}

void Crossword::checkWord()
{
    m_grid->checkWord ();
}

void Crossword::checkLetter()
{
    m_grid->checkLetter ();
}

void Crossword::handleNewColRowFocused( int newCol, int newRow )
{
    int down, across;

    m_grid->colRowToDownAcross( newCol, newRow, down, across );

    if( down != -1 )
        m_downClues->clueSelected (down);

    if( across != -1 )
        m_acrossClues->clueSelected (across);
}

