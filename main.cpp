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

int main(){

    int jordW;
    int jordH;
    std::vector<TDT4102::Color>* Jordfarger = lesBilde(jordKart, jordW, jordH);

    TDT4102::AnimationWindow window(WINDOW_POSITION_X, WINDOW_POSITION_Y, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE );

    Punkt p{WINDOW_WIDTH / 2, 0, WINDOW_HEIGHT / 2};
    std::cout << p;

    Kamera cam{KAMERA_1_FOV, A_RATIO, p};

    std::cout << cam;

    Figur kube("./figurer/kube.obj", Punkt{WINDOW_WIDTH / 2, 5000, WINDOW_HEIGHT / 2});
    Figur kube2("./figurer/kube.obj", Punkt{800, 500, 400});
    Kule kule("./figurer/kube.obj", Punkt{500, 500, 700});


    std::vector<Figur*> alleFigurer = {&kule, &kube}; //&kube, &kube2,

    kube2.setSpin(degToRad(1), enhetsVektor[2]);

    kube2.dobleTrekanter(3);
    kube.dobleTrekanter(1);

    kule.dobleTrekanter(6);
    kule.Spherifiser(500);

    kule.setSpin(degToRad(1), enhetsVektor[2]);

    kule.mapBildeTilKule(jordKart);

    kule.brettUt(800, 450);


    std::vector<TDT4102::Point> stjerner;

    for (int i= 0; i < 100; i++){
        stjerner.push_back(
            TDT4102::Point{randomInt(0, WINDOW_WIDTH), randomInt(0, WINDOW_HEIGHT)}
        );
    }

    int rotasjon = 0;
    bool baklengs = 0;

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

        sjekkKeyPressed(cam, window);

        if (tegnKart){
            antallTrekanter += tegn2DFigur(&window, cam, kule.getUVKoordinater());
        }

        auto end = std::chrono::high_resolution_clock::now();
        long long ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

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