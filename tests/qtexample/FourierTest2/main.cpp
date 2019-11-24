
#include <QApplication>
#include <QWidget>
#include <deque>
#include "fourier.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
struct Widget:public QWidget{

    QTimer timer;
    std::deque<FType> targetWave;
    FReal time{0.};
    Widget(){
//        FTerm t1{50,1.};
//        auto v=FType{300,300} +t1 + std::polar(2.,PI/2.) * t1 + (1.+2.i)*t1 + FTerm{50,3};
        auto v=FType{300,300} +FTerm{50,1} + FTerm{50,-1} + std::polar(2.,PI/2.) * FTerm{50,-1} + std::polar(2.,PI/4.) * FTerm{50,5};

        timer.connect(&timer,&QTimer::timeout,[=](){
            time+=0.01;

            targetWave.emplace_front(v(time));
            if(targetWave.size()>500){
                targetWave.erase(targetWave.end()-1);

            }

            update();
        });
        timer.setSingleShot(false);
        timer.setInterval(30ms);
        timer.start();
    }
    void paintEvent(QPaintEvent *event)
    {
        QPainter p(this);
        p.fillRect(rect(),Qt::black);
        QPainterPath path;

        if(targetWave.size()){
            p.setPen(Qt::white);
            auto start= targetWave.front();
            path.moveTo(QPointF{start.x(),start.y()});
            for(auto& pos:targetWave){
                path.quadTo({start.x(),start.y()},QPointF{pos.x(),pos.y()});
                start =pos;
            }
            p.drawPath(path);
        }

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
