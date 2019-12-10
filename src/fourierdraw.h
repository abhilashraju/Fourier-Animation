#ifndef FOURIERDRAW_H
#define FOURIERDRAW_H
#include "fourier.h"
template<typename Painter,typename Point>
auto make_epiCircleDraw (Painter& p,const Point& offset =Point())
{
    return [&](const FType& c,const FType& per,FReal amp){
        p.drawEllipse(offset +Point{c.real(),c.imag()},amp,amp);
        p.drawLine(offset+Point{c.real(),c.imag()},offset+Point{per.real(),per.imag()});
    };
    
}
template<typename Painter,typename Point>
 auto make_handleDraw(Painter& p,const Point& offset =Point())
 {
      return [&](const FType& c,const FType& per,FReal amp){
          p.drawLine(offset+Point{c.real(),c.imag()},offset+Point{per.real(),per.imag()});      
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
auto make_drawWave(Painter& p,int axis=1){
    return  [&p,&axis](const auto& wave,auto offset){
        if(wave.size()){
            Path path;
            path.moveTo(wave.front().real(),wave.front().imag());

            if(axis){
                auto start=Point{offset.x(),wave.front().imag()};
                path.lineTo(start);
                for(auto& pos:wave){
                    path.addEllipse(Point{start.x(),pos.imag()},2,2);
                    start = Point{start.x()+2,pos.imag()};
                }
            }else{
                auto start=Point{wave.front().real(),offset.y()};
                path.lineTo(start);
                for(auto& pos:wave){
                    path.addEllipse(Point{pos.real(),start.y()},2,2);
                    start = Point{pos.real()+2,start.y()};
                }
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
                path.moveTo(Point{start.real(),start.imag()});
                for(auto& pos:wave){
                    path.quadTo({start.real(),start.imag()},Point{pos.real(),pos.imag()});
                    start =pos;
                }
                p.drawPath(path);
            }

        };
} 
#endif //FOURIERDRAW_H
