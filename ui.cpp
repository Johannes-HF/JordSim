#include "ui.h"
#include "widgets/CheckBox.h"
#include "widgets/Slider.h"
#include "widgets/Button.h"

void startSim(AnimationWindow* window){
    window->deleteWidgets();
}

void lagHovedmenyUI(AnimationWindow& window){

    TDT4102::CheckBox jordCheck{{100, 100}, 200, 50, ""};
    jordCheck.setLabel("Tegn Jorda");

    TDT4102::CheckBox solCheck{{100, 200}, 200, 50, ""};
    solCheck.setLabel("Tegn Sola");

    TDT4102::CheckBox flyCheck{{100, 300}, 200, 50, ""};
    flyCheck.setLabel("Tegn Fly");

    window.add(jordCheck);
    window.add(solCheck);
    window.add(flyCheck);

    TDT4102::Slider kvalitet{{100, 400}, 200, 30, 1, 7, 0, 1};
    window.add(kvalitet);

    TDT4102::Button startKnapp({100, 500}, 200, 50, "Start Simulasjon");
    startKnapp.setCallback([&window](){ startSim(&window); });
    window.add(startKnapp);
}