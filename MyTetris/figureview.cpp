#include "figureview.h"

FigureView::FigureView(QWidget *parent, IFigure *figure) : QWidget(parent), _figure(figure)
{

}


void FigureView::paintEvent(QPaintEvent *event)
{
    // Рисуем следующую фигуру если есть, посередине QPainter::tanslate
}

void FigureView::newFigure()
{

}


void FigureView::drawFigure(QPainter *painter)
{

}
