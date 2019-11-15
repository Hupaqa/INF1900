#ifndef PATH_CORRECTOR
#define PATH_CORRECTOR

#include <avr/io.h>
#include "navigator.h"

class PathCorrector {
    public:
        PathCorrector(uint8_t vitesse = UINT8_MAX/2);

        virtual void redressementDroit() = 0;
        virtual void redressementGauche() = 0;

    protected:
        uint8_t _vitesse;
        Navigator _navigator;
};

#endif