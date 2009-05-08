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

#include <QDebug>
#include <QVBoxLayout>

Crossword::Crossword( QWidget* parent )
    : QWidget( parent )
    , m_puzzle( 0 )
{
    // Create widgets
    m_puzzleGroupBox = new QGroupBox( "Puzzle", this );
    QVBoxLayout *puzzleLayout = new QVBoxLayout( m_puzzleGroupBox );

    m_grid = new CrosswordGrid( this );
    m_grid->setMinimumSize( 500, 500 );
    puzzleLayout->addWidget( m_grid );
    m_puzzleGroupBox->setLayout( puzzleLayout );

    // CLUES LAYOUT
    QWidget     *cluesBox       = new QWidget( this );
    QVBoxLayout *cluesBoxLayout = new QVBoxLayout( cluesBox );

    QGroupBox* acrossGroupBox = new QGroupBox( "Across", cluesBox );
    QVBoxLayout *acrossCluesLayout = new QVBoxLayout( acrossGroupBox );
    m_acrossClues = new CrosswordClueList( this );
    m_acrossClues->setMinimumWidth(300);
    acrossCluesLayout->addWidget( m_acrossClues );
    acrossGroupBox->setLayout( acrossCluesLayout );

    QGroupBox* downGroupBox   = new QGroupBox( "Down", cluesBox );
    QVBoxLayout *downCluesLayout = new QVBoxLayout( downGroupBox );
    m_downClues   = new CrosswordClueList( this );
    m_downClues->setMinimumWidth(300);
    downCluesLayout->addWidget( m_downClues );
    downGroupBox->setLayout( downCluesLayout );

    cluesBoxLayout->addWidget( acrossGroupBox );
    cluesBoxLayout->addWidget( downGroupBox );
    cluesBox->setLayout( cluesBoxLayout );

    // Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout( this );
    mainLayout->addWidget( m_puzzleGroupBox );
    mainLayout->addWidget( cluesBox );
    setLayout( mainLayout );

    connect( m_acrossClues, SIGNAL( clueSelected(AcrossLiteClue::Orientation, int) ),
             m_grid,        SLOT  ( selectClue(AcrossLiteClue::Orientation, int) ) );

    connect( m_downClues,   SIGNAL( clueSelected(AcrossLiteClue::Orientation, int) ),
             m_grid,        SLOT  ( selectClue(AcrossLiteClue::Orientation, int) ) );

    connect( m_grid, SIGNAL( currentCellChanged(int, int, int, int) ),
             this,   SLOT  ( handleNewColRowFocused(int, int, int, int) ) );
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

void Crossword::handleNewColRowFocused( int currentRow, int currentColumn, int previousRow, int previousColumn )
{
    Q_UNUSED( previousRow )
    Q_UNUSED( previousColumn )

    int down, across;

    m_grid->colRowToDownAcross( currentColumn, currentRow, down, across );

    qDebug() << "selected across:" << across << "; down:" << down;

    m_downClues->clueSelected( down );
    m_acrossClues->clueSelected( across );
}

