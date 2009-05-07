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

#include "AcrossLitePuzzle.h"

#include <fcntl.h>
#include <string.h>




AcrossLitePuzzle::AcrossLitePuzzle( const string& filename )
{
    load( filename );
}

AcrossLitePuzzle::~AcrossLitePuzzle()
{
}

ostream& operator<< ( ostream& os, const AcrossLitePuzzle& rhs )
{
    os << "N Columns = "  << rhs.nColumns() << endl;
    os << "N Rows    = "  << rhs.nRows()    << endl << endl;
    os << "Diagram Grid"  << endl << rhs._diagram   << endl;
    os << "Solution Grid" << endl << rhs._solution  << endl;

    return os;
}

int AcrossLitePuzzle::nColumns() const
{
    return _diagram.nColumns();
}

int AcrossLitePuzzle::nRows() const
{
    return _diagram.nRows();
}

int AcrossLitePuzzle::diagramCell( const int column, const int row ) const
{
    return _diagram.cell( column, row );
}

int AcrossLitePuzzle::solutionCell( const int column, const int row ) const
{
    return _solution.cell( column, row );
}

int AcrossLitePuzzle::cellNumber( const int column, const int row ) const
{
    return ( int )_numbers.cell( column, row );
}

int AcrossLitePuzzle::index( const int column, const int row ) const
{
    int i = column + ( row * nColumns() );

    return i;
}

void AcrossLitePuzzle::setDiagramCell( const int column, const int row, const int letter )
{
    _diagram.setCell( column, row, letter );
}

AcrossLiteClues::const_iterator AcrossLitePuzzle::beginAcrossClue() const
{
    return _acrossClues.begin();
}

AcrossLiteClues::const_iterator AcrossLitePuzzle::endAcrossClue() const
{
    return _acrossClues.end();
}

AcrossLiteClues::const_iterator AcrossLitePuzzle::beginDownClue() const
{
    return _downClues.begin();
}

AcrossLiteClues::const_iterator AcrossLitePuzzle::endDownClue() const
{
    return _downClues.end();
}

const string& AcrossLitePuzzle::puzzleName() const
{
    return _puzzleName;
}

const string& AcrossLitePuzzle::authorName() const
{
    return _authorName;
}

const string& AcrossLitePuzzle::copyright() const
{
    return _copyright;
}

const AcrossLiteGrid& AcrossLitePuzzle::diagram() const
{
    return _diagram;
}

const AcrossLiteGrid& AcrossLitePuzzle::solution() const
{
    return _solution;
}

const AcrossLiteGrid& AcrossLitePuzzle::numbers() const
{
    return _numbers;
}

const AcrossLiteClues& AcrossLitePuzzle::acrossClues() const
{
    return _acrossClues;
}

const AcrossLiteClues& AcrossLitePuzzle::downClues() const
{
    return _downClues;
}

void AcrossLitePuzzle::load( const string& filename )
{

    _init();

    //
    // Open the file.
    //
    int fh = ::open( filename.c_str(), O_RDONLY );
    if ( fh < 0 )
    {
        return;
    }

    //
    // Read the header.
    //
    int stat = ::read( fh, &_header, sizeof( AcrossLitePuzHeader ) );
    if ( stat != sizeof( AcrossLitePuzHeader ) )
    {
        return;
    }

    _solution.resize( _header._nColumns, _header._nRows );
    _diagram.resize( _header._nColumns, _header._nRows );
    _numbers.resize( _header._nColumns, _header._nRows );

    if ( nColumns() < 1 || nColumns() > 25 )
    {
        return;
    }

    if ( nRows() < 1 || nRows() > 25 )
    {
        return;
    }

    //
    // Read the the Solution and populate the Solution grid.
    //
    for ( int r = 0; r < nRows(); r++ )
    {
        for ( int c = 0; c < nColumns(); c++ )
        {
            char letter;
            stat = ::read( fh, &letter, 1 );
            if ( stat != 1 )
            {
                return;
            }

            _solution.setCell( c, r, letter );
        }
    }

    //
    // Read the the Diagram and populate the Diagram grid.
    //
    for ( int r = 0; r < nRows(); r++ )
    {
        for ( int c = 0; c < nColumns(); c++ )
        {
            char letter;
            stat = ::read( fh, &letter, 1 );
            if ( stat != 1 )
            {
                return;
            }

            if ( letter == '-' ) letter = ' ';

            _diagram.setCell( c, r, letter );
        }
    }

    //
    // Calculate the cell numbers.
    //
    _calculateCellNumbers();

    //
    // Read puzzle name, author, and copyright.
    //
    _puzzleName = _readString( fh );
    _authorName = _readString( fh );
    _copyright  = _readString( fh );

    //
    // Read the clues.
    //
    for ( int r = 0; r < nRows(); r++ )
    {
        for ( int c = 0; c < nColumns(); c++ )
        {
            int number = cellNumber( c, r );
            if ( number == 0 ) continue;

            // Try an 'across'
            if ( c == 0 || diagramCell( c - 1, r ) == '.' )
            {
                string clueText = _readString( fh );
                if ( clueText.size() == 0 )
                {
                    cout << "Unexepected EOF while reading clues." << endl;
                }

                AcrossLiteClue c( number, clueText );
                _acrossClues.push_back( c );
            }

            // Try a 'down'
            if ( r == 0 || diagramCell( c, r - 1 ) == '.' )
            {
                string clueText = _readString( fh );
                if ( clueText.size() == 0 )
                {
                    cout << "Unexepected EOF while reading clues." << endl;
                }

                AcrossLiteClue c( number, clueText );
                _downClues.push_back( c );
            }
        }
    }

    //
    // Close the file.
    //
    stat = ::close( fh );
    if ( stat < 0 )
    {
        return;
    }
}

void AcrossLitePuzzle::save( const string& filename )
{

    // Create the file.
    int fh = ::creat( filename.c_str(), 0666 );
    if ( fh < 0 )
    {
        return;
    }

    // Write the header.
    int stat = ::write( fh, &_header, sizeof( AcrossLitePuzHeader ) );
    if ( stat != sizeof( AcrossLitePuzHeader ) )
    {
        return;
    }

    // Write the the Solution.
    for ( int r = 0; r < nRows(); r++ )
    {
        for ( int c = 0; c < nColumns(); c++ )
        {

            char letter = _solution.cell( c, r );

            stat = ::write( fh, &letter, 1 );
            if ( stat != 1 )
            {
                return;
            }
        }
    }

    // Write the the Diagram.
    for ( int r = 0; r < nRows(); r++ )
    {
        for ( int c = 0; c < nColumns(); c++ )
        {

            char letter = _diagram.cell( c, r );

            if ( letter == ' ' ) letter = '-';

            stat = ::write( fh, &letter, 1 );
            if ( stat != 1 )
            {
                return;
            }
        }
    }

    // Write the puzzle name, author, and copyright.
    _writeString( fh, _puzzleName );
    _writeString( fh, _authorName );
    _writeString( fh, _copyright );

    // Write the clues.
    int acrossIndex = 0;
    int downIndex   = 0;
    for ( int r = 0; r < nRows(); r++ )
    {
        for ( int c = 0; c < nColumns(); c++ )
        {
            int number = cellNumber( c, r );
            if ( number == 0 ) continue;

            // Try an 'across'
            if ( c == 0 || diagramCell( c - 1, r ) == '.' )
            {
                string clueText = _acrossClues[acrossIndex].clue();
                _writeString( fh, clueText );
                acrossIndex++;
            }

            // Try a 'down'
            if ( r == 0 || diagramCell( c, r - 1 ) == '.' )
            {
                string clueText = _downClues[downIndex].clue();
                _writeString( fh, clueText );
                downIndex++;
            }
        }
    }

    // Close the file.
    stat = ::close( fh );
    if ( stat < 0 )
    {
        return;
    }
}

void AcrossLitePuzzle::copy( const AcrossLitePuzzle& rhs )
{
    _diagram        = rhs.diagram();
    _solution       = rhs.solution();
    _numbers        = rhs.numbers();
    _acrossClues    = rhs.acrossClues();
    _downClues      = rhs.downClues();

    _puzzleName     = rhs.puzzleName();
    _authorName     = rhs.authorName();
    _copyright      = rhs.copyright();

    _header._nColumns = rhs.nColumns();
    _header._nRows    = rhs.nRows();
}

void AcrossLitePuzzle::_init()
{
    memset( &_header, 0, sizeof( AcrossLitePuzHeader ) );

    _diagram.resize( 0, 0 );
    _solution.resize( 0, 0 );
    _numbers.resize( 0, 0 );

    _acrossClues.resize( 0 );
    _downClues.resize( 0 );

    _puzzleName = "";
    _authorName = "";
    _copyright  = "";
}

void AcrossLitePuzzle::_calculateCellNumbers()
{
    _numbers.resize( nColumns(), nRows() );

    int number = 1;

    for ( int r = 0; r < nRows(); r++ )
    {
        for ( int c = 0; c < nColumns(); c++ )
        {
            if ( diagramCell( c, r ) == '.' ) continue;

            if ( r == 0 || c == 0 )
            {
                _numbers.setCell( c, r, number++ );

            }
            else if ( diagramCell( c, r - 1 ) == '.' )
            {
                _numbers.setCell( c, r, number++ );

            }
            else if ( diagramCell( c - 1, r ) == '.' )
            {
                _numbers.setCell( c, r, number++ );

            }
            else
            {
                _numbers.setCell( c, r, 0 );
            }
        }
    }
}

string AcrossLitePuzzle::_readString( int fh )
{
    string s;

    while ( 1 )
    {
        char letter;
        int  stat = ::read( fh, &letter, 1 );
        if ( stat   != 1 ) break;
        if ( letter == 0 ) break;

        s += letter;
    }

    return s;
}

void AcrossLitePuzzle::_writeString( int fh, const string& text )
{

    char letter;

    for ( unsigned int i = 0; i < text.length(); i++ )
    {
        letter = text[i];
        int  stat = ::write( fh, &letter, 1 );
        if ( stat   != 1 ) break;
    }

    letter = '\0';
    ::write( fh, &letter, 1 );
}
