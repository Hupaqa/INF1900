#include "suiveurLigne.h"



class Coupure : public SuiveurLigne {
public:
    Coupure();

    virtual void redressementDroit();
    virtual void redressementGauche();

private:

};