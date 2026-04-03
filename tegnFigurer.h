#pragma once
#include "AnimationWindow.h"
#include "std_lib_facilities.h"
#include "figurer.h"
#include "kamera.h"


int tegn2DFigur(TDT4102::AnimationWindow* window, Kamera& cam, const std::vector<float>& figurer);
int tegn3DFigur(TDT4102::AnimationWindow* window, Kamera& cam, const std::vector<Figur*>& figurer);