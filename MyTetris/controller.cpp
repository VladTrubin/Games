#include "controller.h"
#include "scenemodel.h"
#include "sceneview.h"

#include <QMessageBox>

Controller::Controller(IScene *model, IView *view, QObject *parent) : QObject(parent), _model(model), _view(view)
{
    connect(&_timer, &QTimer::timeout, this, &Controller::doStep);
}


void Controller::doStart()
{
    _model->newGame();
    doResume();
}


void Controller::doStep()
{
    _model->doStep();
    _view->repaint();

    if (not _model->gameOn())
    {
        auto res = QMessageBox::information(_view, QStringLiteral("Results"),
                                 QString("Your score: %1! Can we play again?").arg(_model->score()),
                                 QMessageBox::No, QMessageBox::Reset);
        if (res == QMessageBox::No)
        {
            // TODO Exit app
        }
        else
        {
            doStart();
        }
    }
}


void Controller::doPause()
{
    _timer.stop();
}


void Controller::doResume()
{
    _timer.start(stepTimeInterval);
}


void Controller::moveLeft()
{
    _model->moveLeft();
}


void Controller::moveRight()
{
    _model->moveRight();
}


void Controller::colorDown()
{
    _model->colorDown();
}


void Controller::colorUp()
{
    _model->colorUp();
}


void Controller::doDrop(bool enabled)
{
    enabled ? _model->startDrop() : _model->stopDrop();
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


void Controller::setSpeed(const QString &speed)
{
    _model->setSpeed(speed.toUInt());
}



