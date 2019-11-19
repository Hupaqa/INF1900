#include "pathCorrector.h"

PathCorrector::PathCorrector(uint8_t vitesse = UINT8_MAX/2) : 
    _vitesse (vitesse), 
    _navigator(Navigator())
    {};

void PathCorrector::initPWM(){
    _navigator.initPWM();
};

void PathCorrector::ajustementPWM (uint8_t puissanceDroit, bool directionDroit, uint8_t puissanceGauche, bool directionGauche){
    _navigator.ajustementPWM (uint8_t puissanceDroit, bool directionDroit, uint8_t puissanceGauche, bool directionGauche);
};

void PathCorrector::stopPWM(){
    _navigator.stopPWM();
};

uint8_t PathCorrector::getVitesse(){
    return _vitesse;
};