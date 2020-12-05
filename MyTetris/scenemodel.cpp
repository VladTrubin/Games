#include "scenemodel.h"

Scene::Scene(size_t rows, size_t columns, QWidget *parent) : IModel(parent),
    _rows(rows), _columns(columns)
{
    _cells = QVector<QVector<QColor>>(rows);
    for (size_t i = 0; i < rows; ++i)
    {
        _cells[i] = QVector<QColor>(columns);
        for (size_t j = 0; j < columns; ++j)
        {
            _cells[i][j] = emptyCell;
        }
    }

    // Here we can apply the factory pattern
    _cur = new
}
