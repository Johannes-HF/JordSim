#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "figurer.h"



class Kamera{
    private:
        std::array<double, 2> fov; // [vertikal, horisontal] - [theta, alfa]
        std::array<double, 2> aspectRatio;
        Punkt pos;

    public:
        Kamera(const double kamFov, const double kamAspectRatio[2], Punkt kamPos);

        Punkt getPos() const;
        void endrePos(Punkt& p);
        array<double, 2> getFov() const;
        array<double, 2> getAspect() const;

        friend std::ostream& operator<<(std::ostream& os, const Kamera& cam);
    
        std::vector<float> projiser(std::vector<Figur*> figurer);

};

void tegnFigur(TDT4102::AnimationWindow* window, Kamera& cam, std::vector<Figur*> figurer);


