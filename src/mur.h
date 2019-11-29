/*
MIT License
Copyright (c) 2019 
Jordan Lecourtois, Hugo Paquin, William Trépanier, Benjamin Theriault 

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
╔═════════════════════════════════════════════════════╗
║                   Table des états                   ║
╠══════════════╦═══════════════════════╦══════════════╣
║ État courant ║ SuiveurLigneAllumee() ║  État futur  ║
╠══════════════╬═══════════════════════╬══════════════╣
║  debutLigne  ║           X           ║   suivreMur  ║
╠══════════════╬═══════════════════════╬══════════════╣
║   suivreMur  ║         false         ║   suivreMur  ║
╠══════════════╬═══════════════════════╬══════════════╣
║   suivreMur  ║          true         ║  virageDroit ║
╠══════════════╬═══════════════════════╬══════════════╣
║  virageDroit ║           X           ║   finLigne   ║
╠══════════════╬═══════════════════════╬══════════════╣
║   finLigne   ║           X           ║ virageGauche ║
╚══════════════╩═══════════════════════╩══════════════╝
*/

#ifndef MUR_H
#define MUR_H

#include <util/delay.h>
#include <avr/interrupt.h>
#include "suiveurLigne.h"
#include "led.h"

enum EtatMur
{
    debutLigne, 
    suivreMur,
    virageDroit,
    finLigne, 
    virageGauche
};

class Mur : public SuiveurLigne
{
public:
    /* 
     *  Constructeur par paramètres
     *  @param :
     *        uint8_t vitesse
     *        LCM* ecran : permet d'afficher l'état sur le LCD
     *  
     *  Ce constructeur initialise l'état de la machine à état à debutLigne 
     *  et configure les data direction registers pour la led en en sortie 
     *  et le capteur de ligne en entrée. Il active également les interruptions
     *  sur les deux fronts pour la sortie du sonar. Il écrit également la 
     *  partie de l'épreuve sur le LCD.
     */
    Mur(uint8_t vitesse, LCM* lcd);

    /*
     * Destructeur
     * 
     * Ce destructeur s'assure de désactiver l'ensemble des interruptions 
     * pour que celles-ci n'interfèrent pas avec les autres épreuves du 
     * parcours. Il désactive également le compteur 2 utilisé par le sonar.
     */
    ~Mur();

     /*
     *  run
     *  
     *  Cette méthode est la boucle principale de cette classe. Elle appelle les
     *  méthode doAction et changeState tant que la variable _isDone soit vraie.
     */ 
    void run();

    /*
     *  doAction
     *  
     *  Cette méthode représente un switch case qui exécute les actions en 
     *  fonction de l'état courant.
     */
    void doAction();

    /*
     *  changeState
     *  
     *  Cette méthode change l'état courant à l'état suivant de la machine à 
     *  état.
     */
    void changeState();

    /*
     *  enableSonar
     *  
     *  Cette méthode active le signal enable du sonar pour 10us
     */
    void enableSonar();

    /*
     *  fetchSonar
     *  
     *  Cette méthode active le compteur 2 avec son prescaler de 64 ainsi 
     *  que les interruptions sur INT2 (output du sonar). Elle active le
     *  sonar par la suite.
     */
    void fetchSonar();

    /*
     *  moveToWall
     *  
     *  Cette méthode configure le PWM matériel pour que le robot s'approche
     *  du mur.
     */ 
    void moveToWall();

    /*
     *  moveToWall
     *  
     *  Cette méthode configure le PWM matériel pour que le robot s'éloigne
     *  du mur.
     */ 
    void moveAgainstWall();

    /*
     *  repositionnerSurLigne
     * 
     *  Cette méthode permet au robot de regagner la ligne lorsque le capteur
     *  de ligne rencontre la ligne à la fin du mur.
     */
    void repositionnerSurLigne();

    /*
     *  followWall
     * 
     *  Cette méthode est appellée continuellement lorsqu'il faut suivre le 
     *  mur. Elle interroge le sonar quant à la distance entre le robot et
     *  le mur et ajuste la direction du robot en conséquence.
     */
    void followWall();

    // Constantes propres à l'état
    static const uint8_t SONAR_DELAY = 10;
    static const uint16_t DEPASSER_LIGNE = 1000; 
    static const uint8_t FETCH_DELAY = 75;
    static const uint8_t BORNE_INFERIEUR = 14;
    static const uint8_t BORNE_SUPERIEUR = 16;
    static const uint8_t DISTANCE_MAXIMUM = 36;
    static const uint8_t DISTANCE_MINIMUM = 1;

private:
    EtatMur _etat;
    Led _led;
    LCM* _lcd;
    bool _isDone;
};

#endif // MUR_H