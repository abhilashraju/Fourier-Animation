
#include <QApplication>
#include <QWidget>
#include <deque>
#include "fourier.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
using namespace FourierLiterals;



struct Widget:public QWidget{

    QTimer timer;
    std::deque<FType> targetWave;
    FReal time{0.};
    Widget(){
        FTerm t1{50,1.};
      sym=t1 + std::polar(2.,PI/2.) * t1 + (1.+2.i)*t1 + FTerm{50,3};
//       sym =  50._A*4/PI * 1._F + 50._a*4/(3*PI) * 3._F + 50._A*4/(5*PI) * 5._F;
//        sym =  100._A * 1._F + 100._A * 2._F + 100._A * 3._F + 100._A * -4._F + 50._A * -5._F;
        timer.connect(&timer,&QTimer::timeout,[=](){
            time+=0.01;



            update();
        });
        timer.setSingleShot(false);
        timer.setInterval(30ms);
        timer.start();
    }
    void paintEvent(QPaintEvent *event)
    {
        QPainter p(this);
        p.fillRect(rect(),Qt::white);
        QPen pen(Qt::red);
        pen.setWidth(3);
        QPointF offset(400,400);
        targetWave.emplace_front(FType{offset.x(),offset.y()}+ sym(FInterpolator(time,[&](auto c,auto per,auto amp){
            p.drawEllipse(offset+QPointF{c.x(),c.y()},amp,amp);
            p.drawLine(offset+QPointF{c.x(),c.y()},offset+QPointF{per.x(),per.y()});
        })));
        if(targetWave.size()>500){
            targetWave.erase(targetWave.end()-1);

        }
        QPainterPath path;

        if(targetWave.size()){
           pen.setColor(Qt::green);

            p.setPen(pen);
            auto start= targetWave.front();
            path.moveTo(QPointF{start.x(),start.y()});
            for(auto& pos:targetWave){
                path.quadTo({start.x(),start.y()},QPointF{pos.x(),pos.y()});
                start =pos;
            }
            p.drawPath(path);
        }

    }
    FSymbol sym;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(1500,800);
    w.show();

    return a.exec();
}
