#ifndef ACROSSLITEGRID_H
#define ACROSSLITEGRID_H

using namespace std;

#include <vector>
#include <string>
#include <iostream>

class AcrossLiteGrid {
    public:
        AcrossLiteGrid ();
        AcrossLiteGrid (const int nColumns, const int nRows);
        AcrossLiteGrid (const AcrossLiteGrid& src);
       ~AcrossLiteGrid ();

        AcrossLiteGrid& operator=  (const AcrossLiteGrid& rhs);
        friend ostream& operator<< (ostream& os, const AcrossLiteGrid& rhs);

        void            resize     (const int nColumns, const int nRows);
        int             nColumns   () const;
        int             nRows      () const;

        int             cell       (const int column, const int row) const;
        void            setCell    (const int column, const int row, const int letter);
        int             index      (const int column, const int row) const;

    private:
        int             _nColumns;
        int             _nRows;
        vector<int>     _cells;
};

#endif // ACROSSLITEGRID_H
