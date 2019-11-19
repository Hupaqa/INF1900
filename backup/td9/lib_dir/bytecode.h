#ifndef BYTECODE_H
#define BYTECODE_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "instruction.h"
#include "navigator.h"

struct ProgramCounter
{
    uint16_t programCounter = 0;
    uint16_t adresseDebutLoop;
    uint16_t nbLoop;
    uint16_t currentLoop;
    uint8_t instruction;
    uint8_t operande;
};


void execute_bytecode (ProgramCounter& pc);

void fx_att (const uint8_t& nbAtt);

void fx_dal (const uint8_t& delON);
void fx_det ();

void fx_sgo (const uint8_t& note);
void fx_sar ();

void fx_mar0 ();
void fx_mar1 ();
void fx_mav (const uint8_t& vitesseAV);
void fx_mre (const uint8_t& vitesseRE);

void fx_tdr ();
void fx_trg ();

void fx_dbc (ProgramCounter& pc);
void fx_fbc (ProgramCounter& pc);

void fx_fin ();

#endif // BYTECODE_H
