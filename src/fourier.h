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
       cout<<"PointF{" << pt.mx<<"," <<pt.my<<"}";
       return os;
   }
};

using FReal = double;
using FComplex = complex<FReal>;
using FType = PointF<FReal>;
struct FTerm
{
    FReal amp{1.};
    FReal freq{1.};
    FReal startangle{0};

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
auto FT(const Range& r, const FType& start, double time,DrawFun fun ){
       return  std::accumulate(begin(r),end(r),start,[&](auto& pos, auto& term){
                 auto c = (pos+term)(time);
                 fun(pos,c,term.amp);
                 return c;
             });
}

#endif // FOURIER_H
