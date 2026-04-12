#include "utils.h"
#include <random>
#include <cmath>
#include "figurer.h"
#include "konstanter.h"
#include <chrono>
#include <iostream>
#include "scener.h"
#include "ui.h"

TDT4102::Point gammelMusPos{-1, 0};

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

void sjekkKeyPressed(Kamera& cam, AnimationWindow& window, long long dt, std::vector<Fly>& alleFly){

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

    bool venstreMus = false; //window.is_left_mouse_button_down();

    if (venstreMus){
        TDT4102::Point musPos = window.get_mouse_coordinates();

        if (musPos.x != gammelMusPos.x && musPos.y != gammelMusPos.y ){

            float x_ndc = 2 * musPos.x / WINDOW_WIDTH - 1; 
            float z_ndc = 1 - 2 * musPos.y / WINDOW_HEIGHT;
        
            Punkt stråleRetning{x_ndc * A_RATIO[0] / A_RATIO[1] * tan(KAMERA_1_FOV), - 1, z_ndc * tan(KAMERA_1_FOV)};

            stråleRetning = stråleRetning / pow(stråleRetning * stråleRetning, 0.5);

            Punkt camPos = cam.getPos();

            Punkt strålePunkt = camPos;

            Punkt frem = cam.getRetning();
            Punkt verdenOpp = {0, 0, 1};                   
            Punkt hoyre  = (frem ^ verdenOpp);
            hoyre = hoyre / sqrt(hoyre * hoyre);

            Punkt oppover = (hoyre ^ frem);
            oppover = oppover / sqrt(oppover * oppover);

            Punkt stråleRetningVerden{
                    hoyre * stråleRetning.x +
                    frem * stråleRetning.y +
                    oppover * stråleRetning.z};

            stråleRetningVerden = stråleRetningVerden / pow(stråleRetningVerden * stråleRetningVerden, 0.5f);

            std::cout << "frem:     " << frem.x << " " << frem.y << " " << frem.z << std::endl;
            std::cout << "hoyre:    " << hoyre.x << " " << hoyre.y << " " << hoyre.z << std::endl;
            std::cout << "oppover:  " << oppover.x << " " << oppover.y << " " << oppover.z << std::endl;
            std::cout << "stråle:   " << stråleRetningVerden.x << " " << stråleRetningVerden.y << " " << stråleRetningVerden.z << std::endl;
            std::cout << "camPos:   " << camPos.x << " " << camPos.y << " " << camPos.z << std::endl;

            // og for første trekant
            std::cout << "punkter[0]: " << alleFly[0].getPunkter()[0].x << " " << alleFly[0].getPunkter()[0].y << " " << alleFly[0].getPunkter()[0].z << std::endl;
            std::cout << "punkter[1]: " << alleFly[0].getPunkter()[1].x << " " << alleFly[0].getPunkter()[1].y << " " << alleFly[0].getPunkter()[1].z << std::endl;
            std::cout << "punkter[2]: " << alleFly[0].getPunkter()[2].x << " " << alleFly[0].getPunkter()[2].y << " " << alleFly[0].getPunkter()[2].z << std::endl;

            for (Fly& f : alleFly){
                std::vector<Punkt> punkter = f.getPunkter();

                // Möller–Trumbore - algoritmen for å se om en stråle treffer en trekant.

                Punkt A = punkter[1] - punkter[0];
                Punkt B = punkter[2] - punkter[0];
                Punkt h = stråleRetningVerden ^ B;
                float det = A * h;

                float EPSILON = 0.01;

                if (std::abs(det) < EPSILON){
                    continue;
                }

                float invers_det = 1.0 / det;
                Punkt s = camPos - punkter[0] + f.getSentrum();
                float u = (s * h) * invers_det;

                if (u < 0.0 || u > 1.0){
                    continue;
                }

                Punkt q = s ^ A;
                float v = (stråleRetningVerden * q) * invers_det;

                if (v < 0.0 || u + v > 1.0){
                    continue;
                }

                float t = (B * q) * invers_det;

                if (t < EPSILON){
                    continue;
                }
                
                f.printFlyData();
            }

            std::cout << "{ " << musPos.x << ", " << musPos.y << " }" << std::endl;
            gammelMusPos = musPos;
        }
    }

    if (cam.getKanEndres()){
        Punkt frem = cam.getRetning();
        Punkt hoyre = frem ^ Punkt{0, 0, 1};

        Punkt camPos = cam.getPos();

        if(wKeyIsPressed)       camPos = camPos + frem  * skrittLengde * dt;
        if(sKeyIsPressed)       camPos = camPos - frem  * skrittLengde * dt;
        if(dKeyIsPressed)       camPos = camPos + hoyre * skrittLengde * dt;
        if(aKeyIsPressed)       camPos = camPos - hoyre * skrittLengde * dt;
        if(spaceKeyIsPressed)   camPos.z += skrittLengde * dt;
        if(lShiftKeyIsPressed)  camPos.z -= skrittLengde * dt;

        cam.endrePos(camPos);

        if (leftKeyIsPressed)  cam.roterYaw(rotasjonsFart * dt);
        if (rightKeyIsPressed) cam.roterYaw(-rotasjonsFart * dt);
        if (upKeyIsPressed)    cam.roterPitch(rotasjonsFart * dt);
        if (downKeyIsPressed)  cam.roterPitch(-rotasjonsFart * dt);
    }
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

void himmelLegemeInit(CelestialKropp& Tellus, CelestialKropp& Solen, int kvalitet){

    Tellus.dobleTrekanter(kvalitet);
    if (kvalitet < 4){
        Solen.dobleTrekanter(kvalitet);
    }
    else{
        Solen.dobleTrekanter(kvalitet - 1);
    }
    Tellus.Spherifiser(JORD_RADIUS);
    Solen.Spherifiser(SOL_RADIUS);
 
    Tellus.mapBildeTilKule(jordKart);
    Solen.mapBildeTilKule(solKart);
 
    Tellus.setSpin(degToRad(JORD_ROT_HAST), {0, 0, 1});
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
