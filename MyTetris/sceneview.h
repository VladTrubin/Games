#ifndef SCENEVIEW_H
#define SCENEVIEW_H

#include <QWidget>

class Controller;
class IScene;

class IView : public QWidget
{
    Q_OBJECT
protected:
    static constexpr size_t sizeCell = 50;

public:
    explicit IView(QWidget *parent) : QWidget(parent) { }
    virtual ~IView() = 0;
};

class SceneView : public IView
{
    Q_OBJECT
    Q_PROPERTY(uint rows      READ rows       WRITE setRows)
    Q_PROPERTY(uint columns   READ columns    WRITE setColumns)

public:
    explicit SceneView(QWidget *parent = nullptr);
    virtual ~SceneView();

    void setWidgetSize();
    void setModel(IScene *model)            { _model = model;       }
    void setController(Controller *ctrl)    { _controller = ctrl;   }

    size_t rows()                           { return _rows;         }
    size_t columns()                        { return _columns;      }
    size_t sideLen()                        { return sizeCell;      }

public slots:
    void   setRows(size_t rows)             { _rows = rows;         }
    void   setColumns(size_t columns)       { _columns = columns;   }

protected:
    virtual void paintEvent(QPaintEvent *event)         override;
    virtual void keyPressEvent(QKeyEvent *event)        override;
    virtual void keyReleaseEvent(QKeyEvent *event)      override;

    void drawScene(QPainter *painter);


private:
    IScene      *_model;
    Controller  *_controller;
    uint        _rows, _columns;
};

#endif // SCENEVIEW_H
