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

int main(){


    std::vector<TDT4102::Color> Jordfarger = lesBilde(jordKart);

    TDT4102::AnimationWindow window(WINDOW_POSITION_X, WINDOW_POSITION_Y, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE );

    Punkt p{WINDOW_WIDTH / 2, 0, WINDOW_HEIGHT / 2};
    std::cout << p;

    Kamera cam{KAMERA_1_FOV, A_RATIO, p};

    std::cout << cam;

    Figur kube("./figurer/kube.obj", Punkt{WINDOW_WIDTH / 2, 5000, WINDOW_HEIGHT / 2});
    Figur kube2("./figurer/kube.obj", Punkt{800, 500, 400});
    Kule kule("./figurer/kube.obj", Punkt{500, 500, 700});


    std::vector<Figur*> alleFigurer = {&kube, &kube2, &kule}; //&kube2

    kube2.setSpin(degToRad(1), enhetsVektor[2]);

    kube2.dobleTrekanter(3);
    kube.dobleTrekanter(1);

    kule.dobleTrekanter(3);
    //kule.Spherifiser(100);
    //kule.setSpin(degToRad(-1), enhetsVektor[1]);

    std::vector<TDT4102::Point> stjerner;

    for (int i= 0; i < 100; i++){
        stjerner.push_back(
            TDT4102::Point{randomInt(0, WINDOW_WIDTH), randomInt(0, WINDOW_HEIGHT)}
        );
    }

    int rotasjon = 0;
    bool baklengs = 0;
    while(!window.should_close()) {

        window.draw_rectangle({0, 0}, WINDOW_WIDTH, WINDOW_HEIGHT, TDT4102::Color::black);

        int stjerneIndex = 0;
        for (TDT4102::Point p : stjerner){
            window.draw_circle(p, 2, TDT4102::Color::white);
            stjerneIndex ++;
        }

        for (int i = 0; i < 320*5; i+=8){
            for (int k = 0; k < 160*8; k+=8){
                window.draw_circle({i, k}, 8, Jordfarger.at(k/8 * 320 + i/8));
            }
        }


        window.draw_circle({100, 100}, 50, TDT4102::Color::light_yellow);

        sjekkKeyPressed(cam, window);
        
        tegn3DFigur(&window, cam, alleFigurer); 

        kule.brettUt(800, 450);
        tegn2DFigur(&window, cam, kule.getUVKoordinater());

        kube.sentrum.y -= 2;




        if (kube2.sentrum.x > WINDOW_WIDTH){
            kube2.sentrum.x = 0;
        }


        // cam.roterKamera({static_cast<float>(pow(-1, baklengs)), 0, 0});

        // if (rotasjon < 60){ 
        //     if (baklengs == 0){rotasjon += 1;}
        //     else{ rotasjon -= 1;}
        // }   
        // else{baklengs = 1;}
        // if (rotasjon < 0){
        //     baklengs = 0;
        // }

        window.next_frame();

    }
    
    return 0;
}