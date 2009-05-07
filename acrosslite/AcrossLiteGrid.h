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

#ifndef ACROSSLITEGRID_H
#define ACROSSLITEGRID_H

#include "AcrossLiteClue.h"
#include "AcrossLiteGrid.h"

using namespace std;

#include <vector>
#include <string>
#include <iostream>

class AcrossLiteGrid
{
public:
    AcrossLiteGrid();
    AcrossLiteGrid( const int nColumns, const int nRows );
    AcrossLiteGrid( const AcrossLiteGrid& src );
    ~AcrossLiteGrid();

    AcrossLiteGrid& operator= ( const AcrossLiteGrid& rhs );
    friend ostream& operator<< ( ostream& os, const AcrossLiteGrid& rhs );

    void            resize( const int nColumns, const int nRows );
    int             nColumns() const;
    int             nRows() const;

    int             cell( const int column, const int row ) const;
    void            setCell( const int column, const int row, const int letter );
    int             index( const int column, const int row ) const;

private:
    int             _nColumns;
    int             _nRows;
    vector<int>     _cells;
};

#endif // ACROSSLITEGRID_H
