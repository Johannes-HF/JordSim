#include "scener.h"
#include "variabler.h"

template<typename F>

void lagKnapp(F kallFunk, Point pos, int bredde, int hoyde, string tekst){

    TDT4102::Button knapp {pos, bredde, hoyde, tekst};
    knapp.setCallback(kallFunk);

    window.add(knapp);
}

//HovedMeny - HM
float HM_cam_FOV = 30.0;
double FOCAL = (WINDOW_HEIGHT / 2) / std::tan(degToRad(HM_cam_FOV));
const double rotasjonsFart = degToRad(0.02);
Punkt HM_pos{0, -12000, 0};

AnimationWindow HM_window(WINDOW_POSITION_X, WINDOW_POSITION_Y, WINDOW_WIDTH, WINDOW_HEIGHT, "Hovedmeny");



Kamera hovedMenyCam{HM_cam_FOV, A_RATIO, HM_pos, false};

Scene hovedMeny(hovedMenyCam, alleFigurer, HM_window);

