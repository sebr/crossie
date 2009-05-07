/***************************************************************************
 *   Copyright (C) 2009 by Seb Ruiz <ruiz@kde.org>                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "MainWindow.h"

MainWindow::MainWindow( QWidget *parent )
        : QMainWindow( parent )
{
    m_crossword = new Crossword( this );

    setCentralWidget( m_crossword );

    QMenu *fileMenu = menuBar()->addMenu( tr( "&File" ) );
    fileMenu->insertAction( "&Open...", this, SLOT( launchOpenDialog() ), QKeySequence::Open );
    fileMenu->insertAction( "&Save...", this, SLOT( launchSaveDialog() ), QKeySequence::Save );
    fileMenu->insertAction( "&Quit",    qApp, SLOT( quit() ) );

    QMenu *viewMenu = menuBar()->addMenu( tr( "&View" ) );
    viewMenu->insertAction( "Reveal Puzzle", this, SLOT( revealSolution() ) );
    viewMenu->insertAction( "Reveal Word",   this, SLOT( revealWord() ) );
    viewMenu->insertAction( "Reveal Letter", this, SLOT( revealLetter() ) );
    viewMenu->addSeparator();
    viewMenu->insertAction( "Check Puzzle",  this, SLOT( checkSolution() ) );
    viewMenu->insertAction( "Check Word",    this, SLOT( checkWord() ) );
    viewMenu->insertAction( "Check Letter",  this, SLOT( checkLetter() ) );
    viewMenu->addSeparator();
    viewMenu->insertAction( "Clear",         this, SLOT( clearSolution() ) );

    QMenu *helpMenu = menuBar()->addMenu( tr( "&Help" ) );
    helpMenu->insertAction( "About...",      this, SLOT( launchAboutDialog() ) );

//    toolBar()->setLabel( "Puzzle Operations" );

//    KToolBarButton* openButton           = new KToolBarButton( QPixmap(fileopen_xpm), 1, toolBar(), "open",           "Open Puzzle" );
//    toolBar()->addSeparator();
//
//    KToolBarButton* revealSolutionButton = new KToolBarButton( QPixmap(solution_xpm), 2, toolBar(), "revealsolution", "Reveal Puzzle" );
//    KToolBarButton* revealWordButton     = new KToolBarButton( QPixmap(word_xpm),     3, toolBar(), "revealword",     "Reveal Word" );
//    KToolBarButton* revealLetterButton   = new KToolBarButton( QPixmap(letter_xpm),   4, toolBar(), "revealletter",   "Reveal Letter" );
//    toolBar()->addSeparator();
//
//    KToolBarButton* checkSolutionButton  = new KToolBarButton( QPixmap(check_solution_xpm), 5, toolBar(), "checksolution",  "Check Puzzle" );
//    KToolBarButton* checkWordButton      = new KToolBarButton( QPixmap(check_word_xpm),     6, toolBar(), "checkword",      "Check Word" );
//    KToolBarButton* checkLetterButton    = new KToolBarButton( QPixmap(check_letter_xpm),   7, toolBar(), "checkletter",    "Check Letter" );
//
//    QObject::connect (openButton,           SIGNAL(clicked(int)), this, SLOT(launchOpenDialog()));
//
//    QObject::connect (revealSolutionButton, SIGNAL(clicked(int)), this, SLOT(revealSolution()));
//    QObject::connect (revealWordButton,     SIGNAL(clicked(int)), this, SLOT(revealWord()));
//    QObject::connect (revealLetterButton,   SIGNAL(clicked(int)), this, SLOT(revealLetter()));
//
//    QObject::connect (checkSolutionButton,  SIGNAL(clicked(int)), this, SLOT(checkSolution()));
//    QObject::connect (checkWordButton,      SIGNAL(clicked(int)), this, SLOT(checkWord()));
//    QObject::connect (checkLetterButton,    SIGNAL(clicked(int)), this, SLOT(checkLetter()));
//
//    statusBar()->message ("Enjoy!", 5000);
}

void MainWindow::launchOpenDialog()
{
    const QString fileName = QFileDialog::getOpenFileName( this,
                             tr( "Open Crossword" ),
                             QDir::homePath(),
                             tr( "Crossword Files (*.puz)" ) );
    setPuzzle( filename );
}

void MainWindow::launchSaveDialog()
{
    const QString fileName = QFileDialog::getSaveFileName( this,
                             tr( "Save Crossword" ),
                             QDir::homePath(),
                             tr( "Crossword Files (*.puz)" ) );

    savePuzzle( filename );
}

void MainWindow::setPuzzle( const QString& filename )
{
    if( !filename.isNull() )
        m_crossword->setPuzzle( filename );
}

void MainWindow::savePuzzle( const QString& filename )
{
    if( !filename.isNull() )
        m_crossword->savePuzzle( filename );
}

void MainWindow::revealSolution()
{
    m_crossword->revealSolution( true );
}

void MainWindow::revealWord()
{
    m_crossword->revealWord( true );
}

void MainWindow::revealLetter()
{
    m_crossword->revealLetter( true );
}

void MainWindow::checkSolution()
{
    m_crossword->checkSolution();
}

void MainWindow::checkWord()
{
    m_crossword->checkWord();
}

void MainWindow::checkLetter()
{
    m_crossword->checkLetter();
}

void MainWindow::clearSolution()
{
    m_crossword->clearSolution();
}

