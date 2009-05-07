#ifndef CROSSWORDCLUELIST_H
#define CROSSWORDCLUELIST_H

#include <QWidget>

class CrosswordClueList : public QWidget
{
    Q_OBJECT

public:
    CrosswordClueList( AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList, QWidget* parent, char* name = 0 );
    CrosswordClueList( QWidget* parent, char* name = 0 );
    ~CrosswordClueList();

    void                        setPuzzle( AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList );
    AcrossLitePuzzleBase*       puzzle();
    AcrossLiteClue::Orientation clueList();

signals:
    void clueSelected( AcrossLiteClue::Orientation o, int number );

public slots:
    void clueSelected( int number );

private slots:
    void _selected( QListBoxItem* item );

private:
    CrosswordClueList( );

    AcrossLitePuzzleBase*       m_puzzle;
    AcrossLiteClue::Orientation m_clueList;
};


#endif // CROSSWORDCLUELIST_H
