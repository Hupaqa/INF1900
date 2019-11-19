/*********************************************
 * PORTB : 
 *  PIN1: DEL LIBRE +
 *  PIN2: DEL LIBRE - 
 *  PIN3: PWM piezo
 *  PIN4: 0V
 * 
 * ******************************************/

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/delay.h>
#include "memoire_24.h"
#include "bytecode.h"

uint8_t lectureOctet(Memoire24CXXX& mem, ProgramCounter& pc)
{
    uint8_t lecture;
    uint8_t statut = mem.lecture(pc.programCounter, &lecture);
    _delay_ms(MEM_DELAY);
    pc.programCounter++;
    return lecture;
}

void fetchInstruction(Memoire24CXXX& mem, ProgramCounter& pc)
{
    pc.instruction = lectureOctet(mem, pc);
    pc.operande = lectureOctet(mem, pc);
}

bool waitForDBT(Memoire24CXXX& mem, ProgramCounter& pc)
{
    fetchInstruction(mem, pc);
    return (pc.instruction != DBT); 
}

int main()
{
    DDRB = 0xff;
    DDRD = 0xff;

    Memoire24CXXX mem;
    ProgramCounter pc;

    while (waitForDBT(mem, pc))
    {
    }

    do
    {
        fetchInstruction(mem, pc);
        execute_bytecode(pc);
    } 
    while (pc.instruction != FIN);
}