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
    auto s = QSize(_columns*sizeCell, _rows*sizeCell);
    setFixedSize(s);
}


void SceneView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    drawScene(&painter);
}


void SceneView::drawScene(QPainter *painter)
{
    auto& grid = _model->grid();
    for (size_t r = 0; r < _rows; ++r)
    {
        for (size_t c = 0; c < _columns; ++c)
        {
//            QRect curr = QRect((c*sizeCell)+1, (r*sizeCell)+1, sizeCell-2, sizeCell-2);
            QRect curr = QRect((c*sizeCell), (r*sizeCell), sizeCell, sizeCell);
//            painter->fillRect(curr, grid[r][c]);
            QBrush brush = QBrush(QGradient(grid[r][c]));
            painter->setBrush(brush);
            painter->drawEllipse(curr);
        }
    }
}


void SceneView::keyPressEvent(QKeyEvent *event)
{
    if (_model->gameOn())
    {
        switch(event->key())
        {
            case Qt::Key_Left:   _controller->moveLeft();    break;
            case Qt::Key_Right:  _controller->moveRight();   break;
            case Qt::Key_Down:   _controller->rotateDown();  break;
            case Qt::Key_Up:     _controller->rotateUp();    break;
            case Qt::Key_Space:  _controller->doDrop(true);  break;
            case Qt::Key_Escape: _controller->togglePause(); break;
            default: QWidget::keyPressEvent(event);          break;
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
