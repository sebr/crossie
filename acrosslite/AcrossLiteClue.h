#ifndef ACROSSLITECLUE_H
#define ACROSSLITECLUE_H

using namespace std;

#include <vector>
#include <string>

class AcrossLiteClue
{
    public:
        enum Orientation
        {
           Unknown = 0,
           Across  = 1,
           Down    = 2
        };

        AcrossLiteClue();
        AcrossLiteClue( const int number, const string& clue );
        AcrossLiteClue( const AcrossLiteClue& src );
       ~AcrossLiteClue();

        AcrossLiteClue& operator=  (const AcrossLiteClue& rhs);
        bool            operator<  (const AcrossLiteClue& rhs);
        bool            operator== (const AcrossLiteClue& rhs);
        friend ostream& operator<< (ostream& os, const AcrossLiteClue& rhs);

        void set(const int number, const string& clue);
        int  number() const;
        const string& clue() const;

    private:
        int    _number;
        string _clue;
};

typedef vector<AcrossLiteClue> AcrossLiteClues;

#endif // ACROSSLITECLUE_H
