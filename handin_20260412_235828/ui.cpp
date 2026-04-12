#include "ui.h"
#include "widgets/TextBox.h"

void lagHovedmenyUI(
    TDT4102::AnimationWindow& window,
    TDT4102::CheckBox& jordCheck,
    TDT4102::CheckBox& solCheck,
    TDT4102::CheckBox& flyCheck,
    TDT4102::Slider& kvalitet,
    TDT4102::Button& startKnapp,
    bool& startFlag
){

    jordCheck.setLabel("Tegn Jorda");
    jordCheck.setLabelColor (TDT4102::Color{255, 255, 255}); 
    solCheck.setLabel("Tegn Sola");
    solCheck.setLabelColor (TDT4102::Color{255, 255, 255}); 
    flyCheck.setLabel("Tegn Fly");
    flyCheck.setLabelColor (TDT4102::Color{255, 255, 255}); 


    startKnapp.setCallback([&startFlag](){ startFlag = true; });

    window.add(jordCheck);
    window.add(solCheck);
    window.add(flyCheck);
    window.add(kvalitet);
    window.add(startKnapp);
}