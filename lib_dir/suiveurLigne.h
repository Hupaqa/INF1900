#ifndef SUIVEUR_LIGNE
#define SUIVEUR_LIGNE

#include <util/delay.h>
#include "display.h"

#define MILIEU PINC4
#define GAUCHE PINC3
#define EXTREME_GAUCHE PINC2
#define DROITE PINC5
#define EXTREME_DROITE PINC6

enum DIRECTION{
    AVANT = 0,
    ARRIERE = 1
};

class SuiveurLigne
{
    public:
        /*  
        *  Constructeur par paramètres
        *  @param: uint8_t vitesse : Represent la vitesse du robot
        * 
        *  Ce constructeur initialise la vitesse du suiveur de ligne et la minuterie
        *  1 pour permettre le PWM des roues
        */ 
        SuiveurLigne(uint8_t vitesse);

        /*  
        *  ajustementPWM par paramètres
        *  @param: 
        *       uint8_t puissanceDroit : Represent la vitesse de la roue droite
        *       DIRECTION directionDroit : Represent la direciton de la roue droite
        *       uint8_t puissanceGauche : Represent la vitesse de la roue gauche
        *       DIRECTION directionGauche : Represent la direction de la roue gauche
        * 
        *  Cette fonction initialise les bits pour les diretions du moteurs (0: avant, 1: arriere).
        *  Ensuite, si les valeurs des puissances sont non nuls, la vitesse est mise à la valeur maximale
        *  pendant 5ms pour surpasser l'intertie. La vitesse est ensuite définie aux valeurs passées en paramètre
        */ 
        void ajustementPWM (uint8_t puissanceDroit, DIRECTION directionDroit, uint8_t puissanceGauche, DIRECTION directionGauche);
        
        /*  
        *  stopPWM
        * 
        *  Cette fonction permet de mettre OCR1A et OCR1B à 0 pour arreter le PWM
        */ 
        void stopPWM();

        /*  
        *  avancerDroit
        * 
        *  Cette fonction appelle la fonction ajustementPWM en lui passant _vitesse comme
        *  puissance pour les deux roues
        */ 
        void avancerDroit();

        /*  
        *  redressementDroit
        * 
        *  Cette fonction appelle la fonction ajustementPWM en lui passant _vitesse comme
        *  puissance pour la roue gauche et BASSE_INTENSITE pour la roue droite
        */ 
        void redressementDroit();

         /*  
        *  redressementGauche
        * 
        *  Cette fonction appelle la fonction ajustementPWM en lui passant _vitesse comme
        *  puissance pour la roue droite et BASSE_INTENSITE pour la roue gauche
        */ 
        void redressementGauche();

        /*  
        *  tournerDroit
        * 
        *  Cette fonction appelle la fonction ajustementPWM en lui passant  _vitesse comme
        *  puissance pour les deux roues. Cependant la roue gauche va vers l'avant et la roue droite
        *  vers l'arriere.
        *
        *  Le robot tourne tant que le capteur extérieur du suiveur de ligne n'est pas allumé
        */ 
        void tournerDroit();

        /*  
        *  tournerGauche
        * 
        *  Cette fonction appelle la fonction ajustementPWM en lui passant  _vitesse comme
        *  puissance pour les deux roues. Cependant la roue droite va vers l'avant et la roue gauche
        *  vers l'arriere.
        *
        *  Le robot tourne tant que le capteur extérieur du suiveur de ligne n'est pas allumé
        */ 
        void tournerGauche();

        /*  
        *  virageGaucheCaree
        * 
        *  Cette fonction fait avancer le robot pendant 1s puis appelle tournerGauche
        */ 
        void virageGaucheCaree();

        /*  
        *  suivreLigne
        * 
        *  @return: bool: retourne true si le suiveur de ligne détecte une ligne et false sinon
        *
        *  Cette fonction appelle suiveurLigneAllume et si le capteur
        *  ne detecte aucune ligne, il arrete le PWM et retourne false
        *
        *  Sinon, cette fonction fait avancer le robot droit si le capteur milieu du suiveur
        *  de ligne est actif, et appelle le redressement approprié si le capteur
        *  du milieu est éteint. Il retourne ensuite true
        */ 
        bool suivreLigne();

        /*  
        *  suiveurLigneAllume
        * 
        *  @return: bool: retourne true si le suiveur de ligne détecte une ligne et false sinon
        *
        *  Cette fonction verifie si le suiveur de ligne detecte une ligne et retourne le resultat
        */ 
        bool suiveurLigneAllume();
    protected:
        uint8_t _vitesse;
        static const uint8_t HAUTE_INTENSITE = 90;
        static const uint8_t BASSE_INTENSITE = 32;
        static const uint8_t OFF = 0;
};

#endif