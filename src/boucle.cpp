#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "boucle.h"

Boucle::Boucle(uint8_t vitesse, LCM* lcd) :
    SuiveurLigne(vitesse), 
    _etat(ETAT_BOUCLE::SUIVRE_LIGNE),
    _lcd(lcd)
{
    DDRC = 0x00; // Met le port D en entrée
    _lcd->write("Les deux boucles", 0, true);
};

void Boucle::run()
{
    while(_etat != ETAT_BOUCLE::QUIT)
    {
        doAction();
        changeState();
    }
};

void Boucle::doAction()
{
    switch (_etat)
    {
        case ETAT_BOUCLE::SUIVRE_LIGNE:
            _lcd->write("SUIVRELIGNE", 0, true);
            while (!(PINC & (1 << EXTREME_GAUCHE)))
            {
                suivreLigne();
            }
            break;
        case ETAT_BOUCLE::ALLER_GROSSE_BOUCLE : 
            allerGrosseBoucle();
            break;
        case ETAT_BOUCLE::GROSSE_BOUCLE: 
            faireGrosseBoucle();
            break;
        case ETAT_BOUCLE::PETITE_BOUCLE:
            fairePetiteBoucle();
            break;
        case ETAT_BOUCLE::FIN_BOUCLE: 
            while(suivreLigne());
            virageGaucheCaree();           
            break;
        case ETAT_BOUCLE::QUIT: 
            break;
    }
};

void Boucle::changeState(){
    switch(_etat)
    {
        case ETAT_BOUCLE::SUIVRE_LIGNE:
            _etat = ETAT_BOUCLE::ALLER_GROSSE_BOUCLE;
            break;
        case ETAT_BOUCLE::ALLER_GROSSE_BOUCLE : 
            _etat = ETAT_BOUCLE::GROSSE_BOUCLE;
            break;
        case ETAT_BOUCLE::GROSSE_BOUCLE:
            _etat = ETAT_BOUCLE::PETITE_BOUCLE;
            break;
        case ETAT_BOUCLE::PETITE_BOUCLE:
            _etat = ETAT_BOUCLE::FIN_BOUCLE;
            break;
        case ETAT_BOUCLE::FIN_BOUCLE: 
            _etat = ETAT_BOUCLE::QUIT;
            break;
        case ETAT_BOUCLE::QUIT: 
            break;
    }
};

bool Boucle::boucleDetectee()
{
    if (PINC & (1 << EXTREME_GAUCHE))
    {
        do
        {
            suivreLigne();
        } 
        while (PINC & (1 << EXTREME_GAUCHE));
        return true;
    }
    else
    {
        return false;
    }
    
}

void Boucle::allerGrosseBoucle()
{
    uint8_t intersectionCourrante = 0;

    while (intersectionCourrante != intersectionGrosseBoucle)
    {
        if (boucleDetectee()) 
        {
            intersectionCourrante++;
            _lcd->printUINT8(intersectionCourrante);
        }
        suivreLigne();
    }
}

void Boucle::faireGrosseBoucle()
{
    
    while(boucleDetectee())
    {
        suivreLigne();
    }
    virageGaucheCaree();
    for (uint8_t segmentEnCours = 0; segmentEnCours < nSegments; ++segmentEnCours)
    {
        while(suivreLigne());
        virageGaucheCaree();
    }
    while (!(PINC & (1 << MILIEU)));
}

void Boucle::fairePetiteBoucle()
{
    while(!boucleDetectee())
    {
        suivreLigne();
    }
    virageCarrePetiteBoucle();

    for (uint8_t segmentEnCours = 0; segmentEnCours < nSegments; ++segmentEnCours)
    {
        while(suivreLigne());
        virageCarrePetiteBoucle();
    }
}


void Boucle::virageCarrePetiteBoucle(){
    ajustementPWM(_vitesse, DIRECTION::AVANT, 0, DIRECTION::ARRIERE);
    while(!(PINC & (1 << EXTREME_GAUCHE)));
};
