#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>
#include "bytecode.h"
#include "led.h"
#include "delay.h"
#include "play_music.h"
#include "notes.h"

void execute_bytecode (ProgramCounter& pc)
{
    switch(pc.instruction)
    {
        case DBT : break;
        case ATT : fx_att(pc.operande); break;
        case DAL : fx_dal(pc.operande); break;
        case DET : fx_det(); break;
        case SGO : fx_sgo(pc.operande); break;
        case SAR : fx_sar(); break;
        case MAR0 : fx_mar0(); break;
        case MAR1 : fx_mar1(); break;
        case MAV : fx_mav(pc.operande); break;
        case MRE : fx_mre(pc.operande); break;
        case TRD : fx_tdr(); break;
        case TRG : fx_trg(); break;
        case DBC : fx_dbc(pc); break;
        case FBC : fx_fbc(pc); break;
        case FIN : break;
    }
};

void fx_att (const uint8_t& nbAtt)
{
    for (unsigned i = 0; i < nbAtt; ++i)
    {
        _delay_ms(25);
    }
    //const uint8_t DELAY = 25;
    //delay_ms(DELAY * nbAtt);
};

void fx_dal (const uint8_t& delON)
{
    if (delON % 2)
    {
        turnRed();
    }
    else 
    {
        turnGreen();
    }
};

void fx_det ()
{
    turnOff();
};

void fx_sgo (const uint8_t& note)
{
    start_sound(note);
};

void fx_sar ()
{
    stop_sound();
};

void fx_mar0 ()
{
    stopPWM();
};

void fx_mar1 ()
{
    stopPWM();
};

void fx_mav (const uint8_t& vitesseAV){
    ajustementPWM(vitesseAV,0,vitesseAV,0);
};

void fx_mre (const uint8_t& vitesseRE)
{
    ajustementPWM(vitesseRE,1,vitesseRE,1);
};

void fx_tdr ()
{
    turndroite();
};

void fx_trg ()
{
    turngauche();
};

void fx_dbc (ProgramCounter& pc)
{
    pc.adresseDebutLoop = pc.programCounter;
    pc.nbLoop = pc.operande;
    pc.currentLoop = 0;
}

void fx_fbc (ProgramCounter& pc)
{
    ++pc.currentLoop;
    if (pc.currentLoop <= pc.nbLoop)
    {
        pc.programCounter = pc.adresseDebutLoop;
    }
    else
    {
        pc.adresseDebutLoop = 0;
        pc.currentLoop = 0;
        pc.nbLoop = 0;
    }
}