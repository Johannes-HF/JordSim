#pragma once
#include "std_lib_facilities.h"
#include "figurer.h"
#include "kamera.h"
#include "fly.h"

int randomInt(int low, int high);
double degToRad(double deg);
bool sorterIndexPar(IndexPar& a, IndexPar& b);

float stringAspectRatioToFloat(std::string aRatio);

void printTrekantKoordinater(std::vector<float>& toDplan, int figurer);

void tegnKontur (AnimationWindow* window, TDT4102::Point p1, TDT4102::Point p2, TDT4102::Point p3);
    
void sjekkKeyPressed(Kamera& cam, AnimationWindow& window, long long dt, std::vector<Fly>& alleFly);

int getFPS(long long løkkeTidMs);

void debugInfo(const Kamera& cam, AnimationWindow& window, int FPS, int antallTrekanter);

void himmelLegemeInit(CelestialKropp& Tellus, CelestialKropp& Solen);

void lesFlydata(std::string flyFil, std::vector<Fly>& alleFly);

