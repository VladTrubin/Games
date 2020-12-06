#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include <QWidget>
#include <QVector>

class IFigure;

class IScene : public QWidget
{
    Q_OBJECT
protected:
    static constexpr QColor emptyCell = QColor{150, 150, 150};

public:
    IScene(QWidget *parent = nullptr) : QWidget(parent) {   }

};


class Scene : public IScene
{
    Q_OBJECT
public:
    Scene(size_t rows, size_t columns, QWidget *parent = nullptr);
    virtual ~Scene();

    void clear();

private:
    QVector<QVector<QColor>>    _cells;
    IFigure                     *_cur, *_next;
    size_t                      _rows, _columns;
    size_t                      _score;
    bool                        _gameOn{false};
};

#endif // SCENEMODEL_H
