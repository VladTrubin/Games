#include "scenemodel.h"
#include "figure.h"

#include <QtDebug>

Scene::Scene(size_t rows, size_t columns, QWidget *parent) : IScene(parent),
    _rows(rows), _columns(columns)
{
    // Set with revert order by rows
//    _same = Same([](const pair& l, const pair& r) { return (l.first > r.first) || ((l.first == l.second) && (l.second > r.second)); });
    _same = Same();

    _grid.resize(rows);
    for (size_t r = 0; r < rows; ++r)
    {
        _grid[r].resize(columns);
    }
    clear();

    // Here we can apply the factory method (for example)
    _currFig  = new FigureV();
    _nextFig  = new FigureV();
}

Scene::~Scene()
{
    delete _currFig;
    delete _nextFig;
}

void Scene::clear()
{
    for (size_t r = 0; r < _rows; ++r)
    {
        _grid[r].fill(emptyCell);
        for (size_t c = 0; c < _columns; ++c)
        {
            _grid[r][c] = emptyCell;
        }
    }
}

void Scene::doStep()
{
    if (not _gameOn)
        return;

    // Столкновение снизу
    if ((_currFig->row()+_currFig->cells() == _rows) or
            (_grid[_currFig->row()+_currFig->cells()][_currFig->column()] != emptyCell))
    {
        if (_currFig->row() == 0)
        {
            _gameOn = false;
            _currFig->setHide(true);    _nextFig->setHide(true);
            emit upCurrFigure();        emit upNextFigure();
            clear();
            return;
        }

        // Добавляем цвета фигуры на сетку
        for (size_t i = 0; i < _currFig->cells(); ++i)
        {
            _grid[_currFig->row()+i][_currFig->column()] = _currFig->colors()[i];
        }

        // Ищем рядом стоящих близнецов:)
        QColor prevColor;
        for (size_t i = 0; i < _currFig->cells(); ++i)
        {
            QColor curColor = _grid[_currFig->row()+i][_currFig->column()];
            if (curColor == prevColor)
            {
                prevColor = curColor;
                continue;
            }

            findSame(_currFig->row()+i, _currFig->column(), _currFig->row()+i, _currFig->column());
            if (_same.size() >= cellsForFire)
            {
                setScore(_score+_same.size());
                burn();
            }
            _same.clear();
        }

        // настраиваем фигуры после столкновения
        _currFig->getColors(_nextFig);
        setInitFigPos(_currFig);

        _nextFig->makeRandomColors();
        emit upNextFigure();
    }
    else    // Нет столкновения - идем дальше
    {
        _currFig->setRow(_currFig->row()+1);
    }

    emit upCurrFigure();
}



void Scene::findSame(size_t curRow, size_t curCol, size_t oldRow, size_t oldCol)
{
    _same.insert(std::make_pair(curRow, curCol));

    size_t newRow = curRow-1, newCol = curCol;
    if (test(newRow, newCol, oldRow, oldCol))
    {
        findSame(newRow, newCol, curRow, curCol);
    }

    newRow = curRow+1, newCol = curCol;
    if (test(newRow, newCol, oldRow, oldCol))
    {
        findSame(newRow, newCol, curRow, curCol);
    }

    newRow = curRow, newCol = curCol-1;
    if (test(newRow, newCol, oldRow, oldCol))
    {
        findSame(newRow, newCol, curRow, curCol);
    }

    newRow = curRow, newCol = curCol+1;
    if (test(newRow, newCol, oldRow, oldCol))
    {
        findSame(newRow, newCol, curRow, curCol);
    }
}


bool Scene::test(size_t curRow, size_t curCol, size_t oldRow, size_t oldCol)
{
    if (curRow >= _rows or curCol >= _columns or _grid[curRow][curCol] == emptyCell)
        return false;

    if (_grid[curRow][curCol] != _grid[oldRow][oldCol])
        return false;

    if (_same.find({curRow, curCol}) != _same.end())
        return false;

    if ((curRow == oldRow) && (curCol == oldCol))
        return false;

    return true;
}


void Scene::burn()
{
    // Здесь можно подумать над анимацией
    for (auto& cell : _same)
    {
        size_t row = cell.first;
        size_t col = cell.second;
        while ((row > 0) and (_grid[row-1][col] != emptyCell))
        {
            _grid[row][col] = _grid[row-1][col];
            --row;
        }

        _grid[row][col] = emptyCell;
    }

    // Функционал для повторной отчистки
    auto oldSame = _same;
    _same.clear();

    for (auto& cell : oldSame)
    {
        findSame(cell.first, cell.second, cell.first, cell.second);
        if (_same.size() >= cellsForFire)
            burn();
        _same.clear();
    }
}



void Scene::moveRight()
{
    size_t col = _currFig->column()+1;
    if (col >= _columns)
        return;

    bool canRight = true;
    for (size_t i = 0; i < _currFig->cells(); ++i)
    {
        size_t row = _currFig->row()+i;
        canRight &= (_grid[row][col] == emptyCell);
    }

    if (canRight)
    {
        _currFig->setColumn(_currFig->column()+1);
    }
}

void Scene::moveLeft()
{

    if (_currFig->column() == 0)
        return;

    size_t col = _currFig->column()-1;

    bool canLeft = true;
    for (size_t i = 0; i < _currFig->cells(); ++i)
    {
        size_t row = _currFig->row()+i;
        canLeft &= (_grid[row][col] == emptyCell);
    }

    if (canLeft)
    {
        _currFig->setColumn(_currFig->column()-1);
    }
}

void Scene::rotateUp()
{
    _currFig->rotateColors(Direction::UP);
}

void Scene::rotateDown()
{
    _currFig->rotateColors(Direction::DOWN);
}

void Scene::setSpeed(size_t speed)
{
    _speed = speed;
    // TODO to realize the acceleration of the game
}



void Scene::newGame()
{
    _gameOn = true;
    clear();
    setScore(0u);

    // формирование текущей фигурки
    _currFig->makeRandomColors();
    setInitFigPos(_currFig);

    // формирование следующей фигурки
    _nextFig->makeRandomColors();
    _nextFig->setRow(0u);
    _nextFig->setColumn(0u);

    // Флаги видимости фигур
    _currFig->setHide(false);    _nextFig->setHide(false);
    emit upNextFigure();         emit upCurrFigure();
}

void Scene::setScore(size_t score)
{
    _score = score;
    emit scoreChanged(_score);
}

void Scene::setInitFigPos(FigureV *figure)
{
    figure->setRow(0u);
    figure->setColumn(_columns/2);
}
