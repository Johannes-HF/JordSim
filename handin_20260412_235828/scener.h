#pragma once
#include "AnimationWindow.h"
#include "std_lib_facilities.h"
#include "konstanter.h"
#include "figurer.h"
#include "kamera.h"
#include "widgets/Button.h"
#include "widgets/CheckBox.h"
#include "widgets/Slider.h"
#include "utils.h"

class Scene{
    private:
    AnimationWindow* window;
    std::vector<Figur*> figurer;
    Kamera cam;

    public:
    Scene(Kamera inCam, std::vector<Figur*>& inFigurer, AnimationWindow& inWindow)
        : cam(inCam), figurer(inFigurer), window(&inWindow) {};
};

Scene lagHovedMeny(std::vector<Figur*>& alleFigurer);