#include "scenemodel.h"
#include "figure.h"


Scene::Scene(size_t rows, size_t columns, QWidget *parent) : IScene(parent),
    _rows(rows), _columns(columns)
{
    _cells.resize(rows);
    for (size_t r = 0; r < rows; ++r)
    {
        _cells[r].resize(columns);
    }
    clear();

    // Here we can apply the factory method (for example)
    _cur  = new FigureV();
    _next = new FigureV();
}

Scene::~Scene()
{
    delete _cur;
    delete _next;
}

void Scene::clear()
{
    for (size_t r = 0; r < _rows; ++r)
    {
        _cells[r].fill(emptyCell);
        for (size_t c = 0; c < _columns; ++c)
        {
            _cells[r][c] = emptyCell;
        }
    }

    // TODO Буем ли здесь обнулять счет игры? и gameOn?
}
