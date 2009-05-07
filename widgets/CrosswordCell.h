#ifndef CROSSWORDCELL_H
#define CROSSWORDCELL_H

#include <QTableWidgetItem>

class CrosswordCell : public QTableWidgetItem
{
    Q_OBJECT

public:
    CrosswordCell();
    ~CrosswordCell();

    void setColRowLabel( const int col, const int row );
    int  colLabel() const;
    int  rowLabel() const;
    void setSolution( const char letter );
    void setGuess( const char letter );
    char solution() const;
    char guess() const;
    void revealSolution( const bool flag );
    bool isSolutionRevealed() const;
    void setShowCorrectness( const bool flag );
    bool showCorrectness() const;
    bool isSolutionCorrect() const;
    void setNumber( const int number = 0 );
    int  number() const;
    void showNumber( const bool flag );
    bool isNumberShown() const;
    void hilite( const bool flag );
    bool isHilited() const;

    virtual QSize sizeHint() const;
    virtual QSizePolicy sizePolicy() const;
    virtual void paintEvent( QPaintEvent* e );
    virtual void paintNumber( QPainter& p );
    virtual void paintFrame( QPainter& p );
    virtual void paintLetter( QPainter& p );
    virtual void paintBlock( QPainter& p );

private:
    CrosswordCell();

    int  m_colLabel;
    int  m_rowLabel;
    char m_solution;
    char m_guess;
    bool m_isSolutionRevealed;
    bool m_showCorrectness;
    int  m_number;
    bool m_isNumberShown;
    bool m_isHilited;
};

#endif // CROSSWORDCELL_H
