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

#ifndef CROSSWORDGRID_H
#define CROSSWORDGRID_H

#include "CrosswordCell.h"

#include "acrosslite/AcrossLitePuzzle.h"

#include <QTableWidget>
#include <QGridLayout>

class CrosswordGrid : public QTableWidget
{
    Q_OBJECT

public:

    enum FocusOrientation
    {
        FocusUnknown    = 0,
        FocusHorizontal = 1,
        FocusVertical   = 2
    };

    CrosswordGrid( QWidget* parent );
    ~CrosswordGrid();

    void setPuzzle( AcrossLitePuzzle* puzzle );
    AcrossLitePuzzle* puzzle();
    void savePuzzle( const QString& filename );

    void revealSolution( const bool flag );
    void revealWord( const bool flag );
    void revealLetter( const bool flag );
    void uncheckSolution();
    void checkSolution();
    void checkWord();
    void checkLetter();

    CrosswordCell* cell( const int number );
    void setFocusCell( const int col, const int row );
    void retreatFocusCell();
    void advanceFocusCell( const int count = 1 );
    void setFocusOrientation( const CrosswordGrid::FocusOrientation orientation );
    CrosswordGrid::FocusOrientation focusOrientation() const;

    void hiliteSolution( const bool flag );
    void hiliteFullSolution( const bool flag );

    void colRowToDownAcross( const int col, const int row, int& down, int& across );

    virtual QSize minimumSizeHint() const;
    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    virtual void  keyPressEvent( QKeyEvent* e );
//    virtual void  mousePressEvent( QMouseEvent* e );
    virtual bool  eventFilter( QObject* o, QEvent *e );

public slots:
    void setFocusCell( AcrossLiteClue::Orientation o, int number );

private slots:
    void currentCellChanged( QTableWidgetItem *current, QTableWidgetItem *previous );

signals:
    void rowFocused( int row );
    void colFocused( int col );
    void colRowFocused( int col, int row );

private:
    CrosswordCell *getCell( const int row, const int col ) const;

    AcrossLitePuzzle*     m_puzzle;
    FocusOrientation      m_focusOrientation;
};


#endif // CROSSWORDGRID_H
