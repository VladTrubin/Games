#include "sceneview.h"
#include "scenemodel.h"
#include "controller.h"

#include <QPainter>
#include <QKeyEvent>


IView::~IView()
{

}


SceneView::SceneView(QWidget *parent) : IView(parent)
{
}


SceneView::~SceneView()
{

}


void SceneView::setWidgetSize()
{
    auto s = QSize(_rows/sizeCell, _columns/sizeCell);
    setFixedSize(s);
}


void SceneView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    drawScene(&painter);

//    if (_model->gameOn())
//        drawFigure(&painter);   // падающую фигуру

}


void SceneView::drawScene(QPainter *painter)
{
    auto& grid = _model->grid();
    for (size_t r = 0; r < _rows; ++r)
    {
        for (size_t c = 0; c < _columns; ++c)
        {
            QRect curr = QRect(c+1, r+1, sizeCell-2, sizeCell-2);
            painter->fillRect(curr, grid[r][c]);
        }
    }
}


void SceneView::keyPressEvent(QKeyEvent *event)
{
    if (_model->gameOn())
    {
        switch(event->key())
        {
            case Qt::Key_Left:  _controller->moveLeft();    break;
            case Qt::Key_Right: _controller->moveRight();   break;
            case Qt::Key_Down:  _controller->colorDown();   break;
            case Qt::Key_Up:    _controller->colorUp();     break;
            case Qt::Key_Space: _controller->doDrop(true);  break;
            case Qt::Key_Pause: _controller->doPause();     break;
            default: QWidget::keyPressEvent(event);         break;
        }
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}


void SceneView::keyReleaseEvent(QKeyEvent *event)
{
    if (_model->gameOn())
    {
        if (event->key() == Qt::Key_Space)
            _controller->doDrop(false);
        else
            QWidget::keyReleaseEvent(event);
    }
    else
        QWidget::keyReleaseEvent(event);
}
