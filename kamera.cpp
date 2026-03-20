#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "figurer.h"
#include "kamera.h"
#include "utils.h"
#include "konstanter.h"

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

Punkt Kamera::getPos() const {return pos;}
void Kamera::endrePos(Punkt& p){
    pos = p;
}

array<double, 2> Kamera::getFov() const {return fov;}
array<double, 2> Kamera::getAspect() const {return aspectRatio;};


std::vector<float> Kamera::projiser(std::vector<Figur*> figurer){

    std::vector<float> toDplan;

    std::array<double, 2> aspArr = getAspect();

    double aRatio = aspArr[0] / aspArr[1];

;

    for (int i = 0; i < figurer.size(); i++){

        Figur* fig = figurer.at(i);

        fig->sorterEtterDybde();

        for (int j = 0; j < fig->getIndexer().size(); j += 3){

            const Punkt& A =  fig->getPunkter().at(fig->getIndexer().at(j));
            const Punkt& B =  fig->getPunkter().at(fig->getIndexer().at(j+1));
            const Punkt& C =  fig->getPunkter().at(fig->getIndexer().at(j+2));

            Punkt absA = A + fig->getSentrum();
            Punkt absB = B + fig->getSentrum();
            Punkt absC = C + fig->getSentrum();

            //Sjekker om trekanten er for nærme eller langt unna
            if (absA.y >= FAR || absB.y >= FAR ||absC.y >= FAR || absA.y <= NEAR ||absB.y <= NEAR ||absC.y <= NEAR){
                continue;
            }

            //Sjekker om trekanten vender vekk fra kamera

            const Punkt u = B - A;
            const Punkt v = C - A;

            Punkt NormalVektor = {
                u.y*v.z - u.z*v.y,
                u.z*v.x - u.x*v.z,
                u.x*v.y - u.y*v.x
            };

            Punkt viewDir = absA - this->pos; // Vector from camera to absolute vertex
            if (NormalVektor.x * viewDir.x + NormalVektor.y * viewDir.y + NormalVektor.z * viewDir.z >= 0){
                continue;
            }
/*
            if (NormalVektor.x * A.x + NormalVektor.y * A.y + NormalVektor.z * A.z <= 0){
                continue;
            }
        */
            //Sjekker om z koordinaten er over der man ser
            double hyp = std::tan(fov[0]);            
     
            hyp = std::tan(fov[1]);
            
            //Sjekker om x koordinaten er lenger til siden enn der man ser

            std::vector<Punkt*> hjorner{&absA, &absB, &absC};

            for (int k = 0; k < 3; k++){

                Punkt* p = hjorner.at(k);

                float xp = (p->x - this->pos.x) * FOCAL / (p->y - this->pos.y) + WINDOW_WIDTH / 2;// std::cos(Kamera::fov[1])) / (p->y); 
                float zp = -(p->z - this->pos.z) * FOCAL / (p->y - this->pos.y) + WINDOW_HEIGHT / 2; //std::cos(fov[0])) / (p->y);
           
                std::cout << "xp: " << xp << "\nzp: " << zp << "\n";
                
                // if (k == 0){
                //     if (xp < 0 || xp > WINDOW_WIDTH || zp < 0 || zp > WINDOW_HEIGHT){
                //         break;
                //     }
                // }

                toDplan.push_back(xp);
                toDplan.push_back(zp);   
            }
        }
 
    }

    return toDplan;

};

void tegnFigur(TDT4102::AnimationWindow* window, Kamera& cam, std::vector<Figur*> figurer){

    std::cout << "Figur trekant:\n" ;

    std::vector<float> toDplan = cam.projiser(figurer);

    std::vector<TDT4102::Color> farger {TDT4102::Color::green, TDT4102::Color::hot_pink, TDT4102::Color::royal_blue, TDT4102::Color::dark_orange};
    int fargeI = 0;
    for (int i = 0; i < toDplan.size(); i+=6){

        if (fargeI > 11){ fargeI = 0;}

        std::vector<TDT4102::Point> punkter = {};

        for (int j = 0; j < 6; j+=2){

            TDT4102::Point p {toDplan.at(i+j), toDplan.at(i+j+1)};
            punkter.push_back(p);
            std::cout << toDplan.at(i+j) << ", " <<  toDplan.at(i+j+1) << std::endl;
        }

        window->draw_triangle(
            punkter.at(0), 
            punkter.at(1),  
            punkter.at(2), 
            figurer[0]->getFarger().at(fargeI/2)
        );
        std::cout << "Tegnet trekant" << std::endl;
        
        fargeI ++;

        std::cout << "\n";
    }

    std::cout << "\n\n\n"; 

};