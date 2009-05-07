
#include "AcrossLiteClue.h"

AcrossLiteClue::AcrossLiteClue ()
{
    _number = 0;
    _clue   = "";
}

AcrossLiteClue::AcrossLiteClue (const int number, const string& clue)
{
    _number = 0;
    _clue   = "";

    set (number, clue);
}

AcrossLiteClue::AcrossLiteClue (const AcrossLiteClue& src)
{
    _number = 0;
    _clue   = "";

    *this = src;
}

AcrossLiteClue::~AcrossLiteClue ()
{
}

AcrossLiteClue& AcrossLiteClue::operator= (const AcrossLiteClue& rhs)
{
    set (rhs.number(), rhs.clue());

    return *this;
}

bool AcrossLiteClue::operator< (const AcrossLiteClue& rhs)
{
    return (number() < rhs.number());
}

bool AcrossLiteClue::operator== (const AcrossLiteClue& rhs)
{
    return (number() == rhs.number());
}

ostream& operator<< (ostream& os, const AcrossLiteClue& rhs)
{
    os << rhs.number() << ") " << rhs.clue();

    return os;
}

void AcrossLiteClue::set (const int number, const string& clue)
{
    _number = number;
    _clue   = clue;
}

int AcrossLiteClue::number () const
{
    return _number;
}

const string& AcrossLiteClue::clue () const
{
    return _clue;
}

