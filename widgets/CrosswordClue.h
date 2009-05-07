#ifndef CROSSWORDCLUE_H
#define CROSSWORDCLUE_H

class CrosswordClue : public QListBoxText
{
public:
    CrosswordClue( const int number, QListBox* listbox, const QString& text );
    CrosswordClue( const int number, const QString& text );
    CrosswordClue( const int number, QListBox* listbox, const QString& text, QListBoxItem* after );
    ~CrosswordClue();

    int number() const;

private:
    int m_number;
};

#endif // CROSSWORDCLUE_H
