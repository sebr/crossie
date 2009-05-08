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

    connect( this, SIGNAL( currentItemChanged(QTableWidgetItem*, QTableWidgetItem*) ),
             this, SLOT  ( currentCellChanged(QTableWidgetItem*, QTableWidgetItem*) ) );
}

CrosswordGrid::~CrosswordGrid()
{
}

CrosswordCell *CrosswordGrid::getCell( const int row, const int col ) const
{
    return dynamic_cast<CrosswordCell*>( item( row, col ) );
}

void CrosswordGrid::currentCellChanged( QTableWidgetItem *current, QTableWidgetItem *previous )
{
    Q_UNUSED( previous )
    CrosswordCell *cell = dynamic_cast<CrosswordCell*>( current );
    if( cell && !cell->isBlank() && !cell->isSolutionRevealed() )
        editItem( current );
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
            cell->setColRowLabel( col, row );
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

//void CrosswordGrid::keyPressEvent( QKeyEvent* e )
//{
//    QString letter = e->text().upper();
//
//    // cout << "Grid - Key pressed: " << letter.ascii() << endl;
//
//    CrosswordCell* cell = focusCell();
//    if ( cell )
//    {
//        if ( e->key() == Key_Right )
//        {
//            if ( focusOrientation() == CrosswordGrid::FocusHorizontal )
//            {
//                setFocusCell( cell->colLabel() + 1, cell->rowLabel() );
//            }
//            else
//            {
//                setFocusOrientation( CrosswordGrid::FocusHorizontal );
//            }
//
//        }
//        else if ( e->key() == Key_Left )
//        {
//            if ( focusOrientation() == CrosswordGrid::FocusHorizontal )
//            {
//                setFocusCell( cell->colLabel() - 1, cell->rowLabel() );
//            }
//            else
//            {
//                setFocusOrientation( CrosswordGrid::FocusHorizontal );
//            }
//
//        }
//        else if ( e->key() == Key_Up )
//        {
//            if ( focusOrientation() == CrosswordGrid::FocusVertical )
//            {
//                setFocusCell( cell->colLabel(), cell->rowLabel() - 1 );
//            }
//            else
//            {
//                setFocusOrientation( CrosswordGrid::FocusVertical );
//            }
//
//        }
//        else if ( e->key() == Key_Down )
//        {
//            if ( focusOrientation() == CrosswordGrid::FocusVertical )
//            {
//                setFocusCell( cell->colLabel(), cell->rowLabel() + 1 );
//            }
//            else
//            {
//                setFocusOrientation( CrosswordGrid::FocusVertical );
//            }
//
//        }
//        else if ( e->key() >= Key_A && e->key() <= Key_Z )
//        {
//            cell->setGuess( letter.ascii()[0] );
//
//            advanceFocusCell();
//
//        }
//        else if ( e->key() == Key_Space )
//        {
//            cell->setGuess( ' ' );
//
//            advanceFocusCell();
//
//        }
//        else if ( e->key() == Key_Delete || e->key() == Key_BackSpace )
//        {
//            cell->setGuess( ' ' );
//
//            advanceFocusCell( -1 );
//        }
//    }
//}

//void CrosswordGrid::mousePressEvent( QMouseEvent* e )
//{
//    hiliteFullSolution( false );
//
//    if ( e->button() == Qt::RightButton )
//    {
//        if ( focusOrientation() == CrosswordGrid::FocusHorizontal )
//            setFocusOrientation( CrosswordGrid::FocusVertical );
//        else if ( focusOrientation() == CrosswordGrid::FocusVertical )
//            setFocusOrientation( CrosswordGrid::FocusHorizontal );
//    }
//
//    hiliteSolution( true );
//
//    QTableWidgetItem::mousePressEvent( e );
//}

bool CrosswordGrid::eventFilter( QObject* o, QEvent* e )
{
//    if ( e->type() == QEvent::KeyPress )    // key press
//    {
//        QKeyEvent* k = ( QKeyEvent* )e;
//        switch ( k->key() )
//        {
//        case Key_Left:
//        case Key_Right:
//        case Key_Up:
//        case Key_Down:
//        case Key_Delete:
//        case Key_BackSpace:
//            keyPressEvent( k );
//            return TRUE;  // eat event
//            break;
//        default:
//            if ( k->key() >= Key_A && k->key() <= Key_Z )
//            {
//                keyPressEvent( k );
//                return TRUE;
//            }
//            break;
//        }
//
//    }
//    else if ( e->type() == QEvent::MouseButtonPress )    // mouse press
//    {
//        QMouseEvent* m = ( QMouseEvent* )e;
//        switch ( m->button() )
//        {
//        case RightButton:
//        case LeftButton:
//        {
//            mousePressEvent( m );
//
//            CrosswordCell* cell = focusCell();
//            if ( cell )
//            {
//                setFocusCell( cell->colLabel(), cell->rowLabel() );
//            }
//
//            return TRUE; // eat event
//        }
//
//        break;
//
//        default:
//            break;
//        }
//    }
//
    return QWidget::eventFilter( o, e );    // standard event processing
}


CrosswordCell* CrosswordGrid::cell( const int number )
{
//    QObjectList*  l = queryList( "QWidget", "CrosswordCell" );
//    QObjectListIt it( *l );
//    QObject*      obj;
//
//    while (( obj = it.current() ) != 0 )
//    {
//        CrosswordCell* cell = ( CrosswordCell* )obj;
//        if ( cell->number() == number )
//        {
//            return cell;
//        }
//        ++it;
//    }
//
//    return 0;
}


void CrosswordGrid::setFocusCell( const int col, const int row )
{
    hiliteSolution( false );

    CrosswordCell* cell = dynamic_cast<CrosswordCell*>( item( col, row ) );
    if ( cell )
    {
        hiliteSolution( true );

        emit colFocused( col );
        emit rowFocused( row );
        emit colRowFocused( col, row );
    }
}

void CrosswordGrid::setFocusCell( AcrossLiteClue::Orientation o, int number )
{
//    hiliteFullSolution( false );
//
//    CrosswordCell* c = cell( number );
//    if ( c )
//    {
//        setFocusCell( c->colLabel(), c->rowLabel() );
//
//        if ( o == AcrossLiteClue::Across )
//        {
//            setFocusOrientation( CrosswordGrid::FocusHorizontal );
//        }
//        else if ( o == AcrossLiteClue::Down )
//        {
//            setFocusOrientation( CrosswordGrid::FocusVertical );
//        }
//        else
//        {
//            setFocusOrientation( CrosswordGrid::FocusUnknown );
//        }
//
//        hiliteSolution( true );
//    }
}

void CrosswordGrid::advanceFocusCell( const int count )
{
//    CrosswordCell* c = focusCell();
//    if ( c == 0 ) return;
//
//    int col = c->colLabel();
//    int row = c->rowLabel();
//
//    if ( focusOrientation() == CrosswordGrid::FocusVertical )
//    {
//        CrosswordCell* cx = cell( col, row + count );
//        if ( cx == 0 ) return;
//        if ( cx->isBlank() ) return;
//
//        setFocusCell( col, row + count );
//
//    }
//    else if ( focusOrientation() == CrosswordGrid::FocusHorizontal )
//    {
//        CrosswordCell* cx = cell( col + count, row );
//        if ( cx == 0 ) return;
//        if ( cx->isBlank() ) return;
//
//        setFocusCell( col + count, row );
//    }
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

    int col = c->colLabel(); // Get current col/row.
    int row = c->rowLabel();

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
    switch( event->key() )
    {
        case Qt::Key_Up:
            setCurrentCell( currentRow() - 1, currentColumn() );
            break;
        case Qt::Key_Down:
            setCurrentCell( currentRow() + 1, currentColumn() );
            break;
        case Qt::Key_Right:
        case Qt::Key_Tab:
            setCurrentCell( currentRow(), currentColumn() + 1);
            break;
        case Qt::Key_Left:
        case Qt::Key_Backtab:
            setCurrentCell( currentRow(), currentColumn() - 1 );
            break;
        default:
            QTableWidget::keyPressEvent( event );
    }
}

