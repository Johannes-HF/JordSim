#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "figurer.h"
#include "kamera.h"
#include "utils.h"
#include "konstanter.h"
#include <cmath>

std::ostream& operator<<(std::ostream& os, const Kamera& cam){
    os << "Vinkel/fov: [" << cam.fov[0] << ", " << cam.fov[1] << "]"
    << "\nSideforhold: " << cam.aspectRatio[0] << " / " << cam.aspectRatio[1]
    << "\nPosisjon: " << cam.pos;

    return os;
}


Kamera::Kamera(const double kamFov, const double kamAspectRatio[2], Punkt kamPos) : 
    pos(kamPos), 
    aspectRatio{kamAspectRatio[0], kamAspectRatio[1]}
    
    {
        fov[0] = degToRad(kamFov);

        double alfa = std::asin(static_cast<double>(kamAspectRatio[1]) / static_cast<double>(kamAspectRatio[0]) * std::cos(fov[0]));
        
        fov[1] = alfa;
}

const Punkt& Kamera::getPos() const {return pos;}
void Kamera::endrePos(Punkt& p){
    pos = p;
}

const array<double, 2>& Kamera::getFov() const {return fov;}
const array<double, 2>& Kamera::getAspect() const {return aspectRatio;};
const Punkt& Kamera::getRetning() const {return retning;};

void Kamera::roterYaw(double theta){
    double x = retning.x;
    double y = retning.y;
    retning.x = x * cos(theta) - y * sin(theta);
    retning.y = x * sin(theta) + y * cos(theta);
};

void Kamera::roterPitch(double theta){
    Punkt opp{0, 0, 1};
    Punkt hoyre = retning ^ opp;

    double len = sqrt(hoyre * hoyre);
    if (len < 1e-6) return;
    hoyre = hoyre / len;

    // Rodrigues: v' = v*cos(θ) + (k × v)*sin(θ) + k*(k·v)*(1-cos(θ))
    Punkt kryssprodukt = hoyre ^ retning;
    float kdotv = hoyre * retning;

    retning.x = retning.x * cos(theta) + kryssprodukt.x * sin(theta) + hoyre.x * kdotv * (1 - cos(theta));
    retning.y = retning.y * cos(theta) + kryssprodukt.y * sin(theta) + hoyre.y * kdotv * (1 - cos(theta));
    retning.z = retning.z * cos(theta) + kryssprodukt.z * sin(theta) + hoyre.z * kdotv * (1 - cos(theta));

    retning = retning / sqrt(retning * retning);
};



std::vector<float> Kamera::projiser(std::vector<Figur*> figurer){

    std::vector<float> toDplan;

    const std::array<double, 2> aspArr = getAspect();

    double aRatio = aspArr[0] / aspArr[1];

    for (int i = 0; i < figurer.size(); i++){

        Figur* fig = figurer.at(i);
        std::vector<Punkt> punkter = fig->getPunkter();
        std::vector<int> indexer = fig->getIndexer();
        Punkt sentrum = fig->getSentrum();
        const std::vector<TDT4102::Color>& farger = fig->getFarger();

        if (fig->getSpin() != 0){
            fig->roterFigur();
        }

        //sorterEtterDybde();

        int antallFarger = fig->getFarger().size();

        for (int j = 0; j < indexer.size(); j += 3){

            const Punkt& A =  punkter.at(indexer.at(j));
            const Punkt& B =  punkter.at(indexer.at(j+1));
            const Punkt& C =  punkter.at(indexer.at(j+2));

            const Punkt relA = A + sentrum - this->pos;
            const Punkt relB = B + sentrum - this->pos;
            const Punkt relC = C + sentrum - this->pos;

            Punkt fremover = this->retning;

            Punkt hoyre = fremover ^ Punkt{0, 0, 1};
            Punkt opp = hoyre ^ fremover;

            std::array<float, 3> dybde = {relA * fremover,
                                        relB * fremover,
                                        relC * fremover};
            std::array<float, 3> hoyreK = {relA * hoyre, relB * hoyre, relC * hoyre};

            std::array<float, 3> oppK = {relA * opp, relB * opp, relC * opp};

            
            if (dybde[0] <= NEAR || dybde[1] <= NEAR || dybde[2] <= NEAR ||
                dybde[0] >= FAR  || dybde[1] >= FAR  || dybde[2] >= FAR) {
                continue;
}

            //Sjekker om trekanten vender vekk fra kamera

            const Punkt u = B - A;
            const Punkt v = C - A;

            Punkt NormalVektor = u ^ v;

            if (NormalVektor * this->retning >= 0){
                continue;
            }

            const Punkt* hjorner[3] = {&relA, &relB, &relC};

            for (int k = 0; k < 3; k++){

                const Punkt* p = hjorner[k];

                if (dybde[k] <= 0){ continue;}

                float xp = (hoyreK[k]) * FOCAL / (dybde[k]) * aRatio + WINDOW_WIDTH / 2;// std::cos(Kamera::fov[1])) / (p->y); 
                float zp = -(oppK[k]) * FOCAL / (dybde[k]) * aRatio + WINDOW_HEIGHT / 2; //std::cos(fov[0])) / (p->y);

                toDplan.push_back(xp);
                toDplan.push_back(zp);
                toDplan.push_back(p->y - this->pos.y);
                
            }
            TDT4102::Color c = farger.at(j / 3);
            toDplan.push_back(c.redChannel);
            toDplan.push_back(c.greenChannel);
            toDplan.push_back(c.blueChannel);
        }
    }

    return toDplan;

};
