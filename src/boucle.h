#ifndef BOUCLE_H
#define BOUCLE_H

#include "suiveurLigne.h"

enum class ETAT_BOUCLE {
    ALLER_GROSSE_BOUCLE,
    FAIRE_BOUCLE,
    FIN_BOUCLE,
    QUIT
};

class Boucle : public SuiveurLigne 
{
public:
    /*  
    *  Constructeur par paramètres
    *  @param : 
    *       uint8_t vitesse
    *       LCM* ecran : permet d'afficher l'état sur le LCD
    * 
    *  Ce constructeur initialise l'état de la machine à etat à ALLER_GROSSE_BOUCLE,
    *  il initialise le lcd et affiche l'étape, soit "Les deux boucles". Il me également
    *  le port D en entrée. 
    */ 
    Boucle(uint8_t vitesse, LCM* lcd);

    /*
    *  run
    *  
    *  Cette fonction est la boucle principale de cette classe. Elle appelle les
    *  fonction doAction et changeState tant que tous l'état actuel n'est pas QUIT.
    */ 
    void run();

    /*
     *  doAction
     *  
     *  Cette fonction représente un switch case qui exécute les actions en fonction
     *  de l'état courant.
     */
    void doAction();

    /*
     *  changeState
     *  
     *  Cette fonction change l'état courant à l'état suivant de la machine à état
     */
    void changeState();

    /*
     *  boucleDetectee
     *  
     *  Cette fonction retourne si une boucle est détecter. Si une boucle est
     *  détectée, la fonction attend d'avoir dépassé l'intersection avant de retourner true
     */
    bool boucleDetectee();


    void allerGrosseBoucle();
    void suivreBoucles();

    static const uint8_t intersectionGrosseBoucle = 2;
    static const uint8_t nBoucles = 2;
    static const uint8_t nSegments = 3;

private:
    ETAT_BOUCLE _etat;
    LCM* _lcd;
};

#endif //BOUCLE_H
