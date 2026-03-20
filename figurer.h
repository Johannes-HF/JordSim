#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"

struct Punkt{
    float x;
    float y;
    float z;
    bool l = 1;

    friend std::ostream& operator<<(std::ostream& os, const Punkt& p);

    friend Punkt operator+(const Punkt& LHS, const Punkt& RHS);
    friend Punkt operator-(const Punkt& LHS, const Punkt& RHS);
    friend int operator*(const Punkt& LHS, const Punkt& RHS);

};

inline std::array<Punkt, 6> enhetsVektor = {Punkt(1, 0, 0), Punkt(0, 1, 0), Punkt(0, 0, 1), Punkt(-1, 0, 0), Punkt(0, -1, 0), Punkt(0, 0, -1) };

struct IndexPar{
    std::array<int, 3> hjorne;
    float total_Y_verdi;
};

class Figur
{
    protected:

    std::vector<Punkt> punkter;
    std::vector<int> indexer;
    std::vector<TDT4102::Color> farger;

    

    public:
    Figur(std::string filnavn, Punkt inSentrum);

    Punkt sentrum;

    

    std::vector<Punkt> getPunkter() const ;
    std::vector<int> getIndexer() const ;
    std::vector<Punkt> getRetning() const ;
    std::vector<TDT4102::Color> getFarger() const ;
    Punkt getSentrum() const ;

    void endreSentrum(Punkt& nyttSentrum);
    void sorterEtterDybde();

};

class Kube : public Figur
{
    public:
    Kube(std::string filnavn, Punkt inSentrum) : Figur(filnavn, inSentrum) {};

    void genererTrekanter();
};

//std::vector<int> genererTrekanter(std::vector<Punkt>& p);

std::vector<Punkt>& roter(std::vector<Punkt> punkter, float thetaPrFrame);
    