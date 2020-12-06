#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include <QWidget>
#include <QVector>
#include <set>

class FigureV;

using pair = std::pair<size_t, size_t>;
using Same = std::set<pair, bool (*)(const pair&, const pair&)>;
using Grid = QVector<QVector<QColor>>;

class IScene : public QObject
{
    Q_OBJECT
protected:
    static constexpr QColor emptyCell = QColor{150, 150, 150};

public:
    IScene(QObject *parent = nullptr) : QObject(parent) {   }
    virtual ~IScene() { }

    virtual bool    gameOn()    = 0;
    virtual Grid&   grid()      = 0;
    virtual void    newGame()   = 0;
    virtual void    doStep()    = 0;
    virtual void    moveRight() = 0;
    virtual void    moveLeft()  = 0;
    virtual void    startDrop() = 0;
    virtual void    stopDrop()  = 0;
    virtual void    colorDown() {   }
    virtual void    colorUp()   {   }

    virtual void    setSpeed(size_t)  = 0;
    virtual size_t  score()           = 0;

protected:
    bool    _gameOn{false};
};


// ******************************************************************
class Scene : public IScene
{
    Q_OBJECT

    static constexpr size_t minSpeed     = 1;
    static constexpr size_t maxSpeed     = 10;
    static constexpr size_t cellsForFire = 3;

public:
    Scene(size_t rows, size_t columns, QWidget *parent = nullptr);
    virtual ~Scene();

    void clear();

    bool    gameOn()  override  { return _gameOn;   }
    Grid&   grid()    override  { return _grid;     }
    size_t  score()   override  { return _score;    }

    void doStep()    override;
    void moveRight() override;
    void moveLeft()  override;

    void startDrop() override;
    void stopDrop()  override;

    void colorUp()   override;
    void colorDown() override;

    void setSpeed(size_t speed)  override;

private:
    void findSame(size_t row, size_t col);
    void finding();
    void burn();

public slots:
    void newGame() override;

signals:
    void updateView();

private:
    Grid        _grid;
    Same        _same;
    FigureV     *_curFig, *_nextFig;
    size_t      _rows, _columns;
    size_t      _score;
    size_t      _speed{minSpeed};
    bool        _haveDrop{false};
};

#endif // SCENEMODEL_H
