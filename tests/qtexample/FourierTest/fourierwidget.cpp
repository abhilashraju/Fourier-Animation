#include "fourierwidget.h"
#include <QPainter>
FourierWidget::FourierWidget(QWidget *parent) :
    QWidget(parent)

{
    timer.connect(&timer,&QTimer::timeout,[=](){
        time+=0.01;
        update();
    });
    timer.setSingleShot(false);
    timer.setInterval(30ms);
    timer.start();


    resize(1000,700);
}
FourierWidget::~FourierWidget()
{

}
void FourierWidget::paintEvent(QPaintEvent *event)
{

    QPainter p(this);
    p.fillRect(rect(),Qt::black);



    QPointF middle = QPointF(250,height()/2);
    p.setPen(Qt::white);
    targetWave.emplace_front(FT(terms,{middle.x(),middle.y()},time,[&](auto start,auto r,auto amp)->void{
            p.drawEllipse(QPointF{start.x(),start.y()},amp,amp);
            p.drawLine(QPointF{start.x(),start.y()},QPointF{r.x(),r.y()});

    }));
    if(targetWave.size()>500){
        targetWave.erase(targetWave.end()-1);

    }
    QPainterPath path;
    switch (dmode) {
    case DrawXY:{
            auto start= targetWave.front();
            path.moveTo(QPointF{start.x(),start.y()});
            for(auto& pos:targetWave){
                path.quadTo({start.x(),start.y()},QPointF{pos.x(),pos.y()});
                start =pos;
            }
        }
        break;
    case DrawY:{

            path.moveTo(targetWave.front().x(),targetWave.front().y());
            auto start=QPointF{middle.x()+100,targetWave.front().y()};
            path.lineTo(start);
            for(auto& pos:targetWave){
                path.addEllipse(QPointF{start.x(),pos.y()},2,2);
                start = QPointF{start.x()+2,pos.y()};
            }
         }
        break;
    case DrawX:{

            path.moveTo(targetWave.front().x(),targetWave.front().y());
            auto start=QPointF{targetWave.front().x(),middle.y()+100};
            path.lineTo(start);
            for(auto& pos:targetWave){
                path.addEllipse(QPointF{pos.x(),start.y()},2,2);
                start = QPointF{pos.x(),start.y()+2};
            }
         }
        break;
    }

    p.drawPath(path);

}
void FourierWidget::addFourierTerm(const std::vector<FTerm>& t)
{
    std::copy(begin(t),end(t),std::back_inserter(terms));
}
void FourierWidget::setDrawMode(DrawMode m)
{
    dmode = m;
}
