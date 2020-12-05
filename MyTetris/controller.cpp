#include "controller.h"
#include "scenemodel.h"
#include "sceneview.h"



Controller::Controller(IModel *model, IView *view, QObject *parent) : QObject(parent), _model(model), _view(view)
{

}


void Controller::doStep()
{

}


void Controller::doPause()
{

}


void Controller::doResume()
{

}


void Controller::moveLeft()
{

}


void Controller::moveRight()
{

}


void Controller::doRotate()
{

}


void Controller::doSave()
{

}


void Controller::doLoad()
{

}



