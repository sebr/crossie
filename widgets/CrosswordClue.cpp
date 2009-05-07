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

#include "CrosswordClue.h"

CrosswordClue::CrosswordClue( const int n, QListBox* listbox, const QString& text )
    : QListBoxText( listbox, "" )
{
    m_number = n;

    setText( QString::number( number() ) + QString( "." ) + text );
}

CrosswordClue::CrosswordClue( const int n, const QString& text )
    : QListBoxText( "" )
{
    m_number = n;

    setText( QString::number( number() ) + QString( "." ) + text );
}

CrosswordClue::CrosswordClue( const int n, QListBox* listbox, const QString& text, QListBoxItem* after )
    : QListBoxText( listbox, "", after )
{
    m_number = n;

    setText( QString::number( number() ) + QString( "." ) + text );
}

CrosswordClue::~CrosswordClue()
{
}


int CrosswordClue::number() const
{
    return m_number;
}
