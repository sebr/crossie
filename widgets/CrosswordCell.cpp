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

#include <QColor>

CrosswordCell::CrosswordCell()
    : QTableWidgetItem()
    , m_colLabel( 0 )
    , m_rowLabel( 0 )
    , m_solution( '.' )
    , m_guess()
    , m_isSolutionRevealed( false )
    , m_showCorrectness( false )
    , m_number( 0 )
    , m_isNumberShown( false )
    , m_isHilited( false )
{
    setFlags();
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
                return m_solution;
            return m_guess;
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
            return Qt::white;
        }
        default:
            break;
    }
    return QTableWidgetItem::data( role );
}

void CrosswordCell::setFlags()
{
    if( isBlank() )
        QTableWidgetItem::setFlags( Qt::NoItemFlags );
    else
        QTableWidgetItem::setFlags( Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled );
}

QSize CrosswordCell::sizeHint() const
{
    return QSize( 20, 20 );
}

QSizePolicy CrosswordCell::sizePolicy() const
{
    return QSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
}

void CrosswordCell::setSolution( const QChar &letter )
{
    m_solution = letter;
    setFlags();
}

void CrosswordCell::setColRowLabel( const int col, const int row )
{
    m_colLabel = col;
    m_rowLabel = row;
}

int CrosswordCell::colLabel() const
{
    return m_colLabel;
}

int CrosswordCell::rowLabel() const
{
    return m_rowLabel;
}

void CrosswordCell::setGuess( const QChar &letter )
{
    setShowCorrectness( false );

    // Don't change guess if cell is revealed.
    if ( isSolutionRevealed() )
        return;

    m_guess = letter;
}

QChar CrosswordCell::solution() const
{
    return m_solution;
}

QChar CrosswordCell::guess() const
{
    return m_guess;
}

void CrosswordCell::revealSolution( const bool flag )
{
    m_isSolutionRevealed = flag;

    if ( flag )
        setShowCorrectness( false );
}

bool CrosswordCell::isSolutionRevealed() const
{
    return m_isSolutionRevealed;
}

bool CrosswordCell::showCorrectness() const
{
    return m_showCorrectness;
}

void CrosswordCell::setShowCorrectness( const bool flag )
{
    m_showCorrectness = flag;
}

bool CrosswordCell::isSolutionCorrect() const
{
    return m_solution == m_guess;
}

void CrosswordCell::setNumber( const int number )
{
    m_number = number;

    if ( m_number == 0 )
        showNumber( false );
}

int CrosswordCell::number() const
{
    return m_number;
}

void CrosswordCell::showNumber( const bool flag )
{
    if ( m_number == 0 )
    {
        m_isNumberShown = false;
        return;
    }

    m_isNumberShown = flag;
}

bool CrosswordCell::isNumberShown() const
{
    return m_isNumberShown;
}

void CrosswordCell::hilite( const bool flag )
{
    m_isHilited = flag;
}

bool CrosswordCell::isHilited() const
{
    return m_isHilited;
}
