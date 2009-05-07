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

#ifndef CROSSWORDCLUELIST_H
#define CROSSWORDCLUELIST_H

#include <QWidget>

class CrosswordClueList : public QWidget
{
    Q_OBJECT

public:
    CrosswordClueList( AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList, QWidget* parent, char* name = 0 );
    CrosswordClueList( QWidget* parent, char* name = 0 );
    ~CrosswordClueList();

    void                        setPuzzle( AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList );
    AcrossLitePuzzleBase*       puzzle();
    AcrossLiteClue::Orientation clueList();

signals:
    void clueSelected( AcrossLiteClue::Orientation o, int number );

public slots:
    void clueSelected( int number );

private slots:
    void _selected( QListBoxItem* item );

private:
    CrosswordClueList( );

    AcrossLitePuzzleBase*       m_puzzle;
    AcrossLiteClue::Orientation m_clueList;
};


#endif // CROSSWORDCLUELIST_H
