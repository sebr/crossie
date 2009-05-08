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

#include "CrosswordGrid.h"

#include <QDebug>
#include <QHeaderView>
#include <QMouseEvent>

CrosswordGrid::CrosswordGrid( QWidget* parent )
    : QTableWidget( parent )
    , m_puzzle( 0 )
    , m_focusOrientation( FocusHorizontal )
{
    setEditTriggers( QAbstractItemView::NoEditTriggers );
    setSelectionMode( QAbstractItemView::SingleSelection );
    setSortingEnabled( false );

    horizontalHeader()->hide();
    verticalHeader()->hide();
}

CrosswordGrid::~CrosswordGrid()
{
}

CrosswordCell *CrosswordGrid::getCell( const int row, const int col ) const
{
    // Check bounds conditions
    if( row >= rowCount() || col >= columnCount() || row < 0 || col < 0 )
        return 0;

    return dynamic_cast<CrosswordCell*>( item( row, col ) );
}

QList<CrosswordCell*> CrosswordGrid::getCells() const
{
    QList<CrosswordCell*> cells;
    for( int row = 0; row < rowCount(); row++ )
    {
        for( int col = 0; col < columnCount(); col++ )
        {
            CrosswordCell *cell = getCell( row, col );
            if( cell )
                cells << cell;
        }
    }
    return cells;
}

void CrosswordGrid::setPuzzle( AcrossLitePuzzle* puzzle )
{
    m_puzzle           = puzzle;
    m_focusOrientation = FocusHorizontal;

    setColumnCount( m_puzzle->nColumns() );
    setRowCount( m_puzzle->nRows() );

    int colWidth  = 20;
    int rowHeight = 20;

    for( int row = 0; row < rowCount(); row++ )
    {
        for( int col = 0; col < columnCount(); col++ )
        {
            CrosswordCell* cell = new CrosswordCell();
            cell->setSolution( m_puzzle->solutionCell( col, row ) );
            cell->setShowCorrectness( false );
            cell->setGuess( m_puzzle->diagramCell( col, row ) );
            cell->setNumber( m_puzzle->cellNumber( col, row ) );
            cell->showNumber( true );
            colWidth  = cell->sizeHint().width();
            rowHeight = cell->sizeHint().height();

            setItem( row, col, cell );
        }
    }

    for( int col = 0; col < columnCount(); col++ )
        setColumnWidth( col, colWidth );
    for( int row = 0; row < rowCount(); row++ )
        setColumnWidth( row, rowHeight );
}

AcrossLitePuzzle* CrosswordGrid::puzzle()
{
    return m_puzzle;
}

void CrosswordGrid::savePuzzle( const QString& filename )
{
    Q_UNUSED( filename )
}

void CrosswordGrid::revealSolution( const bool flag )
{
    foreach( CrosswordCell *cell, getCells() )
        cell->revealSolution( flag );
}

void CrosswordGrid::revealWord( const bool flag )
{
    foreach( CrosswordCell *cell, getCells() )
    {
        if( cell->isHilited() )
            cell->revealSolution( flag );
    }
}

void CrosswordGrid::revealLetter( const bool flag )
{
    CrosswordCell* cell = dynamic_cast<CrosswordCell*>( currentItem() );
    if( cell->isHilited() )
        cell->revealSolution( flag );
}

void CrosswordGrid::uncheckSolution()
{
    foreach( CrosswordCell *cell, getCells() )
        cell->setShowCorrectness( false );
}

void CrosswordGrid::checkSolution()
{
    foreach( CrosswordCell *cell, getCells() )
        cell->setShowCorrectness( true );
}

void CrosswordGrid::checkWord()
{
    foreach( CrosswordCell *cell, getCells() )
    {
        if( cell->isHilited() )
            cell->setShowCorrectness( true );
    }
}

void CrosswordGrid::checkLetter()
{
    CrosswordCell* cell = dynamic_cast<CrosswordCell*>( currentItem() );
    if ( cell && cell->isHilited() )
        cell->setShowCorrectness( true );
}

QSize CrosswordGrid::sizeHint() const
{
    int cellSize = CrosswordCell::cellSize() + 2;
    return QSize( cellSize * rowCount(), cellSize * columnCount() );
}

QSizePolicy CrosswordGrid::sizePolicy() const
{
    return QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
}

void CrosswordGrid::setFocusOrientation( const CrosswordGrid::FocusOrientation orientation )
{
    hiliteSolution( false );
    m_focusOrientation = orientation;
    hiliteSolution( true );
}

CrosswordGrid::FocusOrientation CrosswordGrid::focusOrientation() const
{
    return m_focusOrientation;
}

void CrosswordGrid::hiliteSolution( const bool flag )
{
    CrosswordCell* c = dynamic_cast<CrosswordCell*>( currentItem() );
    if( !c )
        return;

    int col = c->column();
    int row = c->row();

    if ( focusOrientation() == CrosswordGrid::FocusVertical )
    {
        // Current to top.
        for ( int r = row; ; r-- )
        {
            CrosswordCell* cx = getCell( col, r );
            if( !cx || cx->isBlank() )
                break;

            cx->hilite( flag );
        }

        // Current to bottom.
        for ( int r = row; ; r++ )
        {
            CrosswordCell* cx = getCell( col, r );
            if( !cx || cx->isBlank() )
                break;

            cx->hilite( flag );
        }

    }
    else if ( focusOrientation() == CrosswordGrid::FocusHorizontal )
    {
        // Current to left.
        for ( int c = col; ; c-- )
        {
            CrosswordCell* cx = getCell( c, row );
            if( !cx || cx->isBlank() )
                break;

            cx->hilite( flag );
        }

        // Current to right.
        for ( int c = col; ; c++ )
        {
            CrosswordCell* cx = getCell( c, row );
            if( !cx || cx->isBlank() )
                break;

            cx->hilite( flag );
        }
    }
}

void CrosswordGrid::hiliteFullSolution( const bool flag )
{
    foreach( CrosswordCell *cell, getCells() )
        cell->hilite( flag );
}

void CrosswordGrid::colRowToDownAcross( const int col, const int row,  int& down, int& across )
{
    down = across = 0;

    // Find nearest down solution number.
    int r = row;
    CrosswordCell* downCell = getCell( r, col );
    while( downCell )
    {
        if( downCell->isBlank() )
            break;

        down = downCell->number();

        downCell = getCell( --r, col );
    }

    // Find nearest across solution number.
    int c = col;
    CrosswordCell* acrossCell = getCell( row, c );
    while( acrossCell )
    {
        if( acrossCell->isBlank() )
            break;

        across = acrossCell->number();

        acrossCell = getCell( row, --c );
    }
}

void CrosswordGrid::keyPressEvent( QKeyEvent *event )
{
    if( currentItem() )
    {
        if( (QChar(event->key()) >= 'a' && QChar(event->key()) <= 'z') ||
            (QChar(event->key()) >= 'A' && QChar(event->key()) <= 'Z') )
        {
            currentItem()->setText( QChar(event->key()) );

            if( focusOrientation() == CrosswordGrid::FocusHorizontal )
            {
                int col = currentColumn();
                if( col < columnCount() )
                    setCurrentCell( currentRow(), col + 1);
            }
            else
            {
                int row = currentRow();
                if( row < rowCount() )
                    setCurrentCell( row + 1, currentColumn() );
            }
            return;
        }
    }

    QTableWidget::keyPressEvent( event );
}

void CrosswordGrid::selectClue( AcrossLiteClue::Orientation orientation, int clueNumber )
{
    qDebug() << "Highlighting" << (orientation == AcrossLiteClue::Across ? "across" : "down")<< "clue" << clueNumber;
    CrosswordCell *target = 0;
    foreach( CrosswordCell *cell, getCells() )
    {
        if( !target && cell->number() == clueNumber )
            target = cell;
        cell->hilite(false);
    }

    clearSelection();
    if( target )
        target->setSelected(true);

    while( target )
    {
        if( target->isBlank() )
            break;

        target->hilite(true);
        if( orientation == AcrossLiteClue::Across )
            target = getCell( target->row(), target->column() + 1 );
        else
            target = getCell( target->row() + 1, target->column() );
    }
}
