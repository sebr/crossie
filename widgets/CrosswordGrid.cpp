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
    return dynamic_cast<CrosswordCell*>( item( row, col ) );
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
    qDebug() << "colWidth:" << colWidth << " rowHeight: " << rowHeight;
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
    for( int row = 0; row < rowCount(); row++ )
    {
        for( int col = 0; col < columnCount(); col++ )
        {
            CrosswordCell *cell = getCell( row, col );
            if( cell )
                cell->revealSolution( flag );
        }
    }
}

void CrosswordGrid::revealWord( const bool flag )
{
    for( int row = 0; row < rowCount(); row++ )
    {
        for( int col = 0; col < columnCount(); col++ )
        {
            CrosswordCell *cell = getCell( row, col );
            if( cell && cell->isHilited() )
                cell->revealSolution( flag );
        }
    }
}

void CrosswordGrid::revealLetter( const bool flag )
{
    CrosswordCell* cell = dynamic_cast<CrosswordCell*>( currentItem() );
    if ( cell && cell->isHilited() )
        cell->revealSolution( flag );
}

void CrosswordGrid::uncheckSolution()
{
    for( int row = 0; row < rowCount(); row++ )
    {
        for( int col = 0; col < columnCount(); col++ )
        {
            CrosswordCell *cell = getCell( row, col );
            if( cell )
                cell->setShowCorrectness( false );
        }
    }
}

void CrosswordGrid::checkSolution()
{
    for( int row = 0; row < rowCount(); row++ )
    {
        for( int col = 0; col < columnCount(); col++ )
        {
            CrosswordCell *cell = getCell( row, col );
            if( cell )
                cell->setShowCorrectness( true );
        }
    }
}

void CrosswordGrid::checkWord()
{
    for( int row = 0; row < rowCount(); row++ )
    {
        for( int col = 0; col < columnCount(); col++ )
        {
            CrosswordCell *cell = getCell( row, col );
            if( cell && cell->isHilited() )
                cell->setShowCorrectness( true );
        }
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
    return QSize( 20, 20 );
}

QSizePolicy CrosswordGrid::sizePolicy() const
{
    return QSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
}

QSize CrosswordGrid::minimumSizeHint() const
{
    return QSize( 20, 20 );
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
       for( int row = 0; row < rowCount(); row++ )
    {
        for( int col = 0; col < columnCount(); col++ )
        {
            CrosswordCell *cell = getCell( row, col );
            if( cell )
                cell->hilite( flag );
        }
    }
}

void CrosswordGrid::colRowToDownAcross( const int col, const int row,  int& down, int& across )
{
    down = across = -1;

    // Find nearest down solution number.
    int r = row;
    CrosswordCell* downCell = dynamic_cast<CrosswordCell*>( item( col, r ) );
    while( downCell )
    {
        if( downCell->isBlank() )
            break;

        down = downCell->number();

        downCell = getCell( col, --r );
    }

    // Find nearest across solution number.
    int c = col;
    CrosswordCell* acrossCell = dynamic_cast<CrosswordCell*>( item( c, row ) );
    while( acrossCell )
    {
        if( acrossCell->isBlank() )
            break;

        across = acrossCell->number();

        acrossCell = getCell( --c, row );
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

