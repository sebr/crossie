/***************************************************************************
 *   Copyright (C) 2009 by Seb Ruiz <ruiz@kde.org>                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "CrosswordCellDelegate.h"
#include "CrosswordCell.h"

#include <QDebug>
#include <QFont>
#include <QPainter>

CrosswordCellDelegate::CrosswordCellDelegate( QObject *parent )
    : QItemDelegate( parent )
{
}

void CrosswordCellDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option,
                                   const QModelIndex &index ) const
{
    QItemDelegate::paint( painter, option, index );

    const QString number = index.data( CrosswordCell::ClueNumberRole ).toString();

    if( !number.isEmpty() )
    {
        painter->save();
        QFont font;
        font.setPointSize( font.pointSize() - 1 );

        QRect rect = option.rect;
        rect.setWidth( rect.width() / 2 );
        rect.setHeight( rect.height() / 2 );

        painter->setFont( font );
        painter->setRenderHint( QPainter::Antialiasing );
        painter->drawText( rect, number );

        painter->restore();
    }
}
