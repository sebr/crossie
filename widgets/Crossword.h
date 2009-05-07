#ifndef CROSSWORD_H
#define CROSSWORD_H

#include <QWidget>

class Crossword : public QWidget
{
    Q_OBJECT

public:
    Crossword( QWidget* parent, char* name = 0 );
    ~Crossword();

    void setPuzzle( const QString& filename );
    void savePuzzle( const QString& filename );

    void clearSolution();
    void revealSolution( const bool flag );
    void revealWord( const bool flag );
    void revealLetter( const bool flag );
    void checkSolution();
    void checkWord();
    void checkLetter();

public slots:
    void handleNewColRowFocused( int newCol, int newRow );

private:
    AcrossLitePuzzleBase* m_puzzle;
    QHGroupBox*           m_puzzleGroupBox;
    CrosswordGrid*        m_grid;
    CrosswordClueList*    m_acrossClues;
    CrosswordClueList*    m_downClues;
};


#endif // CROSSWORD_H
