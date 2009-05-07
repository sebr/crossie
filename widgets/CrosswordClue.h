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

#ifndef CROSSWORDCLUE_H
#define CROSSWORDCLUE_H

class CrosswordClue : public QListBoxText
{
public:
    CrosswordClue( const int number, QListBox* listbox, const QString& text );
    CrosswordClue( const int number, const QString& text );
    CrosswordClue( const int number, QListBox* listbox, const QString& text, QListBoxItem* after );
    ~CrosswordClue();

    int number() const;

private:
    int m_number;
};

#endif // CROSSWORDCLUE_H
