#ifndef COULOIR_H
#define COULOIR_H

#include "suiveurLigne.h"

class Couloir : public SuiveurLigne {
    public:

        /**
         * 
         * 
         **/
        Couloir(uint8_t vitesse);
        void run();
        void suivreCouloir();

    private:
};

#endif