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

using FReal = double;
using FType = complex<FReal>;

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

//A fourier series can be expressed as FS = A0 * e^(2*PI*0) + A1 * e^(2*PI*1) + A2 * e^(2*PI*2) + ....
//where Fn = e^(2*PI*n) is represented with FTerm
//An = Fourient co-efficient of nth term represented with FType
//FS is a function of time and cabe be evaluated for a time t as FT(t)
struct FTerm
{
    FReal amp{1.}; //amplitude
    FReal f{1.};   //frequency
    FReal startangle{0}; //phase angle
    FReal freq()const { return f;}
    FTerm(FReal a,FReal f=1,FReal p=0):amp(a),f(f),startangle(p){}
    //function that evaluate the FTerm at time t and returns resulting vector in complex plane : Fn(t)
    FType operator ()(FReal t)const
    {
        return amp* FType{cos(startangle+ freq()* t),sin(startangle+ freq()* t)};
    }
    //connector that composes vector in complex plain and a Fourier terms: Vn= Vi + Fn(t)
    // return an evaluator  that can converts time in to vector in complex plane
    friend auto operator + (const FType& pos,const FTerm& term)
    {
        return [=](FReal t){
            return pos + term(t);
        };
    }
    //symmetric function for + operator: Vn =Fn(t) + Vi
    friend auto operator + (const FTerm& term,const FType& pos)
    {
        return pos + term;
    }
    //connector that composes two fourier terms: F_S= ( Fn + Fn+1)(t)
    // return an evaluator that can convert time in to a vector in complex plain
    // the time function is an interpolator ,which can be implemented by the client to return time
    //and a callable ,which can be use to draw the intermediate frequencies (epi circles)
    friend auto operator + (const FTerm& term1,const FTerm& term2)
    {
        return [=](FInterpolator ip){
            auto center = term1(ip.time());
            auto per=  center + term2(ip.time());
            ip(FType{0.0,0.0},center,term1.amp);
            ip(center,per,term2.amp);
            return per;

        };
    }
    //mltiplier that connect complex co-coefficient and and frequency component in a fourier term: Fn = An * e^(2*PI*n)
    friend auto operator * (const FType& com,const FTerm& term)
    {
        FReal mag = std::abs<FReal>(com);
        FReal ang = std::arg<FReal>(com);
        return FTerm{term.amp* mag,term.f,ang};

    }
    //symmetric function for * Fn = e^(2*PI*n) *An
    friend auto operator * (const FTerm& term,const FType& com)
    {

        return com*term;

    }
    //steaming operator for debug logs
    template<typename STreamer>
    friend STreamer& operator << (STreamer& os,const FTerm& pt)
    {
        os<<"FTerm{" << pt.amp<<" , " <<pt.freq()<<" , "<< pt.startangle <<"}";
        return os;
    }
};
//Input
// r: the range of FTerms that repersents the terms in fourier series
// start: starting vector to appropriately position the resulting signal in the plane.
// time: the time for which the fourier series should be evaluated
// fun : the drawing call back which user can implement to draw the epic-circles and arrows
// representing frequency component.
// Output : is the final vector computed after adding up all the terms in the series.
template <typename Range,typename DrawFun>
auto F_S(const Range& r, const FType& start, FReal time,DrawFun fun ){
       return  std::accumulate(begin(r),end(r),start,[&](auto& pos, auto& term){
                 auto c = (pos+term)(time);
                 fun(pos,c,term.amp);
                 return c;
             });
}


template <typename R>
auto D_F_T(const R& data,FReal initialphase=0.){
    std::vector<FTerm> terms;
    auto N = std::distance(begin(data),end(data));
     std::transform(begin(data),end(data),std::back_inserter(terms),[&,f=0.0](auto )mutable{
       auto type = std::accumulate(begin(data),end(data),FType{0.,0.},[&,innerfreq=0.](auto sofar,auto current)mutable{
            auto phi = Tou * innerfreq++ * f /N;
            sofar += current * FType{cos(phi),-sin(phi)};
            return sofar;
        });

        type=type * (1./N);

        return FTerm{std::abs(type),f++,std::arg(type)+initialphase};
    });
    return terms;

}
using FSymbol = std::function<FType( FInterpolator )>;
inline FSymbol operator +(FSymbol sym, FTerm term){
    return [sym = std::move(sym),term=std::move(term)]( FInterpolator ip){
        auto center = sym(ip);
        auto per=  center + term (ip.time());
        ip(center,per,term.amp);
        return per;
    };
}
template<typename R1,typename R2,typename R3,typename CombFunc >
void combine (R1 r1,R2 r2, R3 dest, CombFunc func){
         std::inner_product(begin(r1),end(r1),begin(r2),dest,[](auto dest,auto val){
           dest=val;return dest;
         },func);

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
