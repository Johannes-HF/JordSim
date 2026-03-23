#pragma once
#include "std_lib_facilities.h"
#include "AnimationWindow.h"

struct Punkt{
    float x;
    float y;
    float z;
    bool l = 1;
};

std::ostream& operator<<(std::ostream& os, const Punkt& p);
Punkt operator+(const Punkt& LHS, const Punkt& RHS);
Punkt operator-(const Punkt& LHS, const Punkt& RHS);
float operator*(const Punkt& LHS, const Punkt& RHS); //prikk-produkt
Punkt operator*(const Punkt& LHS, const float t);
Punkt operator/(const Punkt& LHS, const float t);
Punkt operator^(const Punkt& LHS, const Punkt& RHS); //Kryssprodukt

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
    double omega; //Rotasjonshastighet
    Punkt rotAkse; //rotasjonsakse

    

    public:
    Figur(std::string filnavn, Punkt inSentrum);

    Punkt sentrum;

    const std::vector<Punkt>& getPunkter() const ;
    const std::vector<int>& getIndexer() const ;
    const std::vector<Punkt>& getRetning() const ;
    const std::vector<TDT4102::Color>& getFarger() const ;
    const Punkt& getSentrum() const ;
    const double getOmega() const ;
    const double getSpin() const ;

    void endreSentrum(Punkt& nyttSentrum);
    void sorterEtterDybde();
    void setSpin(double alfa, Punkt nyRotAkse);
    void dobleTrekanter(int antallDupliseringer);

    void roterFigur();

};

class Kube : public Figur
{
    public:
    Kube(std::string filnavn, Punkt inSentrum) : Figur(filnavn, inSentrum) {};

    void genererTrekanter();
};

class Kule : public Figur
{
    public:
    Kule(std::string filnavn, Punkt inSentrum) : Figur(filnavn, inSentrum) {};

    void Spherifiser(int radius);
};

std::vector<float> sorter2Dplan(std::vector<float>& toDplan);

//std::vector<int> genererTrekanter(std::vector<Punkt>& p);


    