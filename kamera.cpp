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

void Kamera::roterKamera(Punkt omega){
    Punkt nyRetning = omega + this->retning;
    this->retning =  nyRetning / sqrt(nyRetning * nyRetning);
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

            const Punkt absA = A + sentrum;
            const Punkt absB = B + sentrum;
            const Punkt absC = C + sentrum;

            double dA = absA.y - this->pos.y;
            double dB = absB.y - this->pos.y;
            double dC = absC.y - this->pos.y;

            if (dA <= NEAR || dB <= NEAR || dC <= NEAR ||
                dA >= FAR  || dB >= FAR  || dC >= FAR) {
                continue;
}

            //Sjekker om trekanten vender vekk fra kamera

            const Punkt u = B - A;
            const Punkt v = C - A;

            Punkt NormalVektor = u ^ v;

            Punkt viewDir = absA - this->pos; // Vector from camera to absolute vertex
            
            if (NormalVektor.x * viewDir.x + NormalVektor.y * viewDir.y + NormalVektor.z * viewDir.z >= 0){
                continue;
            }

            const Punkt* hjorner[3] = {&absA, &absB, &absC};

            for (int k = 0; k < 3; k++){

                const Punkt* p = hjorner[k];

                float xp = (p->x - this->pos.x) * FOCAL / (p->y - this->pos.y) * aRatio + WINDOW_WIDTH / 2;// std::cos(Kamera::fov[1])) / (p->y); 
                float zp = -(p->z - this->pos.z) * FOCAL / (p->y - this->pos.y) * aRatio + WINDOW_HEIGHT / 2; //std::cos(fov[0])) / (p->y);

                if (p->y - this->pos.y <= 0){ continue;}
               
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
