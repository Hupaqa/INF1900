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

    /*
     *  Constructeur par paramètres
     *  @param :
     *        uint8_t vitesse
     *        LCM* ecran : permet d'afficher l'état sur le LCD
     *   
     *  Constructeur qui initialise l'état initial à ligneDebut et qui
     *  qui configure le data directeur register du PINC en entrée pour
     *  le suiveur ligne. Il configure également le compteur 2 pour
     *  qu'il génère une interruption à chaque 0.032 seconde.
     */
    Couloir(uint8_t vitesse, LCM* ecran);

    /* 
     *  Destructeur
     * 
     *  Désactive le compteur 2 ainsi que les interruptions reliées à
     *  celui-ci lorsque le couloir est terminé. 
     */
    ~Couloir();

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
     *  Cette méthode représente un switch case qui exécute les actions en fonction
     *  de l'état courant.
     */
    void doAction();

    /*
     *  changeState
     *  
     *  Cette méthode change l'état courant, si nécessaire.
     */
    void changeState();

    /*
     *  reinitialiserCompteur
     *  
     *  Cette méthode réinitialise le compteur à 0.
     */
    void reinitialiserCompteur();

    /*
     *  finCouloir
     * 
     *  @return bool : vrai si la ligne de la fin est détectée
     * 
     *  Vérifie si les capteurs GAUCHE, MILIEU ou DROITE du suiveur ligne est
     *  allumé. Le cas échéant, retroune vrai puisque la fin du couloir est
     *  détectée.
     */
    bool finCouloir();

    /*
     *  devierGauche
     * 
     *  Méthode qui ajuste le PWM matérielle pour dévier vigoureusement le
     *  robot à gauche.
     */
    void devierGauche();

    /*
     *  devierDroite
     * 
     *  Méthode qui ajuste le PWM matérielle pour dévier vigoureusement le
     *  robot à droite.
     */
    void devierDroite();

    /*
     *  avancerGauche
     * 
     *  Méthode qui ajuste le PWM matérielle pour dévier doucement le robot
     *  à gauche.
     */
    void avancerGauche();

    /*
     *  avancerDroite
     * 
     *  Méthode qui ajuste le PWM matérielle pour dévier doucement le robot
     *  à droite.
     */
    void avancerDroite();

    // Constantes propres à l'objet couloir
    static const uint8_t BOUNCE_RAPIDE = 40;
    static const uint8_t PWM_REFRESH = 50;
    static const uint8_t VITESSE_BASE_DEVIATION = 32;
    static const uint8_t VITESSE_HAUTE_DEVIATION = 105;

private:
    EtatCouloir _etat;
    LCM* _lcd;
    bool _isDone;
        
        

};

#endif