#pragma once
#include <iostream>
#include "AnimationWindow.h"


TDT4102::Color getPixelColor(SDL_Surface* surf, int bredde, int hoyde);
std::vector<TDT4102::Color> lesBilde(char* filbane);
