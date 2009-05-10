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

#ifndef CROSSWORD_H
#define CROSSWORD_H

#include "CrosswordGrid.h"
#include "CrosswordClueList.h"

#include "acrosslite/AcrossLitePuzzle.h"

#include <QGroupBox>
#include <QWidget>

class Crossword : public QWidget
{
    Q_OBJECT

public:
    Crossword( QWidget* parent );
    ~Crossword();

    void setPuzzle( const QString& filename );
    void savePuzzle( const QString& filename );

    void clearSolution();
    void revealSolution( const bool flag );
    void revealWord( const bool flag );
    void revealLetter( const bool flag );
    void checkSolution();
    void checkWord();
    void checkLetter();

private slots:
    void cellSelectedChanged( int currentRow, int currentColumn, int previousRow, int previousColumn );

private:
    AcrossLitePuzzle  *m_puzzle;
    QGroupBox         *m_puzzleGroupBox;
    CrosswordGrid     *m_grid;
    CrosswordClueList *m_acrossClues;
    CrosswordClueList *m_downClues;
};


#endif // CROSSWORD_H
