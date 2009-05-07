#ifndef CROSSWORDCLUELIST_H
#define CROSSWORDCLUELIST_H

#include <QWidget>

class CrossWordClueList : public QWidget
{
    Q_OBJECT

    public:
        CrossWordClueList( AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList, QWidget* parent, char* name = 0 );
        CrossWordClueList( QWidget* parent, char* name = 0 );
       ~CrossWordClueList();

        void                                setPuzzle           (AcrossLitePuzzleBase* puzzle, AcrossLiteClue::Orientation clueList);
        AcrossLitePuzzleBase*               puzzle              ();
        AcrossLiteClue::Orientation         clueList            ();

    signals:
        void                                clueSelected        (AcrossLiteClue::Orientation o, int number);

    public slots:
        void                                clueSelected        (int number);

    private slots:
        void                                _selected           (QListBoxItem* item);

    private:
        CrossWordClueList ( );

        AcrossLitePuzzleBase*               _puzzle;
        AcrossLiteClue::Orientation         _clueList;
};


#endif // CROSSWORDCLUELIST_H
