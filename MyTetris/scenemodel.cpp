#include "scenemodel.h"
#include "figure.h"


Scene::Scene(size_t rows, size_t columns, QWidget *parent) : IScene(parent),
    _rows(rows), _columns(columns)
{
    // Set with revert order by rows
    _same = Same([](const pair& l, const pair& r) { return l.first > r.first; });

    _grid.resize(rows);
    for (size_t r = 0; r < rows; ++r)
    {
        _grid[r].resize(columns);
    }
    clear();

    // Here we can apply the factory method (for example)
    _curFig  = new FigureV();
    _nextFig = new FigureV();
}

Scene::~Scene()
{
    delete _curFig;
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

    // TODO Буем ли здесь обнулять счет игры? и gameOn?
}

void Scene::doStep()
{
    if (not _gameOn)
        return;

    int speed = _haveDrop ? maxSpeed : _speed;
    _curFig->setRow(_curFig->row()+speed);

    if (_grid[_curFig->row()+3][_curFig->column()] != emptyCell)
    {
        QColor prevColor;
        for (size_t i = 0; i < _curFig->cells(); ++i)
        {
            QColor curColor = _grid[_curFig->row()+i][_curFig->column()];
            if (curColor == prevColor)
            {
                prevColor = curColor;
                continue;
            }

//            _same.insert(_curFig->row()+i, _curFig->column());
            findSame(_curFig->row()+i, _curFig->column());
            if (_same.size() >= cellsForFire)
                burn();
            _same.clear();
        }
    }
}

void Scene::moveRight()
{
    size_t col = _curFig->column()+1;
    if (col >= _columns)
        return;

    bool canRight = true;
    for (size_t i = 0; i < _curFig->cells(); ++i)
    {
        size_t row = _curFig->row()+i;
        canRight &= (_grid[row][col] == emptyCell);
    }

    if (canRight)
    {
        for (size_t i = 0; i < _curFig->cells(); ++i)
        {
            size_t row = _curFig->row()+i;
            qSwap(_grid[row][col-1], _grid[row][col]);
        }
    }
}

void Scene::moveLeft()
{

    if (_curFig->column() == 0)
        return;

    size_t col = _curFig->column()-1;

    bool canLeft = true;
    for (size_t i = 0; i < _curFig->cells(); ++i)
    {
        size_t row = _curFig->row()+i;
        canLeft &= (_grid[row][col] == emptyCell);
    }

    if (canLeft)
    {
        for (size_t i = 0; i < _curFig->cells(); ++i)
        {
            size_t row = _curFig->row()+i;
            qSwap(_grid[row][col+1], _grid[row][col]);
        }
    }
}

void Scene::startDrop()
{
    // TODO можно реализовать в контроллере за счет ускорения времени?
}

void Scene::stopDrop()
{

}

void Scene::colorUp()
{
    size_t row = _curFig->row(), col = _curFig->column();
    qSwap(_grid[row][col], _grid[row+2][col]);
    qSwap(_grid[row][col], _grid[row+1][col]);
}

void Scene::colorDown()
{
    size_t row = _curFig->row(), col = _curFig->column();
    qSwap(_grid[row][col],   _grid[row+2][col]);
    qSwap(_grid[row][col+1], _grid[row+2][col]);
}

void Scene::setSpeed(size_t speed)
{
    _speed = speed;
    // TODO to realize the acceleration of the game
}

void Scene::findSame(size_t row, size_t col)
{
    if (row >= _rows or col >= _columns)
        return;

    if (not _same.empty())
    {
        auto& curCoor = (*_same.begin());
        if (_grid[row][col] != _grid[curCoor.first][curCoor.second])
        {
            return;
        }
    }
    else
    {
        _same.insert(std::make_pair(row, col));
    }

    findSame(row-1, col);
    findSame(row+1, col);
    findSame(row,   col-1);
    findSame(row,   col+1);
}

void Scene::burn()
{
    for (auto& cell : _same)
    {
        size_t row = cell.first;
        while ((row > 0) and (_grid[row-1][cell.second] != emptyCell))
        {
            _grid[row][cell.second] = _grid[row-1][cell.second];
            --row;
        }
    }
}


void Scene::newGame()
{
    _gameOn = true;
    clear();

    // формирование текущей фигурки
    _curFig->makeRandomColors();
    _curFig->setRow(0u);
    _curFig->setColumn(_columns/2);

    // формирование следующей фигурки
    _nextFig->makeRandomColors();
    _nextFig->setRow(0u);
    _nextFig->setColumn(0u);
}
