#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "widgets/Crossword.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void setPuzzle(const QString& filename);
        void savePuzzle(const QString& filename);
        void launchOpenDialog();
        void launchSaveDialog();
        void launchAboutDialog();
        void revealSolution();
        void revealWord();
        void revealLetter();
        void checkSolution();
        void checkWord();
        void checkLetter();
        void clearSolution();

    private:
        Crossword*  m_crossword;
};

#endif // MAINWINDOW_H
