#ifndef FOURIERDRAW_H
#define FOURIERDRAW_H
#include "fourier.h"
template<typename Painter,typename Point>
auto make_epiCircleDraw (Painter& p)
{
    return [&](const FType& c,const FType& per,FReal amp){
        p.drawEllipse(Point{c.x(),c.y()},amp,amp);
        p.drawLine(Point{c.x(),c.y()},Point{per.x(),per.y()});
    };
    
}
template<typename Painter,typename Point>
 auto make_handleDraw(Painter& p)
 {
      return [&](const FType& c,const FType& per,FReal amp){
          p.drawLine(Point{c.x(),c.y()},Point{per.x(),per.y()});
        
      };
 }
template<typename Point,typename Source,typename DrawFun>         
auto make_Values(FReal t, const Point& offset ,const Source& terms, DrawFun draw){
    return [=](auto& wave)->const decltype(wave)& {
        wave.emplace_front(F_S(terms,{offset.x(),offset.y()},t,draw));
        if(wave.size()>500){
            wave.erase(wave.end()-1);

        }
        return wave;
    };

};
template<typename Painter,typename Point,typename Path>
auto make_drawWave(Painter& p){
   return  [&p](const auto& wave,auto offset){
        if(wave.size()){
            Path path;
            path.moveTo(wave.front().x(),wave.front().y());
            auto start=Point{offset.x()+150,wave.front().y()};
            path.lineTo(start);
            for(auto& pos:wave){
                path.addEllipse(Point{start.x(),pos.y()},2,2);
                start = Point{start.x()+2,pos.y()};
            }
            p.drawPath(path);
        }
    };
} 
template<typename Painter,typename Point,typename Path>
auto make_drawTrace(Painter& p){
    return [&p](const auto& wave){
            if(wave.size()){
                Path path;
                auto start= wave.front();
                path.moveTo(Point{start.x(),start.y()});
                for(auto& pos:wave){
                    path.quadTo({start.x(),start.y()},Point{pos.x(),pos.y()});
                    start =pos;
                }
                p.drawPath(path);
            }

        };
} 
#endif //FOURIERDRAW_H