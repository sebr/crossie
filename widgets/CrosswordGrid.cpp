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

CrosswordGrid::CrosswordGrid( QWidget* parent, char* name ) : QWidget( parent, name )
{
    m_gridLayout       = 0;
    m_puzzle           = 0;
    m_focusOrientation = FocusHorizontal;

    setBackgroundColor( "white" );
}

CrosswordGrid::CrosswordGrid( AcrossLitePuzzleBase* puzzle, QWidget* parent, char* name ) : QWidget( parent, name )
{
    m_gridLayout       = 0;
    m_puzzle           = 0;
    m_focusOrientation = FocusHorizontal;

    setBackgroundColor( "white" );

    setPuzzle( puzzle );
}

CrosswordGrid::~CrosswordGrid()
{
}

void CrosswordGrid::setPuzzle( AcrossLitePuzzleBase* puzzle )
{
    if ( _gridLayout )
    {
        delete m_gridLayout;
        m_gridLayout = 0;
    }

    while ( _cells.size() > 0 )
    {
        CrosswordCell* w = m_cells.back();
        delete w;
        m_cells.pop_back();
    }

    m_gridLayout       = new QGridLayout( this, 1, 1 );
    m_puzzle           = puzzle;
    m_focusOrientation = FocusHorizontal;

    for ( int r = 0; r < _puzzle->nRows(); r++ )
    {
        for ( int c = 0; c < _puzzle->nColumns(); c++ )
        {
            CrosswordCell* w = new CrosswordCell( this );
            w->setColRowLabel( c, r );
            w->setSolution( _puzzle->solutionCell( c, r ) );
            w->setShowCorrectness( false );
            // w->setGuess(' ');
            w->setGuess( _puzzle->diagramCell( c, r ) );
            w->setNumber( _puzzle->cellNumber( c, r ) );
            w->showNumber( true );
            w->setFocusPolicy( QWidget::ClickFocus );
            w->show();

            w->installEventFilter( this ); // then install filter

            m_gridLayout->addWidget( w, r, c );

            m_cells.push_back( w );
        }
    }

    m_gridLayout->activate();
}

AcrossLitePuzzleBase* CrosswordGrid::puzzle()
{
    return m_puzzle;
}

void CrosswordGrid::savePuzzle( const QString& filename )
{
    if ( _puzzle == 0 ) return;

    QString f = filename;

    if ( f.contains( '.' ) == false )
    {
        f += ".puz";
    }

    int indx = f.findRev( '.' );

    QString sub = f.mid( indx );

    if ( sub != QString( ".puz" ) )
    {
        QMessageBox::warning( this, "KrossWordPlayer", "Trying to save to a file with a '" + sub + "' extension\nwhen it should be a '.puz' extension." );
        return;
    }

    AcrossLitePuzPuzzle puz;
    puz.copy( *_puzzle );

    QObjectList*  l = queryList( "QWidget", "CrosswordCell" );
    QObjectListIt it( *l );
    QObject*      obj;

    while (( obj = it.current() ) != 0 )
    {
        CrosswordCell* cel = ( CrosswordCell* )obj;

        if ( cel->solution() != '.' )
        {
            int letter = cel->guess();
            puz.setDiagramCell( cel->colLabel(), cel->rowLabel(), letter );
        }

        ++it;
    }


    puz.save( f.ascii() );
}

void CrosswordGrid::revealSolution( const bool flag )
{
    QObjectList*  l = queryList( "QWidget", "CrosswordCell" );
    QObjectListIt it( *l );
    QObject*      obj;

    while (( obj = it.current() ) != 0 )
    {
        (( CrosswordCell* )obj )->revealSolution( flag );
        ++it;
    }
}

void CrosswordGrid::revealWord( const bool flag )
{
    QObjectList*  l = queryList( "QWidget", "CrosswordCell" );
    QObjectListIt it( *l );
    QObject*      obj;

    while (( obj = it.current() ) != 0 )
    {
        CrosswordCell* cell = ( CrosswordCell* )obj;
        if ( cell->isHilited() )
        {
            cell->revealSolution( flag );
        }
        ++it;
    }
}

void CrosswordGrid::revealLetter( const bool flag )
{
    CrosswordCell* cell = focusCell();
    if ( cell != 0 && cell->isHilited() )
    {
        cell->revealSolution( flag );
    }
}

void CrosswordGrid::uncheckSolution()
{
    QObjectList*  l = queryList( "QWidget", "CrosswordCell" );
    QObjectListIt it( *l );
    QObject*      obj;

    while (( obj = it.current() ) != 0 )
    {
        (( CrosswordCell* )obj )->setShowCorrectness( false );
        ++it;
    }
}

void CrosswordGrid::checkSolution()
{
    QObjectList*  l = queryList( "QWidget", "CrosswordCell" );
    QObjectListIt it( *l );
    QObject*      obj;

    while (( obj = it.current() ) != 0 )
    {
        (( CrosswordCell* )obj )->setShowCorrectness( true );
        ++it;
    }
}

void CrosswordGrid::checkWord()
{
    QObjectList*  l = queryList( "QWidget", "CrosswordCell" );
    QObjectListIt it( *l );
    QObject*      obj;

    while (( obj = it.current() ) != 0 )
    {
        CrosswordCell* cell = ( CrosswordCell* )obj;
        if ( cell->isHilited() )
        {
            cell->setShowCorrectness( true );
        }
        ++it;
    }
}

void CrosswordGrid::checkLetter()
{
    CrosswordCell* cell = focusCell();
    if ( cell != 0 && cell->isHilited() )
    {
        cell->setShowCorrectness( true );
    }
}

QSize CrosswordGrid::sizeHint() const
{
    return QSize( 20, 20 );
}

QSizePolicy CrosswordGrid::sizePolicy() const
{
    return QSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred, true );
}

QSize CrosswordGrid::minimumSizeHint() const
{
    return QSize( 20, 20 );
}

void CrosswordGrid::keyPressEvent( QKeyEvent* e )
{
    QString letter = e->text().upper();

    // cout << "Grid - Key pressed: " << letter.ascii() << endl;

    CrosswordCell* cell = focusCell();
    if ( cell )
    {
        if ( e->key() == Key_Right )
        {
            if ( focusOrientation() == CrosswordGrid::FocusHorizontal )
            {
                setFocusCell( cell->colLabel() + 1, cell->rowLabel() );
            }
            else
            {
                setFocusOrientation( CrosswordGrid::FocusHorizontal );
            }

        }
        else if ( e->key() == Key_Left )
        {
            if ( focusOrientation() == CrosswordGrid::FocusHorizontal )
            {
                setFocusCell( cell->colLabel() - 1, cell->rowLabel() );
            }
            else
            {
                setFocusOrientation( CrosswordGrid::FocusHorizontal );
            }

        }
        else if ( e->key() == Key_Up )
        {
            if ( focusOrientation() == CrosswordGrid::FocusVertical )
            {
                setFocusCell( cell->colLabel(), cell->rowLabel() - 1 );
            }
            else
            {
                setFocusOrientation( CrosswordGrid::FocusVertical );
            }

        }
        else if ( e->key() == Key_Down )
        {
            if ( focusOrientation() == CrosswordGrid::FocusVertical )
            {
                setFocusCell( cell->colLabel(), cell->rowLabel() + 1 );
            }
            else
            {
                setFocusOrientation( CrosswordGrid::FocusVertical );
            }

        }
        else if ( e->key() >= Key_A && e->key() <= Key_Z )
        {
            cell->setGuess( letter.ascii()[0] );

            advanceFocusCell();

        }
        else if ( e->key() == Key_Space )
        {
            cell->setGuess( ' ' );

            advanceFocusCell();

        }
        else if ( e->key() == Key_Delete || e->key() == Key_BackSpace )
        {
            cell->setGuess( ' ' );

            advanceFocusCell( -1 );
        }
    }
}

void CrosswordGrid::mousePressEvent( QMouseEvent* e )
{
    hiliteFullSolution( false );

    if ( e->button() == RightButton )
    {
        if ( focusOrientation() == CrosswordGrid::FocusHorizontal )
        {
            setFocusOrientation( CrosswordGrid::FocusVertical );
        }
        else if ( focusOrientation() == CrosswordGrid::FocusVertical )
        {
            setFocusOrientation( CrosswordGrid::FocusHorizontal );
        }
    }

    hiliteSolution( true );
}

bool CrosswordGrid::eventFilter( QObject* o, QEvent* e )
{
    if ( e->type() == QEvent::KeyPress )    // key press
    {
        QKeyEvent* k = ( QKeyEvent* )e;
        switch ( k->key() )
        {
        case Key_Left:
        case Key_Right:
        case Key_Up:
        case Key_Down:
        case Key_Delete:
        case Key_BackSpace:
            keyPressEvent( k );
            return TRUE;  // eat event
            break;
        default:
            if ( k->key() >= Key_A && k->key() <= Key_Z )
            {
                keyPressEvent( k );
                return TRUE;
            }
            break;
        }

    }
    else if ( e->type() == QEvent::MouseButtonPress )    // mouse press
    {
        QMouseEvent* m = ( QMouseEvent* )e;
        switch ( m->button() )
        {
        case RightButton:
        case LeftButton:
        {
            mousePressEvent( m );

            CrosswordCell* cell = focusCell();
            if ( cell )
            {
                setFocusCell( cell->colLabel(), cell->rowLabel() );
            }

            return TRUE; // eat event
        }

        break;

        default:
            break;
        }
    }

    return QWidget::eventFilter( o, e );    // standard event processing
}

CrosswordCell* CrosswordGrid::focusCell()
{
    QObjectList*  l = queryList( "QWidget", "CrosswordCell" );
    QObjectListIt it( *l );
    QObject*      obj;

    while (( obj = it.current() ) != 0 )
    {
        CrosswordCell* cell = ( CrosswordCell* )obj;
        if ( cell->hasFocus() )
        {
            return cell;
        }
        ++it;
    }

    return 0;
}

CrosswordCell* CrosswordGrid::cell( const int col, const int row )
{
    QObjectList*  l = queryList( "QWidget", "CrosswordCell" );
    QObjectListIt it( *l );
    QObject*      obj;

    while (( obj = it.current() ) != 0 )
    {
        CrosswordCell* cell = ( CrosswordCell* )obj;
        if ( cell->colLabel() == col && cell->rowLabel() == row )
        {
            return cell;
        }
        ++it;
    }

    return 0;
}

CrosswordCell* CrosswordGrid::cell( const int number )
{
    QObjectList*  l = queryList( "QWidget", "CrosswordCell" );
    QObjectListIt it( *l );
    QObject*      obj;

    while (( obj = it.current() ) != 0 )
    {
        CrosswordCell* cell = ( CrosswordCell* )obj;
        if ( cell->number() == number )
        {
            return cell;
        }
        ++it;
    }

    return 0;
}


void CrosswordGrid::setFocusCell( const int col, const int row )
{
    hiliteSolution( false );

    CrosswordCell* c = cell( col, row );
    if ( c )
    {
        c->setFocus();

        hiliteSolution( true );

        emit colFocused( col );
        emit rowFocused( row );
        emit colRowFocused( col, row );
    }
}

void CrosswordGrid::setFocusCell( AcrossLiteClue::Orientation o, int number )
{
    hiliteFullSolution( false );

    CrosswordCell* c = cell( number );
    if ( c )
    {
        setFocusCell( c->colLabel(), c->rowLabel() );

        if ( o == AcrossLiteClue::Across )
        {
            setFocusOrientation( CrosswordGrid::FocusHorizontal );
        }
        else if ( o == AcrossLiteClue::Down )
        {
            setFocusOrientation( CrosswordGrid::FocusVertical );
        }
        else
        {
            setFocusOrientation( CrosswordGrid::FocusUnknown );
        }

        hiliteSolution( true );
    }
}

void CrosswordGrid::advanceFocusCell( const int count )
{
    CrosswordCell* c = focusCell();
    if ( c == 0 ) return;

    int col = c->colLabel();
    int row = c->rowLabel();

    if ( focusOrientation() == CrosswordGrid::FocusVertical )
    {
        CrosswordCell* cx = cell( col, row + count );
        if ( cx == 0 ) return;
        if ( cx->solution() == '.' ) return;

        setFocusCell( col, row + count );

    }
    else if ( focusOrientation() == CrosswordGrid::FocusHorizontal )
    {
        CrosswordCell* cx = cell( col + count, row );
        if ( cx == 0 ) return;
        if ( cx->solution() == '.' ) return;

        setFocusCell( col + count, row );
    }
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
    CrosswordCell* c = focusCell();
    if ( c == 0 ) return;

    int col = c->colLabel(); // Get current col/row.
    int row = c->rowLabel();

    if ( focusOrientation() == CrosswordGrid::FocusVertical )
    {
        // Current to top.
        for ( int r = row; ; r-- )
        {
            CrosswordCell* cx = cell( col, r );
            if ( cx == 0 ) break;
            if ( cx->solution() == '.' ) break;

            cx->hilite( flag );
        }

        // Current to bottom.
        for ( int r = row; ; r++ )
        {
            CrosswordCell* cx = cell( col, r );
            if ( cx == 0 ) break;
            if ( cx->solution() == '.' ) break;

            cx->hilite( flag );
        }

    }
    else if ( focusOrientation() == CrosswordGrid::FocusHorizontal )
    {
        // Current to left.
        for ( int c = col; ; c-- )
        {
            CrosswordCell* cx = cell( c, row );
            if ( cx == 0 ) break;
            if ( cx->solution() == '.' ) break;

            cx->hilite( flag );
        }

        // Current to right.
        for ( int c = col; ; c++ )
        {
            CrosswordCell* cx = cell( c, row );
            if ( cx == 0 ) break;
            if ( cx->solution() == '.' ) break;

            cx->hilite( flag );
        }
    }
}

void CrosswordGrid::hiliteFullSolution( const bool flag )
{
    QObjectList*  l = queryList( "QWidget", "CrosswordCell" );
    QObjectListIt it( *l );
    QObject*      obj;

    while (( obj = it.current() ) != 0 )
    {
        CrosswordCell* cell = ( CrosswordCell* )obj;
        if ( cell->isHilited() != flag )
        {
            cell->hilite( flag );
        }
        ++it;
    }
}

void CrosswordGrid::colRowToDownAcross( const int col, const int row,  int& down, int& across )
{
    down = across = -1;

    // Find nearest down solution number.
    int r = row;
    CrosswordCell* downCell = cell( col, r );
    while ( downCell )
    {
        if ( downCell->solution() == '.' ) break;

        down = downCell->number();

        downCell = cell( col, --r );
    }

    // Find nearest across solution number.
    int c = col;
    CrosswordCell* acrossCell = cell( c, row );
    while ( acrossCell )
    {
        if ( acrossCell->solution() == '.' ) break;

        across = acrossCell->number();

        acrossCell = cell( --c, row );
    }
}

