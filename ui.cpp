#include "ui.h"

void startSim(){
    //bytt scene
}

TDT4102::CheckBox jordCheck{{100, 100,}, 200, 50, ""};
jordCheck.setLabel("Tegn Jorda");

TDT4102::CheckBox solCheck{{100, 200,}, 200, 50, ""};
solCheck.setLabel("Tegn Jorda");

TDT4102::CheckBox flyCheck{{100, 300,}, 200, 50, ""};
flyCheck.setLabel("Tegn Fly");

HM_window.add(jordCheck);
HM_window.add(solCheck);
HM_window.add(flyCheck);

TDT4102::Slider kvalitet{{100,400},200, 30, 0, 50, 0, 2};  //pos, bredde, hoyde, min, maks, init-verdi, delta

HM_window.add(kvalitet);

hovedMeny.lagKnapp(startSim, {100,400}, 200, 50, "Start Simulasjon");