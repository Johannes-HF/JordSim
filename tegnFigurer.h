#pragma once
#include "AnimationWindow.h"
#include "std_lib_facilities.h"
#include "figurer.h"
#include "kamera.h"


void tegn2DFigur(TDT4102::AnimationWindow* window, Kamera& cam, const std::vector<float>& figurer);
void tegn3DFigur(TDT4102::AnimationWindow* window, Kamera& cam, const std::vector<Figur*>& figurer);