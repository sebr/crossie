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

#ifndef ACROSSLITECLUE_H
#define ACROSSLITECLUE_H

using namespace std;

#include <vector>
#include <string>
#include <iostream>

class AcrossLiteClue
{
public:
    enum Orientation
    {
        Unknown = 0,
        Across  = 1,
        Down    = 2
    };

    AcrossLiteClue();
    AcrossLiteClue( const int number, const string& clue );
    AcrossLiteClue( const AcrossLiteClue& src );
    ~AcrossLiteClue();

    AcrossLiteClue& operator= ( const AcrossLiteClue& rhs );
    bool            operator< ( const AcrossLiteClue& rhs );
    bool            operator== ( const AcrossLiteClue& rhs );
    friend ostream& operator<< ( ostream& os, const AcrossLiteClue& rhs );

    void  set( const int number, const string& clue );
    int   number() const;
    const string& clue() const;

private:
    int    _number;
    string _clue;
};

typedef vector<AcrossLiteClue> AcrossLiteClues;

#endif // ACROSSLITECLUE_H
