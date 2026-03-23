#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "figurer.h"
#include "kamera.h"
#include "konstanter.h"
#include "utils.h"

int main(){

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
    kule.Spherifiser(100);
    kule.setSpin(degToRad(-1), enhetsVektor[1]);

    std::vector<TDT4102::Point> stjerner;

    for (int i= 0; i < 100; i++){
        stjerner.push_back(
            TDT4102::Point{randomInt(0, WINDOW_WIDTH), randomInt(0, WINDOW_HEIGHT)}
        );
    }

    while(!window.should_close()) {

        window.draw_rectangle({0, 0}, WINDOW_WIDTH, WINDOW_HEIGHT, TDT4102::Color::black);

        for (TDT4102::Point p : stjerner){
            window.draw_circle(p, 2, TDT4102::Color::white);
        }

        window.draw_circle({100, 100}, 50, TDT4102::Color::light_yellow);

        sjekkKeyPressed(cam, window);
        
        tegnFigur(&window, cam, alleFigurer); 

        kube.sentrum.y -= 2;


        if (kube2.sentrum.x > WINDOW_WIDTH){
            kube2.sentrum.x = 0;
        }

        window.next_frame();
    }

    return 0;
}