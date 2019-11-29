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

╔═══════════════════════════════════════════════════════════════════════════════════════════╗
║                                      Table des états                                      ║
╠═════════════════════╦═══════════════════════╦═══════════════════════╦═══════════╦═════════╣
║     Etat présent    ║ Capteur gauche allume ║ Capteur gauche allume ║           ║         ║
╠═════════════════════╬═══════════════════════╩═══════════════════════╬═══════════╩═════════╣
║                     ║                      true                     ║        false        ║
╠═════════════════════╬═══════════════════════╦═══════════════════════╣                     ║
║                     ║   nIntersection = 3   ║   nIntersection < 3   ║                     ║
╠═════════════════════╬═══════════════════════╩═══════════════════════╬═════════════════════╣
║     SUIVRE_LIGNE    ║              ALLER_GROSSE_BOUCLE              ║     SUIVRE_LIGNE    ║
╠═════════════════════╬═══════════════════════╦═══════════════════════╬═════════════════════╣
║ ALLER_GROSSE_BOUCLE ║     GROSSE_BOUCLE     ║  ALLER_GROSSE_BOUCLE  ║ ALLER_GROSSE_BOUCLE ║
╠═════════════════════╬═══════════════════════╩═══════════════════════╬═════════════════════╣
║    GROSSE_BOUCLE    ║                 PETITE_BOUCLE                 ║    GROSSE_BOUCLE    ║
╠═════════════════════╬═══════════════════════════════════════════════╬═════════════════════╣
║    PETITE_BOUCLE    ║                   FIN_BOUCLE                  ║    PETITE_BOUCLE    ║
╠═════════════════════╬═══════════════════════════════════════════════╬═════════════════════╣
║      FIN_BOUCLE     ║                      QUIT                     ║      FIN_BOUCLE     ║
╠═════════════════════╬═══════════════════════════════════════════════╬═════════════════════╣
║         QUIT        ║                                               ║                     ║
╚═════════════════════╩═══════════════════════════════════════════════╩═════════════════════╝

*/

#ifndef BOUCLE_H
#define BOUCLE_H

#include "suiveurLigne.h"
#include "music.h"

enum ETAT_BOUCLE {
    SUIVRE_LIGNE,
    ALLER_GROSSE_BOUCLE,
    GROSSE_BOUCLE,
    PETITE_BOUCLE,
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
    *  fonction doAction et changeState tant que l'état actuel n'est pas QUIT.
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

    /*
     *  allerGrosseBoucle
     *  
     *  Cette fonction suis la ligne tant que le robot n'a pas croisé trois intersection
     *  soit le nombre d'intersection pour atteindre la grosse boucle
     */
    void allerGrosseBoucle();

    /*
     *  faireGrosseBoucles
     *  
     *  Cette fonction permet de faire le tour de la grosse boucle une fois celle-ci atteinte et engagée
     */
    void faireGrosseBoucle();

    /*
     *  fairePetiteBoucles
     *  
     *  Cette fonction permet de faire le tour de la petite boucle une fois celle-ci atteinte et engagée
     */
    void fairePetiteBoucle();

    /*
     *  virageCarrePetiteBoucle
     *  
     *  Cette fonction permet de faire un virage carré. Le robot tourne tant que la lumiène ne s'est
     *  allumé deux fois
     */
    void virageCarrePetiteBoucle();

    // Constantes propres à l'état
    static const uint8_t intersectionGrosseBoucle = 3;
    static const uint8_t nBoucles = 2;
    static const uint8_t nSegments = 3;

private:
    ETAT_BOUCLE _etat;
    LCM* _lcd;
};

#endif //BOUCLE_H
