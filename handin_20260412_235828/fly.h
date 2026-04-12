#pragma once
#include "figurer.h"

class Fly : public Figur{

    private:
        std::string icao24;
        std::string kalleNavn;
        std::string landOpprinnelse;
        int posisjon_tid;
        int nullTid;
        float lengdeGrad;
        float breddeGrad;
        float baroHoyde;
        bool onGround;
        float fart;
        float retning;
        float vertikalFart;

        Punkt retningVektor;

    public:

        Fly(std::string inIcao24, 
            std::string inKalleNavn, 
            std::string inLandOpprinnelse,
            int inPosisjon_tid, 
            int inNullTid, 
            float inLengdeGrad,
            float inBreddeGrad,
            float inBaroHoyde,
            bool inOnGround,
            float inFart,
            float inRetning,
            float inVertikalFart) 
            
            : 

            icao24(inIcao24),
            kalleNavn(inKalleNavn),
            landOpprinnelse(inLandOpprinnelse),
            posisjon_tid(inPosisjon_tid),
            nullTid(inNullTid),
            lengdeGrad(inLengdeGrad),
            breddeGrad(inBreddeGrad),
            baroHoyde(inBaroHoyde),
            onGround(inOnGround),
            fart(inFart),
            retning(inRetning),
            vertikalFart(inVertikalFart){ finnKartesisk();};

        void finnKartesisk(); //Setter sentrum i rommet og lager figuren
        void flyFremmover(long long dt, int flyHast);
        void roterMedJord();
        void printFlyData() const;
        void printSentrum() const;



};