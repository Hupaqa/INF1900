#ifndef SELECTION_H
#define SELECTION_H

#define BOUTON_INTERRUPT PIND2
#define BOUTON_BREADBOARD PIND3

#include "display.h"
#include "boucle.h"
#include "couloir.h"
#include "mur.h"
#include "coupure.h"
#include "uart.h"

enum EtatSelection
{
    selection,
    appeler,
    afficherFin,
    finParcours
};

enum EtapesParcours
{
    couloir,
    mur,
    boucles,
    coupures
};

class Selection 
{
    public:
        Selection(LCM* lcd);

        void run();
        void changeState();
        void doAction();

        void runStep();
        EtapesParcours nextStep();
        void updateFirstStep();

        bool breadboardDebounced();
        bool interruptDebounced();
    private:
        EtatSelection _etat;
        EtapesParcours _etapeCourrante;
        LCM* _lcd;
        
        const uint8_t NOMBRE_ETAPES = 4;
};

#endif //SELECTION_H