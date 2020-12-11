#ifndef SCENEMODEL_H
#define SCENEMODEL_H

#include <QWidget>
#include <QVector>
#include <set>

class FigureV;

using pair = std::pair<size_t, size_t>;
//using Same = std::set<pair, bool (*)(const pair&, const pair&)>;
using Same = std::set<pair>;
//using Grid = QVector<QVector<QColor>>;
using Grid = QVector<QVector<QGradient::Preset>>;

class IScene : public QObject
{
    Q_OBJECT
protected:
//    static constexpr QColor emptyCell = QColor{150, 150, 150, 150};
    static constexpr QGradient::Preset emptyCell = QGradient::Preset::PremiumDark;
    static constexpr size_t MinSpeed  = 1;
    static constexpr size_t MaxSpeed  = 10;

public:
    IScene(QObject *parent = nullptr) : QObject(parent) {   }
    virtual ~IScene() { }

    virtual bool    gameOn()    = 0;
    virtual Grid&   grid()      = 0;
    virtual void    newGame()   = 0;
    virtual void    doStep()    = 0;
    virtual void    moveRight() = 0;
    virtual void    moveLeft()  = 0;
    virtual void    rotateDown() {   }
    virtual void    rotateUp()   {   }

    virtual void    setSpeed(size_t)  = 0;
    virtual size_t  score()           = 0;
    virtual size_t  speed()           = 0;
    virtual size_t  maxSpeed()        = 0;
    virtual size_t  minSpeed()        = 0;

signals:
    void speedChanged(size_t);

protected:
    bool    _gameOn{false};
};


// ******************************************************************
class Scene : public IScene
{
    Q_OBJECT

    static constexpr size_t cellsForFire = 3;

public:
    Scene(size_t rows, size_t columns, QWidget *parent = nullptr);
    virtual ~Scene();

    void clear();

    bool    gameOn()   override  { return _gameOn;   }
    Grid&   grid()     override  { return _grid;     }
    size_t  score()    override  { return _score;    }
    size_t  speed()    override  { return _speed;    }
    size_t  maxSpeed() override  { return MaxSpeed;  }
    size_t  minSpeed() override  { return MinSpeed;  }

    FigureV* currFig()  { return _currFig;   }
    FigureV* nextFig()  { return _nextFig;   }

    void doStep()    override;
    void moveRight() override;
    void moveLeft()  override;

    void rotateUp()   override;
    void rotateDown() override;

    void setSpeed(size_t speed)  override;

private:
    void findSame(size_t curRow, size_t curCol, size_t oldRow = 0, size_t oldCol = 0);
    void finding();
    bool test(size_t newRow, size_t newCol, size_t oldRow, size_t oldCol);
    void burn();

public slots:
    void newGame() override;
    void setScore(size_t);

signals:
    void updateView();
    void scoreChanged(size_t);
    void upCurrFigure();
    void upNextFigure();
    void multiChanged(size_t);

private:
    void setInitFigPos(FigureV *figure);

private:
    Grid        _grid;
    Same        _same;
    FigureV     *_currFig, *_nextFig;
    size_t      _rows, _columns;
    size_t      _score{0u};
    size_t      _speed{MinSpeed};
    size_t      _multiplier{1};
    bool        _haveDrop{false}, _needMulti{false};
};

#endif // SCENEMODEL_H
