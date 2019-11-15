#include "pathCorrector.h"

PathCorrector::PathCorrector(uint8_t vitesse = UINT8_MAX/2) : 
    _vitesse (vitesse), 
    _navigator(Navigator())
    {};