#pragma once
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include "widgets/CheckBox.h"
#include "widgets/Slider.h"
#include "widgets/TextBox.h"

void lagHovedmenyUI(
    TDT4102::AnimationWindow& window,
    TDT4102::CheckBox& jordCheck,
    TDT4102::CheckBox& solCheck,
    TDT4102::CheckBox& flyCheck,
    TDT4102::Slider& kvalitet,
    TDT4102::Button& startKnapp,
    bool& startFlag
);