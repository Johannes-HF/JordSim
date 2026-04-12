#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "tegnFigurer.h"
#include "figurer.h"
#include "kamera.h"
#include "konstanter.h"
#include "utils.h"
#include "lesBilder.h"
#include "fly.h"
#include "ui.h"
#include <chrono>

int main(){

    TDT4102::AnimationWindow window(WINDOW_POSITION_X, WINDOW_POSITION_Y, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    // Hovedmenyen
    bool startFlag = false;


    TDT4102::CheckBox jordCheck{{100, 100}, 200, 50, ""};
    TDT4102::CheckBox solCheck {{100, 150}, 200, 50, ""};
    TDT4102::CheckBox flyCheck {{100, 200}, 200, 50, ""};
    TDT4102::Slider kvalitet {{100, 400}, 200, 30, 2, 8, 4, 1};
    TDT4102::Button startKnapp({100, 500}, 200, 50, "Start Simulasjon");



    TDT4102::TextBox tbox({100, 350}, 200, 30, "Oppløsning:");

    tbox.setTextColor(TDT4102::Color::white);

    window.add(tbox);


    lagHovedmenyUI(window, jordCheck, solCheck, flyCheck, kvalitet, startKnapp, startFlag);  

    TDT4102::Image kartAvJorda("bilder/verden2k.jpg");

    while (!window.should_close() && !startFlag) {
        window.draw_image({0, 0}, kartAvJorda, WINDOW_WIDTH, WINDOW_HEIGHT);
        window.draw_rectangle({0, 0}, 400, WINDOW_HEIGHT, TDT4102::Color{40, 40, 40}, TDT4102::Color::black);

        std::string txtBoksTxt = std::format("Oppløsning: {}/8", kvalitet.getValue());
        tbox.setText(txtBoksTxt);

        window.next_frame();
    }

    bool tegnJord = jordCheck.isSelected();
    bool tegnSol  = solCheck.isSelected();
    bool tegnFly  = flyCheck.isSelected();
    int  kvalitetVerdi = kvalitet.getValue();

    window.deleteWidgets();

    
    std::vector<Fly> alleFly;
    if (tegnFly){
        try {
            lesFlydata("flydata/flyData.txt", alleFly);
            std::cout << "Antall flyvende fly: " << alleFly.size() << std::endl;
        } 
        catch (const std::exception& e) {
            std::cerr << "Feil under innlesing av flydata: " << e.what() << std::endl;
            return 1;
        }
    }

    
    Punkt camPos{WINDOW_WIDTH / 2.0, -30000, WINDOW_HEIGHT / 2.0};
    Kamera cam{KAMERA_1_FOV, A_RATIO, camPos, true};

     
    CelestialKropp Tellus{ORIGO, JORD_RADIUS};
    CelestialKropp Solen{{0, 150 * pow(10, 4), 0}, SOL_RADIUS};

    if (tegnJord || tegnSol){
        try {
            himmelLegemeInit(Tellus, Solen, kvalitetVerdi);
        } 
        catch (const std::exception& e) {
            std::cerr << "Feil under init av himmellegemer: " << e.what() << std::endl;
            return 1;
    }   
    }

    std::vector<Figur*> alleFigurer;
    if (tegnFly)
        for (Fly& f : alleFly)
            alleFigurer.push_back(&f);
    if (tegnJord) alleFigurer.push_back(&Tellus);
    if (tegnSol)  alleFigurer.push_back(&Solen);

    
    std::vector<TDT4102::Point> stjerner;
    for (int i = 0; i < 100; i++)
        stjerner.push_back({randomInt(0, WINDOW_WIDTH), randomInt(0, WINDOW_HEIGHT)});

    // Program

    TDT4102::CheckBox debugCheck{{10, 10}, 200, 30, "DebugMeny"};
    debugCheck.setLabelColor(TDT4102::Color::white);
    window.add(debugCheck);

    TDT4102::Slider simulasjonHastighet {{WINDOW_WIDTH / 2 - 100, 20}, 200, 30, 1, 1000, 1, 1};
    window.add(simulasjonHastighet);

    auto start = std::chrono::high_resolution_clock::now();

    while (!window.should_close()) {

        window.draw_rectangle({0, 0}, WINDOW_WIDTH, WINDOW_HEIGHT, TDT4102::Color::black);

        for (const TDT4102::Point& s : stjerner){
            window.draw_circle(s, 2, TDT4102::Color::white);
        }

        int antallTrekanter = tegn3DFigur(&window, cam, alleFigurer);

        auto end = std::chrono::high_resolution_clock::now();
        long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        start = std::chrono::high_resolution_clock::now();

        int flyHast = simulasjonHastighet.getValue(); 

        for (Figur* fig : alleFigurer){
            if (auto* fly = dynamic_cast<Fly*>(fig)){
                
                fly->flyFremmover(ms, flyHast);

            }
        }

        sjekkKeyPressed(cam, window, ms, alleFly);

        if (debugCheck.isSelected()){
            debugInfo(cam, window, getFPS(ms), antallTrekanter);
        }
        window.next_frame();
    }

    return 0;
}