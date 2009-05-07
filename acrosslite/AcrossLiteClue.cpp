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

#include "AcrossLiteClue.h"

AcrossLiteClue::AcrossLiteClue()
{
    _number = 0;
    _clue   = "";
}

AcrossLiteClue::AcrossLiteClue( const int number, const string& clue )
{
    _number = 0;
    _clue   = "";

    set( number, clue );
}

AcrossLiteClue::AcrossLiteClue( const AcrossLiteClue& src )
{
    _number = 0;
    _clue   = "";

    *this = src;
}

AcrossLiteClue::~AcrossLiteClue()
{
}

AcrossLiteClue& AcrossLiteClue::operator= ( const AcrossLiteClue & rhs )
{
    set( rhs.number(), rhs.clue() );

    return *this;
}

bool AcrossLiteClue::operator< ( const AcrossLiteClue& rhs )
{
    return ( number() < rhs.number() );
}

bool AcrossLiteClue::operator== ( const AcrossLiteClue& rhs )
{
    return ( number() == rhs.number() );
}

ostream& operator<< ( ostream& os, const AcrossLiteClue& rhs )
{
    os << rhs.number() << ") " << rhs.clue();

    return os;
}

void AcrossLiteClue::set( const int number, const string& clue )
{
    _number = number;
    _clue   = clue;
}

int AcrossLiteClue::number() const
{
    return _number;
}

const string& AcrossLiteClue::clue() const
{
    return _clue;
}

