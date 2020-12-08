#ifndef FIGUREVIEW_H
#define FIGUREVIEW_H

#include <QWidget>

class FigureV;

class FigureView : public QWidget
{
    Q_OBJECT
public:
    explicit FigureView(QWidget *parent = nullptr, FigureV *figure = nullptr, size_t sideLen = 30);

    virtual void paintEvent(QPaintEvent *event) override;
            void drawFigure();
            void setMovable(bool movable)   { _movable = movable;   }

//public slots:
//    void newFigure();

private:
    FigureV *_figure;
    size_t  _sideLen;
    bool    _movable{false};
};

#endif // FIGUREVIEW_H
