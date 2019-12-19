
#include <QApplication>
#include <QWidget>
#include <deque>
#include "fourier.h"
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <numeric>
#include "fourierdraw.h"
using namespace FourierLiterals;

#include <nlohmann/json.hpp>
using json = nlohmann::json;
auto j2 = R"(
          [
          {"x": -1.8286974392723174, "y": 59.814181827227635},
          {"x": -4.976831584697713, "y": 65.82425182918777},
          {"x": -8.411179967263092, "y": 74.98246433045111},
          {"x": -13.84879666517007, "y": 84.25214580558782},
          {"x": -20.71724567369283, "y": 93.01267813317173},
          {"x": -28.444614388815825, "y": 98.73653579675755},
          {"x": -42.4680080469807, "y": 103.60174657163898},
          {"x": -53.629477619921275, "y": 108.7531719634135},
          {"x": -64.21851719956933, "y": 108.75318601289717},
          {"x": -75.09403562861394, "y": 108.75320044247952},
          {"x": -80.24545342601694, "y": 103.31557828048132},
          {"x": -69.37019983106828, "y": 100.00022225777394},
          {"x": -65.36339085588487, "y": 108.75318753190969},
          {"x": -63.073897902866904, "y": 113.33241868417467},
          {"x": -69.083957272776, "y": 118.19761882700504},
          {"x": -74.23537355116648, "y": 113.90487032132236},
          {"x": -69.65640511273793, "y": 109.89806688417666},
          {"x": -67.08042837422384, "y": 118.19761616873312},
          {"x": -75.6661873395738, "y": 127.35583550486174},
          {"x": -73.66293748251496, "y": 113.33243273365835},
          {"x": -74.52158171294744, "y": 121.6319865752524},
          {"x": -77.09727561278247, "y": 130.21776110909855},
          {"x": -77.33766728350267, "y": 122.7768639679379},
          {"x": -77.95594306620737, "y": 121.01423855851849},
          {"x": -80.24543595875508, "y": 116.48058358683932},
          {"x": -86.82792266368476, "y": 128.50072397051272},
          {"x": -98.67251217635707, "y": 135.08298190372665},
          {"x": -103.99944439191601, "y": 143.95497850198112},
          {"x": -103.99942730440729, "y": 156.83376539426024},
          {"x": -103.99940110386005, "y": 176.58101291847964},
          {"x": -102.56828852852428, "y": 192.03550320338545},
          {"x": -110.00943585650566, "y": 200.00014596013412},
          {"x": -115.14652249682045, "y": 200.00015277599445},
          {"x": -120.0260522134553, "y": 189.7457790536221},
          {"x": -127.75318289662214, "y": 178.58431289811415},
          {"x": -135.48057021792079, "y": 170.28477044842296},
          {"x": -146.92827529210348, "y": 162.55766976298915},
          {"x": -153.79673934147635, "y": 159.98197358463534},
          {"x": -155.22782685517873, "y": 163.41633601702995},
          {"x": -154.0829414278983, "y": 172.28806359319222},
          {"x": -154.08292547964896, "y": 184.30819524323468},
          {"x": -154.082912189326, "y": 194.32505843004265},
          {"x": -156.65860995096358, "y": 200.00020785402023},
          {"x": -156.65864292210486, "y": 175.14999071609603},
          {"x": -164.67225359358204, "y": 163.13013013376778},
          {"x": -174.97507324048425, "y": 164.2747570244962},
          {"x": -178.40943833080524, "y": 160.84040104755928},
          {"x": -180.98515881094056, "y": 149.39270964310722},
          {"x": -186.42280375570786, "y": 137.37284564300074},
          {"x": -190.42960643369287, "y": 133.36605359741233},
          {"x": -190.4296151673238, "y": 126.78355094423331},
          {"x": -182.41628999210653, "y": 119.91507968024204},
          {"x": -181.5576476604397, "y": 110.18443376825358},
          {"x": -183.27470720273254, "y": 103.02949656509006},
          {"x": -181.55767234231996, "y": 91.5817994650321},
          {"x": -179.26820217241658, "y": 78.98948838447},
          {"x": -174.6889824120545, "y": 68.11396387972083},
          {"x": -164.95861174437357, "y": 57.811129803927365},
          {"x": -150.93496296708938, "y": 48.93912166691369},
          {"x": -136.33913248076672, "y": 44.073910132526},
          {"x": -122.31573388650222, "y": 42.92901787003478},
          {"x": -132.6188116902033, "y": 45.79095524558205},
          {"x": -148.3592736239464, "y": 36.91898659943857},
          {"x": -156.94504967645958, "y": 33.19867947860569},
          {"x": -144.0665270166838, "y": 30.33673868597132},
          {"x": -129.18447545835593, "y": 27.474795235065045},
          {"x": -119.74004492311242, "y": 30.62266438848077},
          {"x": -110.86805311410119, "y": 32.33996310164363},
          {"x": -122.88817982769852, "y": 36.06055799760078},
          {"x": -131.18774392159048, "y": 27.47479789299142},
          {"x": -134.3358951545246, "y": 20.60608100267243},
          {"x": -121.17115673859637, "y": 15.7408713670504},
          {"x": -113.15781447656146, "y": 21.75066612470297},
          {"x": -101.70984934646879, "y": 29.19180883103001},
          {"x": -103.14092357019376, "y": 42.64277401491491},
          {"x": -108.86478465086667, "y": 32.33996044371726},
          {"x": -96.12925465054764, "y": 19.174938239899863},
          {"x": -92.26567430975216, "y": 36.060517367816736},
          {"x": -91.40700084109295, "y": 49.797697927755486},
          {"x": -87.68644467649973, "y": 32.626150758483234},
          {"x": -87.40020917525767, "y": 45.504676835691605},
          {"x": -82.821217953369, "y": 58.669676066690606},
          {"x": -82.82122668699992, "y": 52.08717341351161},
          {"x": -64.50479295118788, "y": 65.53811239650373},
          {"x": -42.46806576427347, "y": 60.10045416141351},
          {"x": -51.05384219653976, "y": 56.09392862650173},
          {"x": -61.07069361203728, "y": 64.9659314473171},
          {"x": -74.2354248133471, "y": 75.26877007980264},
          {"x": -83.10740242463616, "y": 84.25223769755249},
          {"x": -74.80784569325554, "y": 87.28890248935139},
          {"x": -59.353341738273684, "y": 96.16087151490244},
          {"x": -42.75422722056584, "y": 103.02931012323434},
          {"x": -30.161657223353075, "y": 104.17416707179427},
          {"x": -18.141531111348293, "y": 100.00015428783772},
          {"x": -10.700644061461908, "y": 92.15400960095766},
          {"x": -9.842005147227724, "y": 79.84765839757694},
          {"x": -17.283181648819077, "y": 65.82426815719023},
          {"x": -25.010306636034485, "y": 58.95581777754788},
          {"x": -23.29325772613823, "y": 58.097160257138},
          {"x": -5.549284361104807, "y": 53.80412093865154},
          {"x": -27.586013826192445, "y": 57.52472912458611},
          {"x": -40.46480641407745, "y": 53.23199087154688},
          {"x": -27.299798829546194, "y": 54.94902345344068},
          {"x": -35.599351152127724, "y": 55.23525287932373},
          {"x": -44.47133232874235, "y": 61.53154888973429},
          {"x": -54.48818830093189, "y": 66.96919117692072},
          {"x": -60.7844634269935, "y": 73.83766016273877},
          {"x": -68.51156980803322, "y": 80.99260989637345},
          {"x": -55.63277859092224, "y": 84.2522012443618},
          {"x": -70.80105236051479, "y": 84.25222136955003},
          {"x": -58.208478714009196, "y": 88.14753570763412},
          {"x": -67.93912158831814, "y": 89.57838025328073},
          {"x": -52.48462522770782, "y": 92.72650186788943},
          {"x": -36.17173292091909, "y": 96.73327758582091},
          {"x": -47.6194258443837, "y": 98.16412440964076},
          {"x": -64.21852669236098, "y": 101.59850696687805},
          {"x": -84.82443363575591, "y": 98.45039218713461},
          {"x": -98.67257961830167, "y": 84.25225834935016},
          {"x": -107.14767688441822, "y": 75.8412505757695},
          {"x": -119.45377638611228, "y": 68.40010900801073},
          {"x": -131.18769038123662, "y": 67.82794818366682},
          {"x": -136.6253034301963, "y": 79.84782661301007},
          {"x": -141.2045254690772, "y": 89.00604063328592},
          {"x": -146.06970305063237, "y": 100.0003240222834},
          {"x": -144.35263569212862, "y": 113.04630811030978},
          {"x": -136.05307083873038, "y": 122.20450504307692},
          {"x": -122.60184104293447, "y": 126.78346095068875},
          {"x": -110.29549059905999, "y": 127.06966303676519},
          {"x": -98.67252508658135, "y": 125.35259756631518},
          {"x": -92.55178222569069, "y": 119.34252362031299},
          {"x": -91.40691958117932, "y": 111.0429693989658},
          {"x": -94.8413002399965, "y": 95.8747001860653},
          {"x": -98.67257961830167, "y": 84.25225834935016},
          {"x": -97.41702945376278, "y": 77.84450612843419},
          {"x": -100.851372899883, "y": 90.72329757740535},
          {"x": -107.71982593745173, "y": 96.44715410138622},
          {"x": -116.30560085105103, "y": 93.58524178747236},
          {"x": -122.31566857483791, "y": 92.15415769120258},
          {"x": -127.46733693501379, "y": 94.15743298964796},
          {"x": -132.33252340776806, "y": 98.45045522062567},
          {"x": -136.33904783590162, "y": 107.8704059752711},
          {"x": -139.48717891116632, "y": 116.19444377440217},
          {"x": -132.04627879314197, "y": 118.19770236509193},
          {"x": -119.73992721000809, "y": 119.342559693405},
          {"x": -110.86793729976252, "y": 119.62876633617344},
          {"x": -104.57165571893432, "y": 117.62522908374348},
          {"x": -101.70974112650165, "y": 110.75676465461744},
          {"x": -99.99270095023633, "y": 103.31560448102856},
          {"x": -110.00957135166266, "y": 97.87798877448806},
          {"x": -109.1509187673524, "y": 95.87471917199413},
          {"x": -109.15091041347459, "y": 102.17100341109423},
          {"x": -115.14664473413565, "y": 107.8703778572988},
          {"x": -121.74346332317866, "y": 113.90493335481342},
          {"x": -128.32570554104, "y": 113.9049420880988},
          {"x": -122.31564958890908, "y": 106.4637762185585},
          {"x": -115.14665913123683, "y": 97.01934034811174},
          {"x": -112.29906088690245, "y": 95.87472334893303},
          {"x": -115.14665761222432, "y": 98.16421400442727},
          {"x": -118.88155252827731, "y": 104.1742847848986},
          {"x": -119.73994695544319, "y": 104.46050433789131},
          {"x": -115.14665517613734, "y": 100.00028299374128},
          {"x": -112.01284019465032, "y": 97.59177301833554},
          {"x": -110.86796084238338, "y": 101.88478727518861},
          {"x": -101.42380972804075, "y": 90.72329833691161},
          {"x": -100.2789326542926, "y": 93.29900210929138},
          {"x": -108.00606827390462, "y": 78.41695700607562},
          {"x": -136.62531558091433, "y": 70.6898791037564},
          {"x": -152.65224079555776, "y": 73.5518240736752},
          {"x": -160.95179653591742, "y": 71.26208777284832},
          {"x": -166.96187337274284, "y": 62.96254304463834},
          {"x": -177.26470365135057, "y": 56.094096082428614},
          {"x": -179.8403922353328, "y": 68.68640754274386},
          {"x": -180.9852522215722, "y": 78.98949066264323},
          {"x": -179.26818318648776, "y": 93.29910691182589},
          {"x": -173.25809989455018, "y": 106.46384380874159},
          {"x": -168.67885924914808, "y": 111.32929033706041},
          {"x": -169.5375129727177, "y": 112.47390469731766},
          {"x": -170.3961803660179, "y": 103.31569789200576},
          {"x": -172.11324446465727, "y": 92.72666059053093},
          {"x": -176.40626973366003, "y": 85.5717268051456},
          {"x": -177.26467175519744, "y": 80.13409894719597},
          {"x": -174.11652417155614, "y": 84.25235844799077},
          {"x": -173.25812305741792, "y": 89.00608316183562},
          {"x": -176.40625058981746, "y": 100.00036427265985},
          {"x": -178.9819518621846, "y": 103.02949086948418},
          {"x": -177.83709225535276, "y": 92.44044977082358},
          {"x": -166.67562344191845, "y": 86.71658755089128},
          {"x": -162.38257652906046, "y": 110.18440832686706},
          {"x": -159.52066633575163, "y": 100.00034186895283},
          {"x": -159.80690996903212, "y": 80.99273102656487},
          {"x": -170.682444346326, "y": 68.97261380610472},
          {"x": -164.3861863077731, "y": 49.225357928007554},
          {"x": -164.95864477978608, "y": 32.91247169692338},
          {"x": -174.9752623406119, "y": 21.750748143777322},
          {"x": -182.98861979138985, "y": 4.293258564240034},
          {"x": -190.42978034507743, "y": 2.2897395385781856},
          {"x": -193.29169076022566, "y": 12.306606522571899},
          {"x": -195.2949428958033, "y": 24.612698809302003},
          {"x": -191.00216932848718, "y": 38.35013524821189},
          {"x": -180.41285678305033, "y": 47.79428712171523},
          {"x": -174.11656456982553, "y": 53.804344592858676},
          {"x": -173.83060659106428, "y": 53.80434421345109},
          {"x": -169.537602206756, "y": 45.218567401086126},
          {"x": -167.53435045093153, "y": 32.62625670027713},
          {"x": -173.54443184444898, "y": 20.8923514384382},
          {"x": -181.27155493324426, "y": 15.454732693872629},
          {"x": -188.42623891570858, "y": 11.734163238956452},
          {"x": -195.29495276834805, "y": 17.17180134920399},
          {"x": -187.85401619713298, "y": 46.649683773607656},
          {"x": -193.5778434828871, "y": 61.81796513757173},
          {"x": -183.5609810555854, "y": 61.245515019091},
          {"x": -183.5609628291628, "y": 74.98269671828916},
          {"x": -171.2545592246876, "y": 115.33583068096209},
          {"x": -164.3860940360553, "y": 118.77018210155252},
          {"x": -170.39615454487824, "y": 122.77698743746389},
          {"x": -179.84031515235807, "y": 126.7835368944041},
          {"x": -187.28147494619384, "y": 125.35271513221765},
          {"x": -182.13007119862004, "y": 120.20103727925016},
          {"x": -158.3760297300466, "y": 117.62530047111234},
          {"x": -150.3626855689005, "y": 125.06644773447695},
          {"x": -140.91825275513818, "y": 129.93162737236597},
          {"x": -132.33247898079824, "y": 131.93488444404318},
          {"x": -136.33900717363642, "y": 138.51739241307493},
          {"x": -138.91497328009945, "y": 138.23117741677422},
          {"x": -140.05957662820708, "y": 145.67233683085692},
          {"x": -149.503994633325, "y": 151.9683731654561},
          {"x": -163.52738601297108, "y": 158.5508944248108},
          {"x": -172.3993706070183, "y": 162.27148514382904},
          {"x": -178.12322181514648, "y": 159.40956903272937},
          {"x": -179.55433552939607, "y": 143.0966839409046},
          {"x": -172.11319016479712, "y": 133.6522477093641},
          {"x": -160.951706922126, "y": 138.8036434831587},
          {"x": -152.93837301362336, "y": 138.51741443702883},
          {"x": -144.06638424263718, "y": 137.9449658375606},
          {"x": -150.64889145216273, "y": 134.51087447288026},
          {"x": -156.9449050036473, "y": 142.23799870058943},
          {"x": -164.09983043550037, "y": 152.8270477733747},
          {"x": -172.39937934064923, "y": 155.68898249065003},
          {"x": -175.54752867481773, "y": 150.25135767072544},
          {"x": -169.8236941744452, "y": 140.52070530362482},
          {"x": -162.09656614920476, "y": 149.67890299589826},
          {"x": -158.66220789374904, "y": 147.96184839005053},
          {"x": -150.64887170707317, "y": 149.39266939307632}



         ]
)"_json;

struct Widget:public QWidget{

    QTimer timer;
    std::deque<FType> targetWavex;
    std::deque<FType> targetWavey;
    FReal time{0.};
    std::vector<FTerm> ftofx;
    std::vector<FTerm> ftofy;
    Widget(){
      std::vector<FReal> xvals;
        std::vector<FReal> yvals;
         for(auto& v: j2){
             xvals.emplace_back(v["x"]);
             yvals.emplace_back(v["y"]);
         }
         ftofx= D_F_T(xvals);
         std::sort(begin(ftofx),end(ftofx),[](auto v1, auto v2){
             return v1.amp > v2.amp;
         });

         ftofy= D_F_T(yvals,PI/2.);
         std::sort(begin(ftofy),end(ftofy),[](auto v1, auto v2){
             return v1.amp > v2.amp;
         });


         timer.connect(&timer,&QTimer::timeout,[=](){
            time+=  Tou/ftofy.size();
            time = (time >Tou)?0.:time;
            if(!time){targetWavex.clear(),targetWavey.clear();}
            update();

        });
        timer.setSingleShot(false);
        timer.setInterval(30ms);
        timer.start();

    }
    void paintEvent(QPaintEvent* )
    {
        QPainter p(this);
        p.fillRect(rect(),Qt::black);
        QPen pen(Qt::red);
        pen.setWidth(3);
        p.setPen(pen);
        QPointF middle(width()/2,height()/2);

        auto epiCircleDraw =make_epiCircleDraw<QPainter,QPointF>(p);
        auto handleDraw=make_handleDraw<QPainter,QPointF>(p);
        auto drawWave=make_drawWave<QPainter,QPointF,QPainterPath>(p);
        auto drawTrace=make_drawTrace<QPainter,QPointF,QPainterPath>(p);
        pen.setWidth(5);
        pen.setColor(Qt::white);
        p.setPen(pen);

        auto values1 = make_Values(time,middle+QPointF(200,-200),ftofx,epiCircleDraw)(targetWavex);
        auto values2 = make_Values(time,middle+QPointF(-300,100) ,ftofy,epiCircleDraw)(targetWavey);
        std::vector<FType> dest;
        combine(values1,values2,std::back_inserter(dest),[](auto val1, auto val2){
            return FType{val1.real(), val2.imag()};
         });
        p.drawLine(QPointF(values1.front().real(),values1.front().imag()),QPointF(dest.front().real(),dest.front().imag()));
        p.drawLine(QPointF(values2.front().real(),values2.front().imag()),QPointF(dest.front().real(),dest.front().imag()));
        pen.setColor(Qt::red);
        p.setPen(pen);
        drawTrace(dest);
    }

};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(1500,800);
    w.show();

    return a.exec();
}
