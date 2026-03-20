#include "std_lib_facilities.h"
#include "AnimationWindow.h"
#include "figurer.h"
#include "konstanter.h"
#include <fstream>


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

int operator*(const Punkt& LHS, const Punkt& RHS){
  
    return LHS.x * RHS.x + LHS.y * RHS.y + LHS.z * RHS.z;
   
}

Figur::Figur(std::string filnavn, Punkt inSentrum){
    sentrum = inSentrum;
    sentrum.y += FOCAL;
    ifstream fil(filnavn);
    std::string linje;

    while(std::getline(fil, linje)){
        std::istringstream iss(linje);
        char identifier;
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

std::vector<Punkt> Figur::getPunkter() const { return punkter;};
std::vector<int> Figur::getIndexer() const { return indexer;};
std::vector<TDT4102::Color> Figur::getFarger() const { return farger;};
Punkt Figur::getSentrum() const {return sentrum;};

void Figur::endreSentrum(Punkt& nyttSentrum){
    sentrum = nyttSentrum;
}

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
