#include "AcrossLiteGrid.h"

AcrossLiteGrid::AcrossLiteGrid()
{
    resize( 0, 0 );
}

AcrossLiteGrid::AcrossLiteGrid( const int nColumns, const int nRows )
{
    resize( nColumns, nRows );
}

AcrossLiteGrid::AcrossLiteGrid( const AcrossLiteGrid& src )
{
    *this = src;
}

AcrossLiteGrid::~AcrossLiteGrid()
{
}

AcrossLiteGrid& AcrossLiteGrid::operator= ( const AcrossLiteGrid & rhs )
{
    _nColumns = rhs._nColumns;
    _nRows    = rhs._nRows;
    _cells    = rhs._cells;

    return *this;
}

ostream& operator<< ( ostream& os, const AcrossLiteGrid& rhs )
{
    for ( int r = 0; r < rhs.nRows(); r++ )
    {
        for ( int c = 0; c < rhs.nColumns(); c++ )
        {
            os << ( char )rhs.cell( c, r );
        }
        os << endl;
    }


    return os;
}

void AcrossLiteGrid::resize( const int nColumns, const int nRows )
{
    _nColumns = nColumns;
    _nRows    = nRows;

    _cells.resize( _nColumns * _nRows );
}

int AcrossLiteGrid::nColumns() const
{
    return _nColumns;
}

int AcrossLiteGrid::nRows() const
{
    return _nRows;
}

int AcrossLiteGrid::cell( const int column, const int row ) const
{
    int i = index( column, row );

    return _cells[i];
}

void AcrossLiteGrid::setCell( const int column, const int row, const int letter )
{
    int i = index( column, row );

    _cells[i] = letter;
}

int AcrossLiteGrid::index( const int column, const int row ) const
{
    int i = column + ( row * nColumns() );

    return i;
}
