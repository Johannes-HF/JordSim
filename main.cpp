#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "tegnFigurer.h"
#include "figurer.h"
#include "kamera.h"
#include "konstanter.h"
#include "utils.h"
#include "lesBilder.h"
#include <cmath>
#include <chrono>
#include "fly.h"

int main(){

    long long ms = 0;

    std::string flydataFil = "flydata/flyData.txt";
    std::vector<Fly> alleFly = {};
    lesFlydata(flydataFil, alleFly);

    std::cout << "Antall flyvende fly: " << alleFly.size() << std::endl;

    int jordW;
    int jordH;
    std::vector<TDT4102::Color>* Jordfarger = lesBilde(jordKart, jordW, jordH);

    TDT4102::AnimationWindow window(WINDOW_POSITION_X, WINDOW_POSITION_Y, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE );

    Punkt p{WINDOW_WIDTH / 2, -12000, WINDOW_HEIGHT / 2};
    std::cout << p;

    Kamera cam{KAMERA_1_FOV, A_RATIO, p};

    std::cout << cam;

    CelestialKropp Tellus{ORIGO, JORD_RADIUS};
    CelestialKropp Solen{{150 * pow(10, 4), 0, 0}, SOL_RADIUS};

    himmelLegemeInit(Tellus, Solen);

    std::vector<Figur*> alleFigurer{};// {&Tellus, &Solen} //&kube, &kube2,

    for (Fly& f : alleFly){
        alleFigurer.push_back(&f);
    }

    alleFigurer.push_back(&Tellus);
    alleFigurer.push_back(&Solen);

    std::vector<TDT4102::Point> stjerner;

    for (int i= 0; i < 100; i++){
        stjerner.push_back(
            TDT4102::Point{randomInt(0, WINDOW_WIDTH), randomInt(0, WINDOW_HEIGHT)}
        );
    }

    auto start = std::chrono::high_resolution_clock::now();

    while(!window.should_close()) {

        window.draw_rectangle({0, 0}, WINDOW_WIDTH, WINDOW_HEIGHT, TDT4102::Color::black);

        int stjerneIndex = 0;
        for (TDT4102::Point p : stjerner){
            window.draw_circle(p, 2, TDT4102::Color::white);
            stjerneIndex ++;
        }

        window.draw_circle({100, 100}, 50, TDT4102::Color::light_yellow);

        int antallTrekanter = tegn3DFigur(&window, cam, alleFigurer);

        for (int i = 0; i < alleFigurer.size(); i++){
            Figur* fig = alleFigurer.at(i);

            if (dynamic_cast<Fly*>(fig)) {
                dynamic_cast<Fly*>(fig)->flyFremmover(ms);
            }
        }

        auto end = std::chrono::high_resolution_clock::now();
        ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        sjekkKeyPressed(cam, window, ms, alleFly);

        if (debug){
            int FPS = getFPS(ms);

            debugInfo(cam, window, FPS, antallTrekanter);
        }

        start = std::chrono::high_resolution_clock::now();

        window.next_frame();

    }
    
    delete Jordfarger;
    return 0;
}