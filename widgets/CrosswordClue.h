#ifndef CROSSWORDCLUE_H
#define CROSSWORDCLUE_H

class CrosswordClue : public QListBoxText
{
    public:
       CrossWordClue(const int number, QListBox* listbox, const QString& text);
       CrossWordClue(const int number, const QString& text);
       CrossWordClue(const int number, QListBox* listbox, const QString& text, QListBoxItem* after);
      ~CrossWordClue ();

       int number() const;

    private:
       int _number;
};

#endif // CROSSWORDCLUE_H
