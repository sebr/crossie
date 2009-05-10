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

#include "CrosswordCell.h"
#include "CrosswordGrid.h"

#include <QColor>

CrosswordCell::CrosswordCell()
    : QTableWidgetItem()
    , m_solution( '.' )
    , m_guess()
    , m_isSolutionRevealed( false )
    , m_showCorrectness( false )
    , m_number( 0 )
    , m_isNumberShown( false )
    , m_isHighlighted( false )
{
    setTextAlignment( Qt::AlignCenter );
}

CrosswordCell::~CrosswordCell()
{
}

QVariant CrosswordCell::data( int role ) const
{
    switch( role )
    {
        case Qt::DisplayRole:
        {
            if( isBlank() )
                return QString();
            if( isSolutionRevealed() )
                return m_solution.toUpper();
            return QTableWidgetItem::data( role ).toString().toUpper();
        }
        case Qt::ForegroundRole:
        {
            if( isBlank() )
                return Qt::black;
            if( isSolutionRevealed() )
            {
                if( isSolutionCorrect() )
                    return Qt::green;
                return Qt::red;
            }
            return Qt::black;
        }
        case Qt::BackgroundRole:
        {
            if( isBlank() )
                return Qt::black;
            if( isHighlighted() )
                return Qt::yellow;
            return Qt::white;
        }
        case ClueNumberRole:
            return m_number > 0 ? QString::number( m_number ) : QString();

        default:
            break;
    }
    return QTableWidgetItem::data( role );
}

Qt::ItemFlags CrosswordCell::flags() const
{
    if( isBlank() )
        return Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

QSize CrosswordCell::sizeHint() const
{
    return QSize( cellSize(), cellSize() );
}

QSizePolicy CrosswordCell::sizePolicy() const
{
    return QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
}

void CrosswordCell::setSolution( const QChar &letter )
{
    m_solution = letter;
    updated();
}

void CrosswordCell::setGuess( const QChar &letter )
{
    setShowCorrectness( false );

    // Don't change guess if cell is revealed.
    if ( isSolutionRevealed() )
        return;

    m_guess = letter;
    updated();
}

void CrosswordCell::revealSolution( const bool flag )
{
    m_isSolutionRevealed = flag;

    if( flag )
        setShowCorrectness( false );
}

void CrosswordCell::setShowCorrectness( const bool flag )
{
    m_showCorrectness = flag;
    updated();
}

bool CrosswordCell::isSolutionCorrect() const
{
    return m_solution == m_guess;
}

void CrosswordCell::setNumber( const int number )
{
    m_number = number;

    if( m_number <= 0 )
        showNumber( false );

    updated();
}

void CrosswordCell::showNumber( const bool flag )
{
    m_isNumberShown = flag && m_number > 0;
    updated();
}

void CrosswordCell::highlight( const bool flag )
{
    m_isHighlighted = flag;
    updated();
}

void CrosswordCell::updated()
{
    if( tableWidget() )
        static_cast<CrosswordGrid*>( tableWidget() )->cellUpdated( this );
}
