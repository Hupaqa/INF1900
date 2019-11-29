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
    _lcd->write("les deux boucles", 0, true);
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
            while (!(PINC & (1 << MILIEU)))
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
    ajustementPWM(_vitesse, DIRECTION::AVANT, _vitesse, DIRECTION::ARRIERE);
    while(!(PINC & (1 << EXTREME_GAUCHE)));
};
