#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <QWidget>

class CrossWord : public QWidget {
    Q_OBJECT

    public:
        CrossWord (QWidget* parent, char* name = 0);
       ~CrossWord ();

        void                                setPuzzle               (const QString& filename);
        void                                savePuzzle              (const QString& filename);

        void                                clearSolution           ();
        void                                revealSolution          (const bool flag);
        void                                revealWord              (const bool flag);
        void                                revealLetter            (const bool flag);
        void                                checkSolution           ();
        void                                checkWord               ();
        void                                checkLetter             ();

    public slots:
        void                                handleNewColRowFocused  (int newCol, int newRow);

    private:
       AcrossLitePuzzleBase*                _puzzle;
       QHGroupBox*                          _puzzleGroupBox;
       CrossWordGrid*                     _grid;
       CrossWordClueList*                 _acrossClues;
       CrossWordClueList*                 _downClues;
};


#endif // CROSSWORD_H
