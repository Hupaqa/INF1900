#ifndef SELECTION_H
#define SELECTION_H

#include "display.h"

#define ddr_lcd DDRA
#define port_lcd PORTA

enum class EtatSelection{
    leCouloir,
    leMur,
    lesBoucles,
    lesCoupures
};

class Selection {
    public:
        Selection();

        void run();
        void changeState();
        void doAction();

    private:
    LCM _lcd;
    EtatSelection _etat;
    bool buttonEventBreadboard;
    bool buttonEventCard;
    uint8_t compteurEtat;
}