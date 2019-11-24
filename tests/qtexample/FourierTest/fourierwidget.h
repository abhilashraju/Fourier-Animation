#ifndef FOURIERWIDGET_H
#define FOURIERWIDGET_H

#include <QWidget>
#include "fourier.h"
#include <deque>
#include <vector>
#include <QTimer>

class FourierWidget : public QWidget
{
    Q_OBJECT

public:
    enum DrawMode
    {
        DrawX,
        DrawY,
        DrawXY
    };
    explicit FourierWidget(QWidget *parent = nullptr);
    ~FourierWidget();
    void paintEvent(QPaintEvent *event);
    void addFourierTerm(const std::vector<FTerm>& t);
    void setDrawMode(DrawMode m);

private:
    int middlex{100};
    FReal time;
    QTimer timer;
    std::deque<FType> targetWave;
    std::vector<FTerm> terms;
    DrawMode dmode{DrawXY};
};

#endif // FOURIERWIDGET_H
