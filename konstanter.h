#pragma once
#include "std_lib_facilities.h"
#include "utils.h"
#include "figurer.h"


//Skjerm
constexpr int WINDOW_POSITION_X = 700;
constexpr int WINDOW_POSITION_Y = 100;
constexpr int WINDOW_WIDTH = 1600;
constexpr int WINDOW_HEIGHT = 900;
constexpr std::string WINDOW_TITLE = "JordSim";

//Kamera
constexpr int NEAR = 1;
constexpr int FAR = 1000000000;
constexpr float KAMERA_1_FOV = 30.0;
constexpr double A_RATIO[2] = {16, 9};
const double FOCAL = (WINDOW_HEIGHT / 2) / std::tan(degToRad(KAMERA_1_FOV));
constexpr int skrittLengde = 500;
const double rotasjonsFart = degToRad(5);

//Figur
constexpr bool gradient = false;
constexpr bool kontur = false;

//Bilder

constexpr char* jordKart = "bilder/verden5k.jpg";
constexpr char* solKart = "bilder/sol1k.jpg";
constexpr bool tegnKart = false;
constexpr bool debug = true;

//Verden
const Punkt ORIGO{0, 0, 0};

