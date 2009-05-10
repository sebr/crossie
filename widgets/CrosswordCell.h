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
        enum CellRole {
            ClueNumberRole = Qt::UserRole
        };

        CrosswordCell();
        ~CrosswordCell();

        static int cellSize() { return 40; }

        void setSolution( const QChar &letter );
        QChar solution() const { return m_solution; }

        void setGuess( const QChar &letter );
        QChar guess() const { return m_guess; }

        void revealSolution( const bool flag );
        bool isSolutionRevealed() const { return m_isSolutionRevealed; }

        void setShowCorrectness( const bool flag );
        bool isShowCorrectness() const { return m_showCorrectness; }
        bool isSolutionCorrect() const;

        void setNumber( const int number = 0 );
        int  number() const { return m_number; }

        void showNumber( const bool flag );
        bool isNumberShown() const { return m_isNumberShown; }

        void highlight( const bool flag );
        bool isHighlighted() const { return m_isHighlighted; }

        bool isBlank() const { return m_solution == '.'; }

        Qt::ItemFlags flags() const;
        virtual QVariant data( int role ) const;

        virtual QSize sizeHint() const;
        virtual QSizePolicy sizePolicy() const;

    private:
        void updated();

        QChar m_solution;
        QChar m_guess;
        bool m_isSolutionRevealed;
        bool m_showCorrectness;
        int  m_number;
        bool m_isNumberShown;
        bool m_isHighlighted;
};

#endif // CROSSWORDCELL_H
