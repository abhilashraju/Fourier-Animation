#include "fourierwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FourierWidget w;
    FTerm t1{50,1.};
    std::vector<FTerm> terms;
    terms.push_back(t1);
    terms.emplace_back(std::polar(2.,PI/2.) * t1);
    terms.emplace_back((1.+2.i)*t1);
    terms.emplace_back(FTerm{50,3});
    w.addFourierTerm(terms);
    w.show();

    return a.exec();
}
