# FourierSeries
A generic algorithm for Fourier Synthesis and Analysis.

![bat](https://github.com/abhilashraju/FourierSeries/blob/master/demo/bat.gif) ![horse](https://github.com/abhilashraju/FourierSeries/blob/master/demo/horse.gif)
![bat](https://github.com/abhilashraju/FourierSeries/blob/master/demo/dude.gif) ![bat](https://github.com/abhilashraju/FourierSeries/blob/master/demo/hand.gif)


This is just a hobby project to demonstate an application of 
1) std::accumulate algorithm in the evaluation of fourier series (Fourier Synthesis)
2) std::inner_prodcut for the fourier transform (Fourier Analysis)

It is just an easy to use header only library.The library has dependency over C++14.
To run the cosole version do the following
```
  cd path_to_repo/tests/justmain
  g++  main.cpp -std=c++14 -lstdc++
  ./a.out
```

You can try the Graphical example if you are willing to depend on QT. Or you can use base libray with any other Graphical toolkit of your choice to draw your own animaitons.

Using Qt Version.
```
  Install Qt from https://www.qt.io/download?hsCtaTracking=f24f249b-61fb-4dec-9869-50512342f8d9%7Cf3adf380-4740-4f7e-9e49-d06fa99445fa
  open qtcreator 
  import FourierTest.pro from path_to_rep/tests/qtexample/FourierTest.
  qmake
  build 
  run
 ``` 
 Example
 ```
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
```

