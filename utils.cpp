#include "utils.h"
#include <random>
#include <cmath>
#include "figurer.h"

int randomInt(int low, int high){
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(low, high);

    return distribution(generator);
}

double degToRad(double deg){
    return deg * M_PI / 180.0;
}

bool sorterIndexPar(IndexPar& a, IndexPar& b){
    return a.total_Y_verdi > b.total_Y_verdi;
}

float stringAspectRatioToFloat(std::string aspectRatio){

    float breddeRatio;
    float hoydeRatio;
   
    bool telNevn = 0;

    for (char i : aspectRatio){
        if (!telNevn){
            breddeRatio *= 10;
            breddeRatio += i;
        }
        else{
            hoydeRatio *= 10;
            hoydeRatio += i;
        }
        if (i == '/'){
            telNevn = 1;
        }
    }

    const float aRatio = breddeRatio / hoydeRatio;

    return aRatio;
};


void printTrekantKoordinater(std::vector<float>& toDplan, int figurer){
    std::cout << "Figur trekant:\n" ;

    std::cout << "Antall trekanter pr fig:\n" << toDplan.size() / 2.0 / 3.0 / figurer << std::endl;

    for (int j = 1; j < 3; j++){
    for (int i = 0; i < toDplan.size() / 2; i+=6){
        std::cout << i / 6 + 1 << ".  ";
        for (int k = 0; k < 6; k+=2){
            cout << toDplan.at(i*j+k) << ", " << toDplan.at(j*i+k+1) << ",    ";
        }
        std::cout << endl;
            
        };
    }
    std::cout << std::endl;
};

void tegnKontur (AnimationWindow* window, TDT4102::Point p1, TDT4102::Point p2, TDT4102::Point p3){
    window->draw_line(p1, p2, TDT4102::Color::white);
    window->draw_line(p1, p3, TDT4102::Color::white);
    window->draw_line(p2, p3, TDT4102::Color::white);

}

void sjekkKeyPressed(Kamera& cam, AnimationWindow& window){

    bool dKeyIsPressed = window.is_key_down(KeyboardKey::D);
    bool aKeyIsPressed = window.is_key_down(KeyboardKey::A);
    bool wKeyIsPressed = window.is_key_down(KeyboardKey::W);
    bool sKeyIsPressed = window.is_key_down(KeyboardKey::S);
    bool spaceKeyIsPressed = window.is_key_down(KeyboardKey::SPACE);
    bool lShiftKeyIsPressed = window.is_key_down(KeyboardKey::LEFT_SHIFT);

    int skrittLengde = 5;
    
    if(dKeyIsPressed) {
        Punkt camPos = cam.getPos();
        camPos.x += skrittLengde;
        cam.endrePos(camPos);
    };
    if(aKeyIsPressed) {
        Punkt camPos = cam.getPos();
        camPos.x -= skrittLengde;
        cam.endrePos(camPos);
    };
    if(wKeyIsPressed) {
        Punkt camPos = cam.getPos();
        camPos.y += skrittLengde;
        cam.endrePos(camPos);
    };
    if(sKeyIsPressed) {
        Punkt camPos = cam.getPos();
        camPos.y -= skrittLengde;
        cam.endrePos(camPos);
    };
    if(lShiftKeyIsPressed && spaceKeyIsPressed) {
        Punkt camPos = cam.getPos();
        camPos.z -= skrittLengde;
        cam.endrePos(camPos);
    }
    else if (spaceKeyIsPressed){
        Punkt camPos = cam.getPos();
        camPos.z += skrittLengde;
        cam.endrePos(camPos);
    };
}

