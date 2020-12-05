#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QWidget>

class IController;
class IModel;

class IView : public QWidget
{

};

class SceneView : public IView
{
    Q_OBJECT
public:
    explicit SceneView(QWidget *parent = nullptr);



private:
    IModel      *model;
    IController *controller;
};

#endif // SCENEVIEW_H
