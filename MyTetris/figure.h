#ifndef FIGURE_H
#define FIGURE_H

#include <QColor>

enum Direction : unsigned char { DOWN, UP };

class IFigure
{
public:
    virtual ~IFigure() = 0;
};

class FigureV : public IFigure
{
protected:
    static constexpr size_t cellsN = 3;

public:
    FigureV();
    virtual ~FigureV();

    void setRow(size_t row);
    void setColumn(size_t column);

    inline size_t row()     { return _row;      }
    inline size_t column()  { return _column;   }

    void rotateColors(Direction dir);
    void makeRandomColors();

private:
    //! Indexes for top position of a FigureV
    size_t _row, _column;
    //! Colors for cells
    QColor  _cells[cellsN];
};

#endif // FIGURE_H
