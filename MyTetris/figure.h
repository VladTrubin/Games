#ifndef FIGURE_H
#define FIGURE_H

//#include <QColor>
#include <QGradient>

enum Direction : unsigned char { DOWN, UP };
static constexpr size_t colorsN = 6;

//SeaStrike     MagicRay    LandingAircraft     DenseWater
//static const QColor colorsT[colorsN] {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::magenta, Qt::cyan};

static const QGradient::Preset colorsT[colorsN] {QGradient::ItmeoBranding, QGradient::ShyRainbow,
    QGradient::PaloAlto, QGradient::OctoberSilence, QGradient::FabledSunset, QGradient::PhoenixStart};


class IFigure
{
public:
    virtual ~IFigure() = 0;
};

class FigureV : public IFigure
{
protected:
    static constexpr size_t cellsN = 3;

public:
    FigureV();
    virtual ~FigureV();

    void setRow(size_t row)         { _row    = row;    }
    void setColumn(size_t column)   { _column = column; }
    void setHide(bool hide)         { _hide   = hide;   }

    const QGradient::Preset* colors()  { return _colors;   }

    inline size_t row()     { return _row;      }
    inline size_t column()  { return _column;   }
    inline size_t cells()   { return cellsN;    }
    inline bool   isHide()  { return _hide;     }

    void rotateColors(Direction dir);
    void makeRandomColors();
    void getColors(FigureV *other);

private:
    //! Indexes for top position of a FigureV
    size_t _row, _column;
    //! Colors for cells
//    QColor  _colors[cellsN];
    QGradient::Preset  _colors[cellsN];

    bool    _hide{true};
};

#endif // FIGURE_H
