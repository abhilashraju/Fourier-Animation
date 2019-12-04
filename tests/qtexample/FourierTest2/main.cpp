
#include <QApplication>
#include <QWidget>
#include <deque>
#include "fourier.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include "fourierdraw.h"
using namespace FourierLiterals;

struct Widget:public QWidget{

    QTimer timer;
    std::deque<FType> targetWave;
    FReal time{0.};
    std::vector<FSymbol> syms;
    std::vector<FSymbol>::iterator iter;
   Widget(){
       FTerm t1{50,1.};
       syms.emplace_back(t1 + std::polar(2.,PI/2.) * t1 + (1.+2.i)*t1 + FTerm{50,3});
       syms.emplace_back( 150._A*4/PI * 1._F + 150._a*4/(3*PI) * 3._F + 150._A*4/(5*PI) * 5._F);
       syms.emplace_back(200._A * 1._F + 50._A * 2._F + 75._A * 3._F + 25._A * -4._F + 50._A * -2._F);
       syms.emplace_back(200._A * -1._F + 50._A * -2._F + 75._A * 3._F + 25._A * -4._F + 50._A * 7._F);
       syms.emplace_back(200._A * 1._F + 50._A * -2._F + 75._A * 3._F + 25._A * -3._F + 50._A * -3._F);
       syms.emplace_back(200._A * 1._F + 50._A * -2._F + 75._A * -4._F + 25._A * -2._F + 50._A * -6._F);
       syms.emplace_back(200._A * 1._F + 20._A * -2._F + 75._A * 4._F + 25._A * -5._F + 100._A * -3._F);

       timer.connect(&timer,&QTimer::timeout,[=](){
            time+=  0.01;
            if(time >=Tou) {
                if(++iter!=syms.end()){
                    targetWave.clear();
                    time=0.;
                }else {
                    iter=syms.begin();
                }
            }
            update();

        });
        timer.setSingleShot(false);
        timer.setInterval(10ms);
        timer.start();
        iter=syms.begin();
    }
    void paintEvent(QPaintEvent *event)
    {
        QPainter p(this);
        p.fillRect(rect(),Qt::white);
        QPen pen(Qt::red);
        pen.setWidth(3);
        p.setPen(pen);
        QPointF offset(400,400);
        auto epiCircleDraw =make_epiCircleDraw<QPainter,QPointF>(p,offset);
        auto handleDraw=make_handleDraw<QPainter,QPointF>(p,offset);
        auto drawWave=make_drawWave<QPainter,QPointF,QPainterPath>(p);
        auto drawTrace=make_drawTrace<QPainter,QPointF,QPainterPath>(p);

        targetWave.emplace_front(FType{offset.x(),offset.y()}+ (*iter)(FInterpolator(time,handleDraw)));


        if(targetWave.size()>1000){
            targetWave.erase(targetWave.end()-1);

        }
        pen.setWidth(5);

        drawTrace(targetWave);

    }

};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(1500,800);
    w.show();

    return a.exec();
}
