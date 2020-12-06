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
    static constexpr int stepTimeInterval = 444;

public:
    explicit Controller(IScene *model, IView *view, QObject *parent = nullptr);

    void doStart();
    void doStep();
    void doPause();
    void doResume();

    void moveLeft();
    void moveRight();

    void colorDown();
    void colorUp();

    void doDrop(bool enabled);

    void doRotate();

    void doSave();
    void doLoad();

public slots:
    void setSpeed(const QString& speed);

private:
    IScene  *_model;
    IView   *_view;
    QTimer  _timer;
};

#endif // CONTROLLER_H
