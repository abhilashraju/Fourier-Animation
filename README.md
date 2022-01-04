# FourierSeries
A generic algorithm for Fourier series evaluation and drawing the approximation.This is just a hobby project to demonstate an application of 
1) std::accumulate algorithm in the evaluation of fourier series (Fourier Synthesis)
2) std::inner_prodcut for the fourier transform (Fourier Analysis)

It is just an easy to use header only library.The library has dependency over C++14.
To run the cosole version do the following
```
  cd path_to_repo/tests/justmain
  g++  main.cpp -std=c++14 -lstdc++
  ./a.out
```

You can try the Graphical example if are willing to depend on QT. Or you can use base libray with any other Graphical toolkit of your choice to draw your own animaitons.
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
 
![bat](https://github.com/abhilashraju/FourierSeries/blob/master/demo/bat.gif) ![horse](https://github.com/abhilashraju/FourierSeries/blob/master/demo/horse.gif)
![bat](https://github.com/abhilashraju/FourierSeries/blob/master/demo/dude.gif) ![bat](https://github.com/abhilashraju/FourierSeries/blob/master/demo/hand.gif)
