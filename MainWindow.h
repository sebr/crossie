/***************************************************************************
 *   Copyright (C) 2009 by Seb Ruiz <ruiz@kde.org>                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "widgets/Crossword.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow( QWidget *parent = 0 );

    public slots:
        void setPuzzle( const QString& filename );
        void savePuzzle( const QString& filename );
        void launchOpenDialog();
        void launchSaveDialog();
        void revealSolution();
        void revealWord();
        void revealLetter();
        void checkSolution();
        void checkWord();
        void checkLetter();
        void clearSolution();

    private:
        Crossword* m_crossword;
};

#endif // MAINWINDOW_H
