#include "fly.h"
#include "figurer.h"
#include "konstanter.h"
#include "AnimationWindow.h"
#include <cmath>

void Fly::finnKartesisk(){

    double phi = degToRad(breddeGrad);
    double lambda = degToRad(lengdeGrad);
    this->retning = degToRad(this->retning);

    float x = JORD_RADIUS * cos( phi ) * cos( lambda );
    float y = JORD_RADIUS * cos( phi ) * sin( lambda );
    float z = JORD_RADIUS * sin( phi );

    Punkt nordVektor{ -sin(phi) * cos(lambda), -sin(phi) * sin(lambda) , cos(phi)};
    Punkt ostVektor{-sin(lambda) / cos(phi), cos(lambda) / cos(phi), 0};

    this->retningVektor = nordVektor * cos(this->retning) + ostVektor * sin(this->retning);

    this->sentrum = {x, y, z};
    this->sentrum = this->sentrum / pow(this->sentrum * this->sentrum, 0.5) * (JORD_RADIUS + this->baroHoyde / 100);

    std::cout << this->sentrum << std::endl;

    Punkt normalTilFly = sentrum ^ retningVektor;
    normalTilFly = normalTilFly / pow(normalTilFly * normalTilFly, 0.5);

    Punkt foran = retningVektor* FLY_SIZE;
    Punkt bak1 = ORIGO - (retningVektor + normalTilFly) * (FLY_SIZE / 2);
    Punkt bak2 = ORIGO - (retningVektor - normalTilFly) * (FLY_SIZE / 2);

    this->punkter = {foran, bak2, bak1};
    this->indexer = {0, 1, 2};
    this->farger = {TDT4102::Color::white, TDT4102::Color::white, TDT4102::Color::white};
}

void Fly::flyFremmover(){
    Punkt nySentrum = this->sentrum + this->retningVektor * this->fart;
    this->sentrum = nySentrum / (pow(nySentrum * nySentrum, 0.5)) * (JORD_RADIUS + this->baroHoyde / 100);
}

void Fly::printFlyData() const{
    std::cout << 
            "flyHex: " << icao24 << std::endl <<
            "Callsign: " << kalleNavn << std::endl <<
            "Opprinnelsesland: " << landOpprinnelse << std::endl <<
            "Posisjonstid: " << posisjon_tid << std::endl <<
            "NullTid: " << nullTid << std::endl <<
            "Lon: " << lengdeGrad << std::endl <<
            "Lat: " << breddeGrad << std::endl <<
            "MoH: " << baroHoyde << std::endl <<
            "Landet: " << onGround << std::endl <<
            "Hastighet: " << fart << std::endl <<
            "Retning: " << retning << std::endl <<
            "VertikalFart: " << vertikalFart << std::endl;
    std::cout << "__________________________________\n" << std::endl;
};