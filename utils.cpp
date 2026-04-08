#include "utils.h"
#include <random>
#include <cmath>
#include "figurer.h"
#include "konstanter.h"
#include <chrono>
#include <iostream>

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

void himmelLegemeInit(CelestialKropp& Tellus, CelestialKropp& Solen){

    Tellus.dobleTrekanter(6);
    Solen.dobleTrekanter(5);

    Tellus.Spherifiser(JORD_RADIUS);
    Solen.Spherifiser(SOL_RADIUS);

    Tellus.mapBildeTilKule(jordKart);
    Solen.mapBildeTilKule(solKart);

    //Tellus.setSpin(degToRad(1), {0, 0, 1});
    Solen.setSpin(degToRad(0.2), {0, 0, 1});
};

void lesFlydata(std::string flyFil, std::vector<Fly>& alleFly){

    try {
        ifstream fil(flyFil);
        if (!fil.is_open()) {
            throw std::runtime_error("Kunne ikke åpne filen: " + flyFil);
        }

        std::string linje;
        std::vector<std::string> filStreng;
        
        while (std::getline(fil, linje)){

            std::string stripLinje = "";
            bool forsteChar = false;
            for (char b : linje){
                if (b != ' '){
                    forsteChar = true;
                }
                if ( forsteChar && b != '\t' && b != ',' && b != '"'){
                    stripLinje += b;
                };
            }

            filStreng.push_back(stripLinje);
            //std::cout << stripLinje << std::endl;
        }
        int i = 3;
        int antallFly = 0;
        while (i < filStreng.size()){
            
            if (filStreng.at(i) == "[" and filStreng.at(i+9) == "false"){
                antallFly++;
                int feilOffset = 0;

                //std::cout << "FlyNr: " << antallFly << std::endl;
                try {


                    feilOffset = 1; std::string icao24 = filStreng.at(i+1);
                    feilOffset = 2; std::string kalleNavn = filStreng.at(i+2);
                    feilOffset = 3; std::string landOpprinnelse = filStreng.at(i+3);
                    feilOffset = 4; int posisjon_tid = (filStreng.at(i+4) == "null") ? 0 : std::stoi(filStreng.at(i+4));
                    feilOffset = 5; int nullTid = (filStreng.at(i+5) == "null") ? 0 : std::stoi(filStreng.at(i+5));
                    feilOffset = 6; float lengdeGrad = (filStreng.at(i+6) == "null") ? 0 : std::stof(filStreng.at(i+6));
                    feilOffset = 7; float breddeGrad = (filStreng.at(i+7) == "null") ? 0 : std::stof(filStreng.at(i+7));
                    feilOffset = 8; float baroHoyde = (filStreng.at(i+8) == "null") ? 0 : std::stof(filStreng.at(i+8));
                    feilOffset = 9; bool onGround = (filStreng.at(i+9) == "false") ? 0 : 1;
                    feilOffset = 10; float fart = (filStreng.at(i+10) == "null") ? 0 : std::stof(filStreng.at(i+10));
                    feilOffset = 11; float retning = (filStreng.at(i+11) == "null") ? 0 : std::stof(filStreng.at(i+11));
                    feilOffset = 12; float vertikalFart = (filStreng.at(i+12) == "null") ? 0 : std::stof(filStreng.at(i+12));

                    

                    Fly fly{
                        icao24,
                        kalleNavn,
                        landOpprinnelse,
                        posisjon_tid,
                        nullTid,
                        lengdeGrad,
                        breddeGrad,
                        baroHoyde,
                        onGround,
                        fart,
                        retning,
                        vertikalFart
                        };

                    alleFly.push_back(fly);
                } catch (const std::exception& e){
                    std::cerr << "FEIL i innlesing av flyNr " << antallFly << ", i linje " << feilOffset << ":\n" << e.what() << ", " << filStreng.at(i+feilOffset) << std::endl;
                } 
                i += 13;
            }  
            i ++;
        } 

    } catch (const std::exception& e) {
        std::cerr << "FEIL i lesFlydata: " << e.what() << std::endl;
    }
    
}
