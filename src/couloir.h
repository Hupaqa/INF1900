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

private:
    EtatCouloir _etat;
    LCM* _lcd;
    bool _isDone;
        
        

};

#endif