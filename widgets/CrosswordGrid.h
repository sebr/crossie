#ifndef CROSSWORDGRID_H
#define CROSSWORDGRID_H

#include <QWidget>

class CrosswordGrid : public QWidget
{
    Q_OBJECT

public:

    enum FocusOrientation
    {
        FocusUnknown    = 0,
        FocusHorizontal = 1,
        FocusVertical   = 2
    };

    CrosswordGrid( QWidget* parent, char* name = 0 );
    CrosswordGrid( AcrossLitePuzzleBase* puzzle, QWidget* parent, char* name = 0 );
    ~CrosswordGrid();

    void setPuzzle( AcrossLitePuzzleBase* puzzle );
    AcrossLitePuzzleBase* puzzle();
    void savePuzzle( const QString& filename );

    void revealSolution( const bool flag );
    void revealWord( const bool flag );
    void revealLetter( const bool flag );
    void uncheckSolution();
    void checkSolution();
    void checkWord();
    void checkLetter();

    CrosswordCell* focusCell();
    CrosswordCell* cell( const int col, const int row );
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
    virtual void  keyPressEvent( QKeyEvent*   e );
    virtual void  mousePressEvent( QMouseEvent* e );
    virtual bool  eventFilter( QObject* o, QEvent *e );

public slots:
    void setFocusCell( AcrossLiteClue::Orientation o, int number );

signals:
    void rowFocused( int row );
    void colFocused( int col );
    void colRowFocused( int col, int row );

private:
    CrosswordGrid();

    AcrossLitePuzzleBase* m_puzzle;
    QGridLayout*          m_gridLayout;
    FocusOrientation      m_focusOrientation;
    QList<CrosswordCell*> m_cells;
};


#endif // CROSSWORDGRID_H
