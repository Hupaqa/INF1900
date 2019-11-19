#include "pathCorrector.h"

// Implémentation de l'error handler que l'on trouve pas dans
// AVR-LibC pour les methodes pures vitruelles
// En cas d'erreur, boucle à l'infini
// Source : https://stackoverflow.com/questions/920500/what-is-the-purpose-of-cxa-pure-virtual
extern "C" void __cxa_pure_virtual()
{
    while(true);
}

PathCorrector::PathCorrector(uint8_t vitesse) : 
    _vitesse (vitesse), 
    _navigator(Navigator())
    {};

void PathCorrector::initPWM()
{
    _navigator.initPWM();
};

void PathCorrector::ajustementPWM (uint8_t puissanceDroit, bool directionDroit, uint8_t puissanceGauche, bool directionGauche)
{
    _navigator.ajustementPWM(puissanceDroit, directionDroit, puissanceGauche, directionGauche);
};

void PathCorrector::stopPWM()
{
    _navigator.stopPWM();
};

uint8_t PathCorrector::getVitesse()
{
    return _vitesse;
};