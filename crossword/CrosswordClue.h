/***************************************************************************
 *   Copyright (C) 2009 by Seb Ruiz <ruiz@kde.org>                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CROSSWORDCLUE_H
#define CROSSWORDCLUE_H

class CrosswordClue : public QListWidgetItem
{
    public:
        CrosswordClue( const int number, const QString& text, QListWidget *parent )
            : QListWidgetItem( parent )
        {
            m_number = number;
            setText( QString::number( m_number ) + ". " + text );
        }

        int number() const { return m_number; }

    private:
        int m_number;
};

#endif // CROSSWORDCLUE_H
