#ifndef SELECTION_H
#define SELECTION_H

#include "display.h"
#include "boucle.h"
#include "couloir.h"
#include "mur.h"
#include "coupure.h"

enum class EtatSelection{
    leCouloir,
    leMur,
    lesBoucles,
    lesCoupures,
    Fin
};

class Selection {
    public:
        Selection();

        void run();
        void changeState();
        void doAction();

    private:
        EtatSelection _etat;
        uint8_t compteurEtat;
        LCM _lcd;
};

#endif //SELECTION_H