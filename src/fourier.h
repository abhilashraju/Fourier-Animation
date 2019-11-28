#ifndef FOURIER_H
#define FOURIER_H
/*MIT License

Copyright (c) 2019 abhilashraju

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <vector>
#include <complex>
#include <numeric>
#include <iostream>
#include <functional>
using namespace std;
using namespace std::complex_literals;
const auto PI = acos(-1);
const auto Tou= 2.*PI;


template<typename T>
struct PointF
{
   T mx;
   T my;

   PointF(double x,double y):mx(x),my(y){}
   T x()const {return mx;}
   T y()const {return my;}
   friend PointF operator * (double v, const PointF& pt){
       return PointF{pt.mx * v,pt.my *v};
   }
   friend PointF operator + (const PointF& pt1, const PointF& pt2){
       return PointF{pt1.mx+pt2.mx,pt1.my+pt2.my};
   }
   template<typename STreamer>
   friend STreamer& operator << (STreamer& os,const PointF& pt)
   {
       os<<"PointF{" << pt.mx<<"," <<pt.my<<"}";
       return os;
   }
};

using FReal = double;
using FComplex = complex<FReal>;
using FType = PointF<FReal>;

struct FInterpolator
{
    FReal mTime{0.0};
    std::function<void(FType,FType,FReal)> mFunc;

    FReal time()const{
        return  mTime;
    }
    void operator()(FType center, FType poinTAtPer,FReal amp)const{
        if(mFunc)
            mFunc(center,poinTAtPer,amp);
    }
    FInterpolator(FReal time,std::function<void(FType,FType,FReal)> func=std::function<void(FType,FType,FReal)>())
        :mTime(time),mFunc(func){

    }
};


struct FTerm
{
    FReal amp{1.};
    FReal freq{1.};
    FReal startangle{0};
    FTerm(FReal a,FReal f=1,FReal p=0):amp(a),freq(f),startangle(p){}
    friend FType operator * (const FTerm& term,FReal t)
    {
        return term.amp* FType{cos(term.startangle+Tou* term.freq* t),sin(term.startangle+Tou * term.freq* t)};
    }
    friend auto operator + (const FType& pos,const FTerm& term)
    {
        return [=](FReal t){
            return pos + term * t;
        };
    }
    friend auto operator + (const FTerm& term1,const FTerm& term2)
    {
        return [=](FInterpolator ip){
            auto center = term1*ip.time();
            auto per=  center + term2 * ip.time();
            ip(FType{0.0,0.0},center,term1.amp);
            ip(center,per,term2.amp);
            return per;

        };
    }
    friend auto operator + (const FTerm& term,const FType& pos)
    {
        return pos + term;
    }
    friend auto operator * (const FComplex& com,const FTerm& term)
    {
        FReal mag = std::abs<FReal>(com);
        FReal ang = std::arg<FReal>(com);
        return FTerm{term.amp* mag,term.freq,ang};

    }
    friend auto operator * (const FTerm& term,const FComplex& com)
    {

        return com*term;

    }
};
template <typename Range,typename DrawFun>
auto FT(const Range& r, const FType& start, FReal time,DrawFun fun ){
       return  std::accumulate(begin(r),end(r),start,[&](auto& pos, auto& term){
                 auto c = (pos+term)(time);
                 fun(pos,c,term.amp);
                 return c;
             });
}


using FSymbol = std::function<FType( FInterpolator )>;
inline FSymbol operator +(FSymbol sym, FTerm term){
    return [sym = std::move(sym),term=std::move(term)]( FInterpolator ip){
        auto center = sym(ip);
        auto per=  center + term * ip.time();
        ip(center,per,term.amp);
        return per;
    };
}

namespace  FourierLiterals{
struct FFreq
{
    long double f;
};
struct FAmp
{
    long double amp;
};
inline constexpr FFreq operator"" _f(long double v){
    return {v};
}
inline constexpr FAmp operator"" _a(long double v){
    return {v};
}
inline constexpr FFreq operator"" _F(long double v){
    return {v};
}
inline constexpr FAmp operator"" _A(long double v){
    return {v};
}
inline FTerm operator *(FAmp amp , FFreq f){
    FReal a= amp.amp;
    FReal fr=f.f;
    return  FTerm{a,fr};
}
inline FAmp operator * (FAmp a,FReal v){
    return {a.amp * v};
}
inline FAmp operator * (FReal v,FAmp a){
    return a * v;
}
inline FAmp operator / (FAmp a,FReal v){
    return {a.amp / v};
}
inline FAmp operator / (FReal v,FAmp a){
    return {v/a.amp};
}
inline FAmp operator + (FAmp a,FReal v){
    return {a.amp + v};
}
inline FAmp operator + (FReal v,FAmp a){
    return a + v;
}
inline FAmp operator - (FAmp a,FReal v){
    return {a.amp - v};
}
inline FAmp operator - (FReal v,FAmp a){
    return {v-a.amp};
}

inline FFreq operator * (FFreq f,FReal v){
    return {f.f * v};
}
inline FFreq operator * (FReal v,FFreq f){
    return f * v;
}
inline FFreq operator / (FFreq f,FReal v){
    return {f.f / v};
}
inline FFreq operator / (FReal v,FFreq a){
    return {v/a.f};
}
inline FFreq operator + (FFreq a,FReal v){
    return {a.f + v};
}
inline FFreq operator + (FReal v,FFreq a){
    return {a.f + v};
}
inline FFreq operator - (FFreq a,FReal v){
    return {a.f - v};
}
inline FFreq operator - (FReal v,FFreq a){
    return {v-a.f};
}
inline FFreq operator - (FFreq f){
    return {-f.f};
}


}
#endif // FOURIER_H
