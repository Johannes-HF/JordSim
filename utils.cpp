#include "utils.h"
#include <random>
#include <cmath>
#include "figurer.h"

int randomInt(int low, int high){
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(low, high);

    return distribution(generator);
}

double degToRad(double deg){
    return deg * M_PI / 180.0;
}

bool sorterIndexPar(IndexPar& a, IndexPar& b){
    return a.total_Y_verdi > b.total_Y_verdi;
}

float stringAspectRatioToFloat(std::string aspectRatio){

    float breddeRatio;
    float hoydeRatio;
   
    bool telNevn = 0;

    for (char i : aspectRatio){
        if (!telNevn){
            breddeRatio *= 10;
            breddeRatio += i;
        }
        else{
            hoydeRatio *= 10;
            hoydeRatio += i;
        }
        if (i == '/'){
            telNevn = 1;
        }
    }

    const float aRatio = breddeRatio / hoydeRatio;

    return aRatio;
};
