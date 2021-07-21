# FourierSeries
A generic algorithm for Fourier series evaluation and drawing the approximation.
It is a header only library ,which contains algorithm that evaluates fourier series from set of frequecy terms given as input.
Two set of examples usage you can find in test folder. One just prints the forier values in std::out. Other one is graphical example ,which requires Qt to be availble in you enviroment. You can use it as a reference in case if you want to draw fourier series using other graphical tool kits.

Using consle version.
  The library is writtern using C++14 features. So you need a c++ compiler with C++14 support. 
  compilation step
  cd path_to_repo/tests/justmain
  g++  main.cpp -std=c++14 -lstdc++
  ./a.out
Using Qt Version.
  Install Qt from https://www.qt.io/download?hsCtaTracking=f24f249b-61fb-4dec-9869-50512342f8d9%7Cf3adf380-4740-4f7e-9e49-d06fa99445fa
  open qtcreator 
  import FourierTest.pro from path_to_rep/tests/qtexample/FourierTest.
  qmake
  build 
  run
  
![bat](https://github.com/abhilashraju/FourierSeries/blob/master/demo/bat.gif) ![horse](https://github.com/abhilashraju/FourierSeries/blob/master/demo/horse.gif)
![bat](https://github.com/abhilashraju/FourierSeries/blob/master/demo/dude.gif)
