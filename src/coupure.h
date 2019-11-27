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
    ETAT_COUPURE _etatCourant;
    ETAT_COUPURE _etatFutur;
    LCM*  _afficheur;
    Music _music;
    bool _isStateDone;
    bool _isDone;
};