#include "lesBilder.h"
#include <iostream>
#include <SDL_image.h>

TDT4102::Color getPixelColor(SDL_Surface* surf, int bredde, int hoyde){


    uint8_t* p = static_cast<uint8_t*>(surf->pixels)  // må static caste fordi pekeren (pitch) og BytesPerPixel begge er i byte (int_8)
                + hoyde * surf->pitch                                                
                + bredde * surf->format->BytesPerPixel;

    uint8_t r, g, b;

    SDL_GetRGB(*reinterpret_cast<uint32_t*>(p), surf->format, &r, &g, &b);
    return TDT4102::Color{r, g, b};

};

std::vector<TDT4102::Color>* lesBilde(char* filbane, int& w, int& h){

    SDL_Surface* surf = IMG_Load(filbane);

    w = surf->w;
    h = surf->h;

    std::vector<TDT4102::Color>* farger = new std::vector<TDT4102::Color>(surf->w * surf->h);

    for (int i = 0; i < w; i ++){
        for (int k = 0; k < h; k++){
            farger->at(k * w + i) = getPixelColor(surf, i, k);
        }
    }
    SDL_FreeSurface(surf);
    return farger;
};