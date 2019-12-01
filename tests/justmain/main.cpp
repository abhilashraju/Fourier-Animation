#include "../../src/fourier.h"
#include <iostream>
int main(int argc, char *argv[])
{
    FTerm t1{50,1.};
       std::vector<FTerm> terms;
       terms.push_back(t1);
       terms.emplace_back(std::polar(2.,PI/2.) * t1);
       terms.emplace_back((1.+2.i)*t1);
       terms.emplace_back(FTerm{50,3});
       int epiccirle{0};
       auto callback = [=](auto center, auto pointAt, auto amp)mutable{
           std::cout<<" Inner Circle: "<<epiccirle << " center: " << center << " pointAt time 0.05: " << pointAt << " amplitude: " <<amp<<"\n";
           epiccirle++;
       };
       std::cout<<F_S(terms,{10,10},0.05,callback) << endl;
       
       //symbolic expression 
       auto v=t1 + std::polar(2.,PI/2.) * t1 + (1.+2.i)*t1 + FTerm{50,3};
       std::cout<<FType(10,10)+v(FInterpolator(0.05,callback))<<endl;
       return 0;
}
