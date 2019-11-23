#ifndef COULOIR_H
#define COULOIR_H

#include "suiveurLigne.h"

enum EtatCouloir
{
    ligneDebut,
    limite_gauche,
    avancer_gauche,
    avancer_droite,
    limite_droite, 
    ligneFin,
    virageFin
};

class Couloir : public SuiveurLigne 
{
    public:

        /**
         * 
         * 
         **/
        Couloir(uint8_t vitesse, LCM* ecran);
        void run();
        bool finCouloir();

        void doAction();
        void changeState();

        void devierGauche();
        void devierDroite();

        void avancerGauche();
        void avancerDroite();

        void partirTimer();
        
    private:
        EtatCouloir _etat;
        LCM* _lcd;
        bool _isDone;

};

#endif