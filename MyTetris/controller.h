#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QTimer>

class IScene;
class IView;

class Controller : public QObject
{
    Q_OBJECT

private:
    static constexpr int stepTimeInterval = 500;

public:
    explicit Controller(IScene *model, IView *view, QObject *parent = nullptr);

    void doAction(void(IScene::*action)());

    void doStart();
    void doStep();
    void togglePause();
    void doPause();
    void doResume();

    void moveLeft();
    void moveRight();

    void rotateDown();
    void rotateUp();

    void doDrop(bool enabled);

    void doSave();
    void doLoad();

public slots:
    void setSpeed(const QString& speed);

signals:
    void speedChanged(size_t);

private:
    IScene  *_model;
    IView   *_view;
    QTimer  _timer;
};

#endif // CONTROLLER_H
