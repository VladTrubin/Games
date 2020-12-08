#include "figureview.h"
#include "figure.h"

#include <QPainter>
#include <QtDebug>

FigureView::FigureView(QWidget *parent, FigureV *figure, size_t sideLen)
    : QWidget(parent), _figure(figure), _sideLen(sideLen)
{
    setFixedSize(sideLen, _figure->cells()*sideLen);
    activateWindow();
    raise();
}


void FigureView::paintEvent(QPaintEvent *event)
{
    if (_figure->isHide())  // Проверить работает ли как задуманно?
        return;

    QPainter painter(this);

    if (_movable)
        move(_figure->column()*_sideLen, _figure->row()*_sideLen);

    for (size_t i = 0; i < _figure->cells(); ++i)
    {
//        QRect rect(1, i*_sideLen+1,
//                   _sideLen-2, _sideLen-2);
//        painter.fillRect(rect, _figure->colors()[i]);
        QRect rect(0, i*_sideLen, _sideLen, _sideLen);
        auto br = QBrush(QGradient(_figure->colors()[i]));
        painter.setBrush(br);
        painter.drawEllipse(rect);
    }

    QWidget::paintEvent(event);
}


void FigureView::drawFigure()
{
//    repaint();
    update();
}
