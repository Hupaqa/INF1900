#ifndef COULOIR_H
#define COULOIR_H

#include "suiveurLigne.h"

class Couloir : public SuiveurLigne {
    public:

        /**
         * 
         * 
         **/
        Couloir(uint8_t vitesse, LCM* ecran);
        void run();
        void suivreCouloir();
        void correctionGauche();
        void correctionDroite();

    private:
        LCM* _lcd;
};

#endif