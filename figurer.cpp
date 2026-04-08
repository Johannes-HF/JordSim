#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "figurer.h"
#include "konstanter.h"
#include "lesBilder.h"
#include <fstream>
#include <cmath>
#include <algorithm>


std::ostream& operator<<(std::ostream& os, const Punkt& p){
    os << "{" << p.x << ", " << p.y << ", " << p.z << "}" << endl;
    return os;
}
Punkt operator+(const Punkt& LHS, const Punkt& RHS){
    Punkt sum;
    sum.x = LHS.x + RHS.x;
    sum.y = LHS.y + RHS.y;
    sum.z = LHS.z + RHS.z;
    return sum;
}

Punkt operator-(const Punkt& LHS, const Punkt& RHS){
    Punkt sub;
    sub.x = LHS.x - RHS.x;
    sub.y = LHS.y - RHS.y;
    sub.z = LHS.z - RHS.z;
    return sub;
}

float operator*(const Punkt& LHS, const Punkt& RHS){
  
    return LHS.x * RHS.x + LHS.y * RHS.y + LHS.z * RHS.z;
}

Punkt operator*(const Punkt& LHS, const float t){
    return Punkt {LHS.x * t, LHS.y * t, LHS.z * t};
}
Punkt operator/(const Punkt& LHS, const float t){
    return Punkt {LHS.x / t, LHS.y / t, LHS.z / t};
}

Punkt operator^(const Punkt& LHS, const Punkt& RHS){

    return Punkt {
        LHS.y * RHS.z - LHS.z * RHS.y,
        LHS.z * RHS.x - LHS.x * RHS.z,
        LHS.x * RHS.y - LHS.y * RHS.x};
}

Figur::Figur(std::string filnavn, Punkt inSentrum){
    sentrum = inSentrum;
    sentrum.y += FOCAL;
    omega = 0;


    ifstream fil(filnavn);
    std::string linje;

    while(std::getline(fil, linje)){
        std::istringstream iss(linje);
        
        char identifier = '\0';

        iss >> identifier; 

        if (identifier == 'v'){
            float x, y, z;
            iss >> x >> y >> z;

            punkter.push_back(Punkt(x, y, z));
        }
        else if(identifier == 'f'){
            int x, y, z;
            iss >> x >> y >> z;
            indexer.push_back(x-1);
            indexer.push_back(y-1);
            indexer.push_back(z-1);

        }
        else if (identifier == 'c'){
            int r, g, b;
            iss >> r >> g >> b;
            farger.push_back(TDT4102::Color(r, g, b));
        }
    }
}

const std::vector<Punkt>& Figur::getPunkter() const { return punkter;};
const std::vector<int>& Figur::getIndexer() const { return indexer;};
const std::vector<TDT4102::Color>& Figur::getFarger() const { return farger;};
const Punkt& Figur::getSentrum() const { return sentrum;};
double Figur::getSpin() const { return omega;};

void Figur::setSpin(double alfa, Punkt nyRotAkse){
    omega = alfa;
    rotAkse = nyRotAkse;
};


void Figur::endreSentrum(Punkt& nyttSentrum){
    sentrum = nyttSentrum;
}

void Figur::roterFigur(){
    for (int i = 0; i < this->punkter.size(); i++){
        Punkt& p = punkter.at(i);

        //Rodriges rotasjonsformel
        p = p * cos(this->omega) + (this->rotAkse ^ p) * sin(omega) + rotAkse * (rotAkse * p) * (1 - cos(omega));
    }
}

void Figur::dobleTrekanter(int antallDupliseringer){

    for (int i = 0; i < antallDupliseringer; i++){

        int antallGamleIndexer = this->indexer.size();
        
        for (int j = 0; j < antallGamleIndexer; j+=3){
    
        int idxA = this->indexer.at(j);
        int idxB = this->indexer.at(j + 1);
        int idxC = this->indexer.at(j + 2);

        Punkt X = this->punkter.at(idxA) + (this->punkter.at(idxB) - this->punkter.at(idxA)) / 2;
        Punkt Y = this->punkter.at(idxB) + (this->punkter.at(idxC) - this->punkter.at(idxB)) / 2;
        Punkt Z = this->punkter.at(idxA) + (this->punkter.at(idxC) - this->punkter.at(idxA)) / 2;

        int idxX = this->punkter.size(); this->punkter.push_back(X);
        int idxY = this->punkter.size(); this->punkter.push_back(Y);
        int idxZ = this->punkter.size(); this->punkter.push_back(Z);

      
        this->indexer.at(j)     = idxA;
        this->indexer.at(j + 1) = idxX;
        this->indexer.at(j + 2) = idxZ;

        this->indexer.push_back(idxX); this->indexer.push_back(idxB); this->indexer.push_back(idxY);
        this->indexer.push_back(idxZ); this->indexer.push_back(idxY); this->indexer.push_back(idxC);
        this->indexer.push_back(idxX); this->indexer.push_back(idxY); this->indexer.push_back(idxZ);

        TDT4102::Color morFarge = this->farger.at(j / 3);
        this->farger.at(j / 3) = morFarge;
        this->farger.push_back(morFarge);
        this->farger.push_back(morFarge);
        this->farger.push_back(morFarge);

        }
    }

};

void Figur::sorterEtterDybde(){

    std::vector<IndexPar> alleIndexPar;

    for (int i = 0; i < indexer.size(); i+=3){
        
        int i1 = indexer.at(i);
        int i2 = indexer.at(i+1);
        int i3 = indexer.at(i+2);

        alleIndexPar.push_back( {IndexPar{{i1, i2, i3}, punkter.at(i1).y + punkter.at(i2).y + punkter.at(i3).y } } );
    }

    std::sort(alleIndexPar.begin(), alleIndexPar.end(), sorterIndexPar);

    for (int i = 0; i < indexer.size(); i+=3){
        indexer[i] = alleIndexPar.at(i/3).hjorne.at(0);
        indexer[i+1] = alleIndexPar.at(i/3).hjorne.at(1);
        indexer[i+2] = alleIndexPar.at(i/3).hjorne.at(2);
    }
}

std::vector<float> sorter2Dplan(const std::vector<float>& toDplan){

    std::vector<IndexPar> alleIndexPar;
    std::vector<float> nyToDplan;
    nyToDplan.resize(toDplan.size() / 12 * 9);

    for (int i = 2; i < toDplan.size(); i+=12){
        // y-verdiene til trekanten
        int i1 = i; 
        int i2 = i+3;
        int i3 = i+6;

        alleIndexPar.push_back( {IndexPar{{i1, i2, i3}, toDplan.at(i1) + toDplan.at(i2) + toDplan.at(i3) } } );
    }

    std::sort(alleIndexPar.begin(), alleIndexPar.end(), sorterIndexPar);

    int nyIndex = 0;

    for (int i = 0; i < alleIndexPar.size(); i++){

        nyToDplan[nyIndex] = toDplan.at(alleIndexPar.at(i).hjorne[0]-2); // Trekker fra 2 for å få x-verdien
        nyToDplan[nyIndex+1] = toDplan.at(alleIndexPar.at(i).hjorne[0]-1);

        nyToDplan[nyIndex+2] = toDplan.at(alleIndexPar.at(i).hjorne[1]-2);
        nyToDplan[nyIndex+3] = toDplan.at(alleIndexPar.at(i).hjorne[1]-1);

        nyToDplan[nyIndex+4] = toDplan.at(alleIndexPar.at(i).hjorne[2]-2);
        nyToDplan[nyIndex+5] = toDplan.at(alleIndexPar.at(i).hjorne[2]-1);

        nyToDplan[nyIndex+6] = toDplan.at(alleIndexPar.at(i).hjorne[2]+1);
        nyToDplan[nyIndex+7] = toDplan.at(alleIndexPar.at(i).hjorne[2]+2);
        nyToDplan[nyIndex+8] = toDplan.at(alleIndexPar.at(i).hjorne[2]+3);

        nyIndex += 9;

    }

    return nyToDplan;
}

const std::vector<float>& CelestialKropp::getUVKoordinater() const {return UV_koordinater;};

void Kule::Spherifiser(int inRadius){
    for (int i = 0; i < this->punkter.size(); i++){
        this->radius = inRadius;
        Punkt& p = this->punkter.at(i);
        p = p * inRadius / sqrt(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2));
    }
};

int Kule::getRadius() const{
    return this->radius;
};

std::vector<std::array<double, 2>> CelestialKropp::KartesiskTilSpherisk(){
    std::vector<std::array<double, 2>> spheriskKoordinat(this->punkter.size());
    int i = 0;
    for (Punkt p : this->punkter){
        double bredde = asin(p.z/this->getRadius()); // Phi
        double lengde = atan2(p.x , p.y); // lambda

        spheriskKoordinat.at(i) = {bredde, lengde};

        i++;
    }
    return spheriskKoordinat;
};

void CelestialKropp::brettUt(int bredde, int hoyde){
    std::vector<std::array<double, 2>> spheriskKoordinat = KartesiskTilSpherisk(); // [phi, lambda]

    this->UV_koordinater.clear();

    for (int t = 0; t < (int)this->indexer.size(); t += 3){
        float us[3], vs[3];

        for (int k = 0; k < 3; k++){
            std::array<double, 2>& p = spheriskKoordinat.at(this->indexer.at(t + k));
            us[k] = (p.at(1) + M_PI) / (2 * M_PI) * bredde;
            vs[k] = (M_PI / 2 - p.at(0)) / M_PI * hoyde;
        }

        float uMin = *std::min_element(us, us + 3);
        float uMax = *std::max_element(us, us + 3);
        if (uMax - uMin > bredde / 2.0f) continue;

        for (int k = 0; k < 3; k++){
            UV_koordinater.push_back(us[k]);
            UV_koordinater.push_back(vs[k]);
            UV_koordinater.push_back(this->sentrum.y);
        }
        TDT4102::Color c = this->farger.at(t / 3);
        UV_koordinater.push_back(c.redChannel);
        UV_koordinater.push_back(c.greenChannel);
        UV_koordinater.push_back(c.blueChannel);
    }
}

void CelestialKropp::mapBildeTilKule(const char* filbane){
    int w, h;
    std::vector<TDT4102::Color>* pixelFarger = lesBilde(filbane, w, h);
    std::vector<std::array<double, 2>> spherisk = KartesiskTilSpherisk();

    for (int t = 0; t < (int)this->indexer.size(); t += 3){
        float us[3], vs[3];
        for (int k = 0; k < 3; k++){
            std::array<double, 2>& p = spherisk.at(this->indexer.at(t + k));
            us[k] = (p.at(1) + M_PI) / (2 * M_PI);
            vs[k] = (M_PI / 2 - p.at(0)) / M_PI;
        }

        float uMin = *std::min_element(us, us + 3);
        float uMax = *std::max_element(us, us + 3);
        if (uMax - uMin > 0.5f){
            for (int k = 0; k < 3; k++)
                if (us[k] < 0.5f) us[k] += 1.0f;
        }

        float u = std::fmod((us[0] + us[1] + us[2]) / 3.0f, 1.0f);
        float v = (vs[0] + vs[1] + vs[2]) / 3.0f;

        int px = (int)(u * w) % w;
        int py = (int)(v * h) % h;

        this->farger.at(t / 3) = pixelFarger->at(py * w + px);
    }

    delete pixelFarger;
}

void Kube::genererTrekanter(){

    //PunktIndex
    for (int i = 0; i < 8; i++){
        indexer.push_back(i);
        indexer.push_back(i+1);
        indexer.push_back(i+2);
    }

    for (int i = 0; i < indexer.size(); i++){
        if (indexer.at(i) > 7){
            indexer.at(i) -= 7;
        };
    }

    indexer.push_back(1);
    indexer.push_back(2);
    indexer.push_back(6);

    indexer.push_back(2);
    indexer.push_back(5);
    indexer.push_back(6);

    indexer.push_back(0);
    indexer.push_back(3);
    indexer.push_back(4);

    indexer.push_back(0);
    indexer.push_back(4);
    indexer.push_back(7);


};
