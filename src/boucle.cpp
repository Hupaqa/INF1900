#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "boucle.h"

Boucle::Boucle(uint8_t vitesse, LCM* lcd) :
    SuiveurLigne(vitesse), 
    _etat(ETAT_BOUCLE::ALLER_GROSSE_BOUCLE),
    _lcd(lcd)
{
    DDRC = 0x00; // Met le port D en entrée
    _lcd->write("Les deux boucles", 0, true);
};

void Boucle::run(){
    while(_etat != ETAT_BOUCLE::QUIT)
    {
        doAction();
        changeState();
    }
};

bool Boucle::boucleDetectee()
{
    if ((PINC & EXTREME_GAUCHE) && (PINC & GAUCHE) && (PINC & MILIEU))
    {
        do
        {
            suivreLigne();
        } 
        while (!((PINC & EXTREME_GAUCHE) && (PINC & GAUCHE && (PINC & MILIEU))));
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
        }
        suivreLigne();
    }
}

void Boucle::suivreBoucles()
{
    for(uint8_t boucleCourante = 0; boucleCourante < nBoucles; ++boucleCourante)
    {
        while(boucleDetectee())
        {
            suivreLigne();
        }
        tournerGauche();
        for (uint8_t segmentEnCours = 0; segmentEnCours < nSegments; ++segmentEnCours)
        {
            while(suivreLigne());
            tournerGauche();
        }
    }
}

void Boucle::doAction()
{
    switch (_etat)
    {
        case ETAT_BOUCLE::ALLER_GROSSE_BOUCLE : 
            allerGrosseBoucle();
            break;
        case ETAT_BOUCLE::FAIRE_BOUCLE: 
            suivreBoucles();
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
        case ETAT_BOUCLE::ALLER_GROSSE_BOUCLE : 
            _etat = ETAT_BOUCLE::FAIRE_BOUCLE;
            break;
        case ETAT_BOUCLE::FAIRE_BOUCLE:
            _etat = ETAT_BOUCLE::FIN_BOUCLE;
            break;
        case ETAT_BOUCLE::FIN_BOUCLE: 
            _etat = ETAT_BOUCLE::QUIT;            
            break;
        case ETAT_BOUCLE::QUIT: 
            break;
    }
};
