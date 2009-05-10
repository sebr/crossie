/***************************************************************************
 *   Copyright (C) 2009 by Seb Ruiz <ruiz@kde.org>                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef CROSSWORDCELLDELEGATE_H
#define CROSSWORDCELLDELEGATE_H

#include <QItemDelegate>

class QPainter;

class CrosswordCellDelegate : public QItemDelegate
{
    public:
        CrosswordCellDelegate( QObject *parent );

        void paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index ) const;
};

#endif // CROSSWORDCELLDELEGATE_H
