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
    Figur kube2("./figurer/kube.obj", Punkt{800, 100, 400});

    std::vector<Figur*> alleFigurer = {&kube, &kube2}; //&kube2
    
    while(!window.should_close()) {

        window.draw_rectangle({0, 0}, WINDOW_WIDTH, WINDOW_HEIGHT, TDT4102::Color::dark_gray);
        window.draw_circle({100, 100}, 50, TDT4102::Color::alice_blue);

        tegnFigur(&window, cam, alleFigurer); 

        kube.sentrum.y -= 2;

        kube2.sentrum.x += 2;
        Punkt camPos = cam.getPos();
        camPos.z += 2;

        if (camPos.z > WINDOW_HEIGHT){
            camPos.z = 0; 
        }

        cam.endrePos(camPos);


        if (kube2.sentrum.x > WINDOW_WIDTH){
            kube2.sentrum.x = 0;
        }

        window.next_frame();
    }

    return 0;
}