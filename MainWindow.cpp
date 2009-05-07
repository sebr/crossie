
#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow( parent )
{
    _crossWord = new CrossWord(this);

    setCentralWidget (_crossWord);

    QMenu *fileMenu = menuBar()->addMenu( tr("&File") );
    fileMenu->insertItem("&Open...", this, SLOT(launchOpenDialog()), QKeySequence::Open );
    fileMenu->insertItem("&Save...", this, SLOT(launchSaveDialog()), QKeySequence::Save );
    fileMenu->insertItem("&Quit", qApp, SLOT(quit()) );

    QMenu *viewMenu = menuBar()->addMenu( tr("&View") );
    viewMenu->insertItem(QPixmap(solution_xpm),       "Reveal Puzzle",   this, SLOT(revealSolution()) );
    viewMenu->insertItem(QPixmap(word_xpm),           "Reveal Word",     this, SLOT(revealWord())     );
    viewMenu->insertItem(QPixmap(letter_xpm),         "Reveal Letter",   this, SLOT(revealLetter())   );
    viewMenu->insertSeparator();
    viewMenu->insertItem(QPixmap(check_solution_xpm), "Check Puzzle",    this, SLOT(checkSolution())  );
    viewMenu->insertItem(QPixmap(check_word_xpm),     "Check Word",      this, SLOT(checkWord())      );
    viewMenu->insertItem(QPixmap(check_letter_xpm),   "Check Letter",    this, SLOT(checkLetter())    );
    viewMenu->insertSeparator();
    viewMenu->insertItem(                             "Clear",           this, SLOT(clearSolution())  );

    QMenu *helpMenu = menuBar()->addMenu( tr("&Help") );
    helpMenu->insertItem("About...",                                     this, SLOT(launchAboutDialog()) );

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

void MainWindow::launchOpenDialog() {
    const QString fileName = QFileDialog::getOpenFileName(this,
                                    tr("Open Crossword"),
                                    QDir::homePath(),
                                    tr("Crossword Files (*.puz)"));
    setPuzzle (filename);
}

void MainWindow::launchSaveDialog() {
    const QString fileName = QFileDialog::getSaveFileName(this,
                                    tr("Save Crossword"),
                                    QDir::homePath(),
                                    tr("Crossword Files (*.puz)"));

    savePuzzle (filename);
}

void MainWindow::setPuzzle (const QString& filename) {
    if (!filename.isNull()) {
        _crossWord->setPuzzle(filename);
    }
}

void MainWindow::savePuzzle (const QString& filename) {
    if (!filename.isNull()) {
        _crossWord->savePuzzle(filename);
    }
}

void MainWindow::revealSolution () {
    _crossWord->revealSolution(true);
}

void MainWindow::revealWord () {
    _crossWord->revealWord(true);
}

void MainWindow::revealLetter () {
    _crossWord->revealLetter(true);
}

void MainWindow::checkSolution () {
    _crossWord->checkSolution();
}

void MainWindow::checkWord () {
    _crossWord->checkWord();
}

void MainWindow::checkLetter () {
    _crossWord->checkLetter();
}

void MainWindow::clearSolution () {
    _crossWord->clearSolution();
}

