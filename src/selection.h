#ifndef SELECTION_H
#define SELECTION_H

#define BOUTON_BREADBOARD PIND2
#define BOUTON_INTERRUPT PIND3

#include "display.h"
#include "boucle.h"
#include "couloir.h"
#include "mur.h"
#include "coupure.h"

enum EtatSelection
{
    selection,
    appeler,
    afficherFin,
    fin
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
        
        const uint8_t nombreEtapes = 4;
};

#endif //SELECTION_H