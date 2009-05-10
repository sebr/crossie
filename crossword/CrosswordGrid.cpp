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
#include "CrosswordCellDelegate.h"

#include <QHeaderView>
#include <QMouseEvent>

CrosswordGrid::CrosswordGrid( QWidget* parent )
    : QTableWidget( parent )
    , m_puzzle( 0 )
    , m_focusOrientation( FocusHorizontal )
    , m_selectedNumber( 0 )
{
    setEditTriggers( QAbstractItemView::NoEditTriggers );
    setSelectionMode( QAbstractItemView::SingleSelection );
    setSortingEnabled( false );

    setItemDelegate( new CrosswordCellDelegate(this) );

    horizontalHeader()->hide();
    verticalHeader()->hide();
    
    connect( this, SIGNAL( currentCellChanged(int, int, int, int) ),
             this, SLOT  ( cellSelectedChanged() ) );
}

CrosswordGrid::~CrosswordGrid()
{
}

bool CrosswordGrid::isOutOfBounds( const int row, const int col ) const
{
    return ( row >= rowCount() || col >= columnCount() || row < 0 || col < 0 );
}

CrosswordCell *CrosswordGrid::getCell( const int row, const int col ) const
{
    // Check bounds conditions
    if( isOutOfBounds( row, col ) )
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
        if( cell->isHighlighted() )
            cell->revealSolution( flag );
    }
}

void CrosswordGrid::revealLetter( const bool flag )
{
    CrosswordCell* cell = dynamic_cast<CrosswordCell*>( currentItem() );
    if( cell->isHighlighted() )
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
        if( cell->isHighlighted() )
            cell->setShowCorrectness( true );
    }
}

void CrosswordGrid::checkLetter()
{
    CrosswordCell* cell = dynamic_cast<CrosswordCell*>( currentItem() );
    if ( cell && cell->isHighlighted() )
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

bool CrosswordGrid::isBlankCell( const int row, const int col ) const
{
    const CrosswordCell *cell = getCell( row, col );
    return cell ? cell->isBlank() : false;
}

CrosswordGrid::FocusOrientation CrosswordGrid::cellOrientation( const CrosswordCell *cell ) const
{
    if( !cell )
        return FocusUnknown;

    const int col = cell->column();
    const int row = cell->row();

    bool isAcross = false;
    bool isDown = false;

    if( !isBlankCell(row, col - 1) || !isBlankCell(row, col + 1) )
        isAcross = true;

    if( !isBlankCell(row - 1, col) || !isBlankCell(row + 1, col) )
        isDown = true;

    if( isAcross && isDown )
        return FocusBoth;
    else if( isAcross )
        return FocusHorizontal;
    else if( isDown )
        return FocusVertical;

    return FocusUnknown;
}

void CrosswordGrid::highlightWord()
{
    CrosswordCell* cell = dynamic_cast<CrosswordCell*>( currentItem() );
    if( !cell )
        return;

    cell->highlight(true);
    int col = cell->column();
    int row = cell->row();

    if ( m_focusOrientation == CrosswordGrid::FocusVertical )
    {
        // Current to top.
        for ( int r = row; ; r-- )
        {
            CrosswordCell* cx = getCell( r, col );
            if( !cx || cx->isBlank() )
                break;

            cx->highlight(true);
        }

        // Current to bottom.
        for ( int r = row; ; r++ )
        {
            CrosswordCell* cx = getCell( r, col );
            if( !cx || cx->isBlank() )
                break;

            cx->highlight(true);
        }

    }
    else if ( m_focusOrientation == CrosswordGrid::FocusHorizontal )
    {
        // Current to left.
        for ( int c = col; ; c-- )
        {
            CrosswordCell* cx = getCell( row, c );
            if( !cx || cx->isBlank() )
                break;

            cx->highlight(true);
        }

        // Current to right.
        for ( int c = col; ; c++ )
        {
            CrosswordCell* cx = getCell( row, c );
            if( !cx || cx->isBlank() )
                break;

            cx->highlight(true);
        }
    }
}

void CrosswordGrid::clearHighlights()
{
    foreach( CrosswordCell *cell, getCells() )
        cell->highlight( false );
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
    CrosswordCell *item = dynamic_cast<CrosswordCell*>( currentItem() );
    if( item )
    {
        if( (QChar(event->key()) >= 'a' && QChar(event->key()) <= 'z') ||
            (QChar(event->key()) >= 'A' && QChar(event->key()) <= 'Z') )
        {
            item->setGuess( QChar(event->key()) );

            // The fake event allows us to gracefully handle moving to the next
            // square as if it were a key press
            if( focusOrientation() == CrosswordGrid::FocusHorizontal )
            {
                QKeyEvent *fakeEvent = new QKeyEvent( event->type(), (int)Qt::Key_Right, event->modifiers() );
                handleArrowKey( fakeEvent, item );
            }
            else
            {
                QKeyEvent *fakeEvent = new QKeyEvent( event->type(), (int)Qt::Key_Down, event->modifiers() );
                handleArrowKey( fakeEvent, item );
            }
            return;
        }

        if( event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete )
        {
            if( item->hasGuess() )
                item->clearGuess();

            if( event->key() == Qt::Key_Backspace )
            {
                if( focusOrientation() == CrosswordGrid::FocusHorizontal )
                {
                    QKeyEvent *fakeEvent = new QKeyEvent( event->type(), (int)Qt::Key_Left, event->modifiers() );
                    handleArrowKey( fakeEvent, item );
                }
                else
                {
                    QKeyEvent *fakeEvent = new QKeyEvent( event->type(), (int)Qt::Key_Up, event->modifiers() );
                    handleArrowKey( fakeEvent, item );
                }
            }
        }
    }

    if( handleArrowKey(event, item) )
        return;

    QTableWidget::keyPressEvent( event );
}

/**
  * Skips blank squares and moves to the next/prev col/row if necessary
  */
bool CrosswordGrid::handleArrowKey( QKeyEvent *event, CrosswordCell *item )
{
    const bool isUp    = event->key() == Qt::Key_Up;
    const bool isDown  = event->key() == Qt::Key_Down;
    const bool isRight = event->key() == Qt::Key_Right;
    const bool isLeft  = event->key() == Qt::Key_Left;

    if( !item || !(isUp || isDown || isRight || isLeft) )
        return false;

    int row = item->row();
    int col = item->column();

    CrosswordCell *nextItem = item;

    while( nextItem )
    {
        if( row == 0 && col == 0 )
            return true;

        if( nextItem != item )
        {
            if( !nextItem->isBlank() )
                break;
        }

        // Left/Up direction means we move into the top left corner
        if( isUp || isLeft )
        {
            if( isUp && --row < 0 )
            {
                row = rowCount() - 1;
                --col;
            }
            else if( isLeft && --col < 0 )
            {
                col = columnCount() - 1;
                --row;
            }
        }
        // Right/Down direction means we move into the bottom right corner
        else if( isDown || isRight )
        {
            if( isDown && ++row == rowCount() )
            {
                row = 0;
                ++col;
            }
            else if( isRight && ++col == columnCount() )
            {
                col = 0;
                ++row;
            }
        }

        nextItem = getCell( row, col );
    }
    if( nextItem )
        setCurrentItem( nextItem );

    return true;
}


void CrosswordGrid::mousePressEvent( QMouseEvent *event )
{
    CrosswordCell *cell = dynamic_cast<CrosswordCell*>( itemAt( event->pos() ) );
    if( cell && cell->isBlank() )
    {
        event->accept();
        return;
    }

    if( event->button() == Qt::RightButton )
    {
        FocusOrientation orientation = cellOrientation( cell );
        if( orientation == FocusBoth )
        {
            m_focusOrientation = ( m_focusOrientation == FocusHorizontal ) ?
                                    FocusVertical : FocusHorizontal;
            clearHighlights();
            highlightWord();
        }
    }

    QTableView::mousePressEvent( event );
}

void CrosswordGrid::clueSelected( AcrossLiteClue::Orientation orientation, int clueNumber )
{
    if( orientation == AcrossLiteClue::Across )
        m_focusOrientation = FocusHorizontal;
    else if( orientation == AcrossLiteClue::Down )
        m_focusOrientation = FocusVertical;

    CrosswordCell *target = 0;
    foreach( CrosswordCell *cell, getCells() )
    {
        if( !target && cell->number() == clueNumber )
            target = cell;
        cell->highlight(false);
    }

    clearSelection();
    if( target )
    {
        setCurrentItem( target );
        target->setSelected(true);
    }

    while( target )
    {
        if( target->isBlank() )
            break;

        target->highlight(true);
        if( orientation == AcrossLiteClue::Across )
            target = getCell( target->row(), target->column() + 1 );
        else
            target = getCell( target->row() + 1, target->column() );
    }

    m_selectedNumber = clueNumber;
}

void CrosswordGrid::cellSelectedChanged()
{
    clearHighlights();

    CrosswordCell* cell = dynamic_cast<CrosswordCell*>( currentItem() );
    FocusOrientation orientation = cellOrientation( cell );

    // Change the orientation. If we are at a crossroad, then keep the last orientation
    if( orientation != FocusBoth )
        m_focusOrientation = orientation;

    highlightWord();
}

void CrosswordGrid::cellUpdated( QTableWidgetItem *item )
{
    if( item )
    {
        QModelIndex index = indexFromItem( item );
        update( index );
    }
}
