
#include <QApplication>
#include <QWidget>
#include <deque>
#include "fourier.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <numeric>
#include "fourierdraw.h"
#include <QMouseEvent>
#include <QPainterPath>
using namespace FourierLiterals;

struct Widget:public QWidget{

    QTimer timer;
    std::deque<FType> targetWave;
    FReal time{0.};
    std::vector<FTerm> terms;
    Widget(){

         timer.connect(&timer,&QTimer::timeout,[=](){
            time+=  Tou/terms.size();
            time = (time >Tou)?0.:time;
            if(!time){targetWave.clear();}
            update();

        });
        timer.setSingleShot(false);
        timer.setInterval(10ms);
        timer.start();

    }
    void paintEvent(QPaintEvent* )
    {
        QPainter p(this);
        p.fillRect(rect(),Qt::black);
        QPen pen(Qt::red);
        pen.setWidth(3);
        p.setPen(pen);




        pen.setWidth(5);
        pen.setColor(Qt::red);
        p.setPen(pen);
        if(!inputvectors.size() && !terms.size()){
            p.setFont(QFont("Times New Roman",10,2,true));
             p.drawText(QPointF(width()/2,height()/2),"Draw figure by not lifting your hand");
        }
        if(inputvectors.size()){
            QPainterPath path;
            auto start= inputvectors.front()+QPoint(width()/2,height()/2);
            path.moveTo(start);
            for(auto& pos:inputvectors){
                path.quadTo(start,pos+QPoint(width()/2,height()/2));
                start =pos+QPoint(width()/2,height()/2);
            }
            p.drawPath(path);
        }
        pen.setColor(Qt::white);
        p.setPen(pen);
        if(terms.size()){
            auto epiCircleDraw =make_epiCircleDraw<QPainter,QPointF>(p);
            auto handleDraw=make_handleDraw<QPainter,QPointF>(p);
            auto drawTrace=make_drawTrace<QPainter,QPointF,QPainterPath>(p);
            auto values1 = make_Values(time,QPointF(width()/2,height()/2),terms,epiCircleDraw,2000)(targetWave);
            pen.setColor(Qt::red);
            p.setPen(pen);
            drawTrace(values1);
        }



    }
    void mouseMoveEvent(QMouseEvent *event)
    {
        inputvectors.emplace_back(event->pos()-QPoint(width()/2,height()/2));
    }
    void mousePressEvent(QMouseEvent *event)
    {
        inputvectors.clear();
        terms.clear();
        targetWave.clear();
        inputvectors.emplace_back(event->pos()-QPoint(width()/2,height()/2));
    }
    void mouseReleaseEvent(QMouseEvent *event)
    {
        std::vector<FType> vals;
        std::transform(begin(inputvectors),end(inputvectors),std::back_inserter(vals),[](auto v){
               return FType{v.x(),v.y()};

        });
        inputvectors.clear();
       terms= D_F_T(vals);
       std::sort(begin(terms),end(terms),[](auto v1, auto v2){
           return v1.amp > v2.amp;
       });
    }
    std::vector<QPointF> inputvectors;
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(1500,800);
    w.show();

    return a.exec();
}
