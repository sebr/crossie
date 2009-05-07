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

#include "Crossword.h"

Crossword::Crossword (QWidget* parent, char* name) : QWidget (parent, name) {
    m_puzzle      = 0;
    m_grid        = 0;
    m_acrossClues = 0;
    m_downClues   = 0;

    // Create widgets
    m_puzzleGroupBox = new QHGroupBox("Puzzle", this);

    QVBox*      cluesBox       = new QVBox(this);
    QVGroupBox* acrossGroupBox = new QVGroupBox("Across", cluesBox);
    QVGroupBox* downGroupBox   = new QVGroupBox("Down",   cluesBox);

    m_grid        = new CrosswordGrid     (_puzzleGroupBox);
    m_grid->setMinimumSize(500,500);
    m_acrossClues = new CrosswordClueList (acrossGroupBox);
    m_acrossClues->setMinimumWidth(300);
    m_downClues   = new CrosswordClueList (downGroupBox);
    m_downClues->setMinimumWidth(300);

    // Create Layouts
    QLayout* topLayout = new QHBoxLayout(this, 5);
    topLayout->add(_puzzleGroupBox);
    topLayout->add(cluesBox);

    QObject::connect (_acrossClues, SIGNAL(clueSelected(AcrossLiteClue::Orientation, int)), m_grid,        SLOT(setFocusCell(AcrossLiteClue::Orientation, int)));
    QObject::connect (_downClues,   SIGNAL(clueSelected(AcrossLiteClue::Orientation, int)), m_grid,        SLOT(setFocusCell(AcrossLiteClue::Orientation, int)));
    QObject::connect (_grid,        SIGNAL(colRowFocused(int, int)),                        this,         SLOT(handleNewColRowFocused(int, int)));
}

Crossword::~Crossword () {
    if (_puzzle) {
        delete m_puzzle;
        m_puzzle = 0;
    }
}

void Crossword::setPuzzle (const QString& filename) {
    if (_puzzle) {
        delete m_puzzle;
        m_puzzle = 0;
    }

    if (filename.right(4) == QString(".puz")) {
        m_puzzle = new AcrossLitePuzPuzzle(filename.ascii());

    }else if (filename.right(4) == QString(".txt")) {
        m_puzzle = new AcrossLiteTxtPuzzle(filename.ascii());
    }

    m_grid->setPuzzle (_puzzle);
    m_acrossClues->setPuzzle (_puzzle, AcrossLiteClue::Across);
    m_downClues->setPuzzle (_puzzle, AcrossLiteClue::Down);

    m_puzzleGroupBox->setTitle(QString(_puzzle->puzzleName().c_str()));
}

void Crossword::savePuzzle (const QString& filename) {
    m_grid->savePuzzle(filename);
}

void Crossword::clearSolution () {
    m_grid->revealSolution (false);
    m_grid->uncheckSolution ();
}

void Crossword::revealSolution (const bool flag) {
    m_grid->revealSolution (flag);
}

void Crossword::revealWord (const bool flag) {
    m_grid->revealWord (flag);
}

void Crossword::revealLetter (const bool flag) {
    m_grid->revealLetter (flag);
}

void Crossword::checkSolution () {
    m_grid->checkSolution ();
}

void Crossword::checkWord () {
    m_grid->checkWord ();
}

void Crossword::checkLetter () {
    m_grid->checkLetter ();
}

void Crossword::handleNewColRowFocused (int newCol, int newRow) {
    int down, across;

    m_grid->colRowToDownAcross (newCol, newRow, down, across);

    if (down != -1) {
        m_downClues->clueSelected (down);
    }

    if (across != -1) {
        m_acrossClues->clueSelected (across);
    }
}

