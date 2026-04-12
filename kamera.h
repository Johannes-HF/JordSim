#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "figurer.h"



class Kamera{
    private:
        std::array<double, 2> fov; // [vertikal, horisontal] - [theta, alfa]
        std::array<double, 2> aspectRatio;
        Punkt pos;
        Punkt retning{0, 1, 0};
        bool kanEndres;

    public:
        Kamera(const double kamFov, const double kamAspectRatio[2], Punkt kamPos, bool inKanEndres);

        const Punkt& getPos() const;
        void endrePos(Punkt& p);
        const array<double, 2>& getFov() const;
        const array<double, 2>& getAspect() const;
        const Punkt& getRetning() const;
        const bool getKanEndres() const;


        friend std::ostream& operator<<(std::ostream& os, const Kamera& cam);
    
        std::vector<float> projiser(std::vector<Figur*> figurer);
        void roterYaw(double theta);
        void roterPitch(double theta);

};

void tegnFigur(TDT4102::AnimationWindow* window, Kamera& cam, std::vector<Figur*> figurer);


