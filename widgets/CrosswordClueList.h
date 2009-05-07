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

#include "acrosslite/AcrossLiteClue.h"
#include "acrosslite/AcrossLitePuzzle.h"

#include <QListWidget>
#include <QListWidgetItem>

/**
  * A widget which holds a list of clues for the crossword puzzle
  * Typically there are two CrosswordClueList widgets:
  *   - across clues
  *   - down clues
  */
class CrosswordClueList : public QListWidget
{
        Q_OBJECT

    public:
        CrosswordClueList( QWidget* parent );
        ~CrosswordClueList();

        void                        setPuzzle( AcrossLitePuzzle* puzzle, AcrossLiteClue::Orientation clueList );
        AcrossLitePuzzle*           puzzle();
        AcrossLiteClue::Orientation clueList();

    signals:
        void clueSelected( AcrossLiteClue::Orientation o, int number );

    public slots:
        void clueSelected( int number );

    private slots:
        void currentClueChanged( QListWidgetItem *current, QListWidgetItem *previous );

    private:
        AcrossLitePuzzle            *m_puzzle;
        AcrossLiteClue::Orientation  m_clueList;
};


#endif // CROSSWORDCLUELIST_H
