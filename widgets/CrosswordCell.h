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

#ifndef CROSSWORDCELL_H
#define CROSSWORDCELL_H

#include <QTableWidgetItem>

class CrosswordCell : public QTableWidgetItem
{
    public:
        CrosswordCell();
        ~CrosswordCell();

        void setColRowLabel( const int col, const int row );
        int  colLabel() const;
        int  rowLabel() const;
        void setSolution( const QChar &letter );
        void setGuess( const QChar &letter );
        QChar solution() const;
        QChar guess() const;
        void revealSolution( const bool flag );
        bool isSolutionRevealed() const;
        void setShowCorrectness( const bool flag );
        bool showCorrectness() const;
        bool isSolutionCorrect() const;
        void setNumber( const int number = 0 );
        int  number() const;
        void showNumber( const bool flag );
        bool isNumberShown() const;
        void hilite( const bool flag );
        bool isHilited() const;

        virtual QSize sizeHint() const;
        virtual QSizePolicy sizePolicy() const;

    private:
        void updateCell();

        int  m_colLabel;
        int  m_rowLabel;
        QChar m_solution;
        QChar m_guess;
        bool m_isSolutionRevealed;
        bool m_showCorrectness;
        int  m_number;
        bool m_isNumberShown;
        bool m_isHilited;
};

#endif // CROSSWORDCELL_H
