#include "fourierwidget.h"
#include <QPainter>
#include "fourierdraw.h"
#include <QPainterPath>
FourierWidget::FourierWidget(QWidget *parent) :
    QWidget(parent)

{
    timer.connect(&timer,&QTimer::timeout,[=](){
        time+=0.02;
        update();
    });
    timer.setSingleShot(false);
    timer.setInterval(16ms);
    timer.start();



}
FourierWidget::~FourierWidget()
{

}
void FourierWidget::paintEvent(QPaintEvent *event)
{

    QPainter p(this);
    p.fillRect(rect(),Qt::black);



    QPointF middle = QPointF(300,height()/2);
    QPen pen(Qt::white);
    pen.setWidth(2);
    p.setPen(pen);
    auto epiCircleDraw =make_epiCircleDraw<QPainter,QPointF>(p);
    auto handleDraw=make_handleDraw<QPainter,QPointF>(p);

    auto values1 = make_Values(time,middle+QPointF(200,-200),terms,epiCircleDraw)(targetWave);


    pen.setColor(Qt::red);

    p.setPen(pen);
    switch( dmode){
    case DrawX:
         make_drawWave<QPainter,QPointF,QPainterPath>(p,0)(values1,middle);

        break;
        case DrawY:
        make_drawWave<QPainter,QPointF,QPainterPath>(p,1)(values1,middle+QPointF{300,0});
        break;
        case DrawXY:
        make_drawTrace<QPainter,QPointF,QPainterPath>(p)(values1);
        break;
    }



}
void FourierWidget::addFourierTerm(const std::vector<FTerm>& t)
{
    std::copy(begin(t),end(t),std::back_inserter(terms));
}
void FourierWidget::setDrawMode(DrawMode m)
{
    dmode = m;
}
