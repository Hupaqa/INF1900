#ifndef COULOIR_H
#define COULOIR_H

#include <avr/interrupt.h>
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
        ~Couloir();
        void run();
        bool finCouloir();
        void doAction();
        void changeState();
        void devierGauche();
        void devierDroite();
        void avancerGauche();
        void avancerDroite();
        void reinitialiserCompteur();

        static const uint8_t BOUNCE_RAPIDE = 35;
        static const uint8_t PWM_REFRESH = 50;
    private:
        EtatCouloir _etat;
        LCM* _lcd;
        bool _isDone;
        
        

};

#endif