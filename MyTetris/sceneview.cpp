#include "sceneview.h"

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
    // method need be invoke from controller after init all
    auto s = QSize(_rows/sizeCell, _columns/sizeCell);
    setFixedSize(s);
}
