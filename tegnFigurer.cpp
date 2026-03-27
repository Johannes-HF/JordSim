#include "AnimationWindow.h"
#include "std_lib_facilities.h"
#include "tegnFigurer.h"
#include "figurer.h"
#include "utils.h"


void  tegn2DFigur(TDT4102::AnimationWindow* window, Kamera& cam, const std::vector<float>& figurer){

    std::vector<TDT4102::Color> farger {TDT4102::Color::green, TDT4102::Color::hot_pink, TDT4102::Color::royal_blue, TDT4102::Color::dark_orange};
    int fargeI = 0;

    std::vector<float> toDplan = sorter2Dplan(figurer);

    for (int i = 0; i < toDplan.size(); i+=9){

        if (fargeI > 11){ fargeI = 0;}

        std::vector<TDT4102::Point> punkter = {};

        for (int j = 0; j < 6; j+=2){

            TDT4102::Point p {toDplan.at(i+j), toDplan.at(i+j+1)};
            punkter.push_back(p);
           // std::cout << toDplan.at(i+j) << ", " <<  toDplan.at(i+j+1) << std::endl; // x og y koord
        }

        window->draw_triangle(
            punkter.at(0), 
            punkter.at(1),  
            punkter.at(2), 
            TDT4102::Color{toDplan.at(i+6), toDplan.at(i+7), toDplan.at(i+8)}
            //TDT4102::Color( (i) / static_cast<float>(toDplan.size()) * 255, 255 - (i) / static_cast<float>(toDplan.size()) * 255, 0)
            //figurer[0]->getFarger().at(fargeI / 3)
        );

        tegnKontur (window, punkter.at(0), punkter.at(1), punkter.at(2));
        
        fargeI ++;
    }
}


void tegn3DFigur(TDT4102::AnimationWindow* window, Kamera& cam, const std::vector<Figur*>& figurer){

    std::vector<float> usortertToDplan = cam.projiser(figurer);

    tegn2DFigur(window, cam, usortertToDplan);
    //printTrekantKoordinater(usortertToDplan, figurer.size());

};