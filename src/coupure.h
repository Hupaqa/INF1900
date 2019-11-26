#include "suiveurLigne.h"

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
     *  @param vitesse : Represent la vitesse du robot
     *  Ce constructeur initialise d'abord le suiveur de ligne, 
     *  puis tous les attributs en initialisant les états courants et futur à
     *  COUPURE1.
     * 
     *  Le constructeur initilise églement le port C en entrée et le port D en sortie
     *  et affiche sur le LCD que l'état actuel est Coupure
     */ 
    Coupure(int vitesse, LCM* ecran);
    
    /*
     *  run
     *  @param 
     *  Cette fonction est la boucle principale de cette classe. Elle appelle les
     *  fonction doAction et changeState tant que l'étape n'est pas terminée.
     */ 
    void run();

    /*
     *  doAction
     *  @param
     *  Cette fonction représente un switch case qui exécute les actions en fonction
     *  de l'état courant.
     */
    void doAction();

    /*
     *  changeState
     *  @param
     *  Cette fonction change l'état courant à l'état suivant de la machine à état
     */
    void changeState();

private:
    ETAT_COUPURE etatCourant;
    ETAT_COUPURE etatFutur;
    bool isStateDone;
    bool isDone;
    LCM*  afficheur;
};