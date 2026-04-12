#include "scener.h"

Scene lagHovedMeny(std::vector<Figur*>& alleFigurer){
    Punkt HM_pos{0, -12000, 0};
    Kamera hovedMenyCam{KAMERA_1_FOV, A_RATIO, HM_pos, false};
    AnimationWindow HM_window(WINDOW_POSITION_X, WINDOW_POSITION_Y, WINDOW_WIDTH, WINDOW_HEIGHT, "Hovedmeny");
    return Scene(hovedMenyCam, alleFigurer, HM_window);
}