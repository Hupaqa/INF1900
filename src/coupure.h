#include "suiveurLigne.h"

enum class ETAT_COUPURE {
    COUPURE1, COUPURE2, COUPURE3, COUPURE4, FIN
};

class Coupure : public SuiveurLigne {

public:

    /*  
     *  Parameter constructor
     *  @param vitesse : Represent speed of the robot.
     *  This constructor first call the SuiveurLigne parameter constructor
     *  with the vitesse parameter.  It then sets the variable etatCourant
     *  and etatFutur to ETAT_COUPURE::DEBUT.
     */ 
    Coupure(int vitesse);

    /*
     *
     * 
     */
    // bool suivreLigne();

    /*
     *
     * 
     */
    //void redressementDroit();

    /*
     *
     * 
     */
    //void redressementGauche();
    
    /*
     *  This funtion is the main loop of thi class, it calls doAction and
     *  changeState until the end of the section is reached.
     */ 
    void run();

    /*
     *  This funtion is a big switch case from etatPresent, it does the action of each section 
     *  and is called repeatedly until the robot reaches the end of the coupure section.
     */
    void doAction();

    /*
     *  This function is called in a while loop until the etatPresent finishes
     *  ETAT_COUPURE::FIN and only changes the state etatPresent to etatFutur.
     */
    void changeState();

private:
    ETAT_COUPURE etatCourant;
    ETAT_COUPURE etatFutur;
    bool isDone;
};