#include "controller.h"
#include "scenemodel.h"
#include "sceneview.h"

#include <QMessageBox>

Controller::Controller(IScene *model, IView *view, QObject *parent) : QObject(parent), _model(model), _view(view)
{
    connect(&_timer, &QTimer::timeout, this, &Controller::doStep);
    connect(_model,  &IScene::speedChanged, this, &Controller::speedChanged);
}

void Controller::doAction(void (IScene::*action)())
{
    if (not _timer.isActive())
        return;

    (_model->*action)();
    _view->repaint();
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
        _timer.stop();
        auto res = QMessageBox::information(_view, QStringLiteral("Results"),
                                 QString("Your score: %1! Can we play again?").arg(_model->score()),
                                 QMessageBox::No, QMessageBox::Ok);
        if (res == QMessageBox::No)
        {
            // TODO Exit app?
        }
        else
        {
            doStart();
        }
    }
}

void Controller::togglePause()
{
    _timer.isActive() ? doPause() : doResume();
}


void Controller::doPause()
{
    _timer.stop();
}


void Controller::doResume()
{
    _timer.start(stepTimeInterval);
    speedChanged(_model->speed());
}


void Controller::moveLeft()
{
    doAction(&IScene::moveLeft);
}


void Controller::moveRight()
{
    doAction(&IScene::moveRight);
}


void Controller::rotateDown()
{
    doAction(&IScene::rotateDown);
}


void Controller::rotateUp()
{
    doAction(&IScene::rotateUp);
}


void Controller::doDrop(bool enabled)
{
    if (_timer.isActive())
    {
        auto currTime = stepTimeInterval / (enabled ? _model->maxSpeed() : _model->speed());
        _timer.start(currTime);
    }
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



