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

#ifndef ACROSSLITEPUZZLE_H
#define ACROSSLITEPUZZLE_H

#include "AcrossLiteClue.h"
#include "AcrossLiteGrid.h"

using namespace std;

#include <vector>
#include <string>
#include <iostream>

struct AcrossLitePuzHeader
{
    char          _junk1[44];
    unsigned char _nColumns;
    unsigned char _nRows;
    char          _junk2[6];
};

class AcrossLitePuzzle
{
    public:
        AcrossLitePuzzle( const string& filename );
        ~AcrossLitePuzzle();

        friend ostream& operator<< ( ostream& os, const AcrossLitePuzzle& rhs );

        void load( const string& filename );
        void save( const string& filename );
        void copy( const AcrossLitePuzzle& puzzle );

        int  nColumns() const;
        int  nRows() const;

        int  diagramCell( const int column, const int row ) const;
        int  solutionCell( const int column, const int row ) const;
        int  cellNumber( const int column, const int row ) const;
        int  index( const int column, const int row ) const;
        void setDiagramCell( const int column, const int row, const int letter );

        AcrossLiteClues::const_iterator beginAcrossClue() const;
        AcrossLiteClues::const_iterator endAcrossClue() const;

        AcrossLiteClues::const_iterator beginDownClue() const;
        AcrossLiteClues::const_iterator endDownClue() const;

        const string& puzzleName() const;
        const string& authorName() const;
        const string& copyright() const;

        const AcrossLiteGrid&  diagram() const;
        const AcrossLiteGrid&  solution() const;
        const AcrossLiteGrid&  numbers() const;
        const AcrossLiteClues& acrossClues() const;
        const AcrossLiteClues& downClues() const;

    private:
        void   _init();
        void   _calculateCellNumbers();
        string _readString( int fh );
        void   _writeString( int fh, const string& text );

        AcrossLiteGrid  _diagram;
        AcrossLiteGrid  _solution;
        AcrossLiteGrid  _numbers;
        AcrossLiteClues _acrossClues;
        AcrossLiteClues _downClues;

        string _puzzleName;
        string _authorName;
        string _copyright;

        AcrossLitePuzHeader _header;
};


#endif // ACROSSLITEPUZZLE_H
