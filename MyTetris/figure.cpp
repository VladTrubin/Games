#include "figure.h"

#include <QRandomGenerator>

IFigure::~IFigure()
{

}


FigureV::FigureV()
{
    makeRandomColors();
}


FigureV::~FigureV()
{

}


void FigureV::rotateColors(Direction dir)
{
    qSwap(_colors[0], _colors[2]);
    if (dir == DOWN)
    {
        qSwap(_colors[1], _colors[2]);
    }
    else
    {
        qSwap(_colors[0], _colors[1]);
    }
}


void FigureV::makeRandomColors()
{
    static QRandomGenerator generator;
    for (size_t i = 0; i < cellsN; ++i)
    {
        _colors[i] = colorsT[generator.generate() % colorsN];
    }
}

void FigureV::getColors(FigureV *other)
{
    for (size_t i = 0; i < cellsN; ++i)
    {
        _colors[i] = other->_colors[i];
    }
}




