#include "utils.h"
#include <random>
#include <cmath>
#include "figurer.h"
#include "konstanter.h"
#include <chrono>

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
    bool rKeyIsPressed = window.is_key_down(KeyboardKey::R);
    bool leftKeyIsPressed = window.is_key_down(KeyboardKey::LEFT);
    bool rightKeyIsPressed = window.is_key_down(KeyboardKey::RIGHT);
    bool upKeyIsPressed = window.is_key_down(KeyboardKey::UP);
    bool downKeyIsPressed = window.is_key_down(KeyboardKey::DOWN);

    Punkt frem = cam.getRetning();
    Punkt hoyre = frem ^ Punkt{0, 0, 1};

    Punkt camPos = cam.getPos();

    if(wKeyIsPressed)       camPos = camPos + frem  * skrittLengde;
    if(sKeyIsPressed)       camPos = camPos - frem  * skrittLengde;
    if(dKeyIsPressed)       camPos = camPos + hoyre * skrittLengde;
    if(aKeyIsPressed)       camPos = camPos - hoyre * skrittLengde;
    if(spaceKeyIsPressed)   camPos.z += skrittLengde;
    if(lShiftKeyIsPressed)  camPos.z -= skrittLengde;

    cam.endrePos(camPos);

    if (leftKeyIsPressed)  cam.roterYaw(rotasjonsFart);
    if (rightKeyIsPressed) cam.roterYaw(-rotasjonsFart);
    if (upKeyIsPressed)    cam.roterPitch(rotasjonsFart);
    if (downKeyIsPressed)  cam.roterPitch(-rotasjonsFart);
}

int getFPS(long long løkkeTidMS){
    if (løkkeTidMS == 0) {return 0;};
    return static_cast<int>(1000 / løkkeTidMS);
};

void debugInfo(const Kamera& cam, AnimationWindow& window, int FPS, int antallTrekanter){

    Punkt camPos = cam.getPos();

    std::string koords = std::format("x: {:.0f} | y: {:.0f} | z: {:.0f}", camPos.x, camPos.y, camPos.z);
    std::string fpsString = std::format("FPS: {}", FPS);
    std::string antallTrekanerString = std::format("Trekanter: {}", antallTrekanter);


    int debugBredde = koords.size() * 12 + 20;
    int fpsBredde = (fpsString.size() + antallTrekanerString.size()) * 13 + 60; 
    if ( fpsBredde > debugBredde){
        debugBredde = fpsBredde;
    };

    window.draw_rectangle({0, WINDOW_HEIGHT - 90}, debugBredde, 80, TDT4102::Color{40, 40, 40});
    window.draw_text({20, WINDOW_HEIGHT - 80}, koords, TDT4102::Color::white, 30);
    window.draw_text({20, WINDOW_HEIGHT - 50}, fpsString, TDT4102::Color::white, 30);
    window.draw_text({static_cast<int>(fpsString.size() * 15 + 20), WINDOW_HEIGHT - 50}, antallTrekanerString, TDT4102::Color::white, 30);

};

