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

#include "suiveurLigne.h"
#include "music.h"

enum class ETAT_COUPURE {
    COUPURE1, 
    COUPURE2, 
    COUPURE3, 
    COUPURE4, 
    FIN
};

class Coupure : public SuiveurLigne {

public:
    /*  
     *  Constructeur par paramètres
     *  @param : 
     *      uint8_t vitesse : Represent la vitesse du robot
     *      LCM* ecran : permet d'afficher l'état sur le LCD
     * 
     *  Ce constructeur initialise d'abord le suiveur de ligne, 
     *  puis tous les attributs en initialisant les états courants et futur à
     *  COUPURE1.
     * 
     *  Le constructeur initialise également le port C en entrée et le port D en sortie
     *  et affiche sur le LCD que l'état actuel est Coupure
     */ 
    Coupure(uint8_t vitesse, LCM* ecran);
    
    /*
     *  run
     *   
     *  Cette fonction est la boucle principale de cette classe. Elle appelle les
     *  fonction doAction et changeState tant que l'étape n'est pas terminée.
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

private:
    static const uint8_t SON_GRAVE = 45;
    static const uint8_t SON_AIGU = 75;
    ETAT_COUPURE _etatCourant;
    ETAT_COUPURE _etatFutur;
    LCM*  _afficheur;
    Music _music;
    bool _isStateDone;
    bool _isDone;
};