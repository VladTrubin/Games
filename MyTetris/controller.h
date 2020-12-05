#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class IModel;
class IView;

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(IModel *model, IView *view, QObject *parent = nullptr);

    void doStep();
    void doPause();
    void doResume();
    void moveLeft();
    void moveRight();
    void doRotate();

    void doSave();
    void doLoad();


private:
    IModel  *_model;
    IView   *_view;
};

#endif // CONTROLLER_H
