#ifndef FIGUREVIEW_H
#define FIGUREVIEW_H

#include <QWidget>

class IFigure;

class FigureView : public QWidget
{
    Q_OBJECT
public:
    explicit FigureView(QWidget *parent = nullptr, IFigure *figure = nullptr);

            void drawFigure(QPainter *painter);
    virtual void paintEvent(QPaintEvent *event) override;

public slots:
    void newFigure();

private:
    IFigure *_figure;
};

#endif // FIGUREVIEW_H
