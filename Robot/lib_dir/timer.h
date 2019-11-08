#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*************************************************************************************
**************************************************************************************
**Fonctions et variables qui permettent d'attendre un delais quelconque avec le timer 1
**Fonctions:
**  init_timer1 : initialise le timer1 et calcul le nombre de cycles a effectuer
**  delay_timer1 : effectue le plus grand nombre de cycle que permet timer1 et ajuste delayTimer1_cycles
**  reset_timer1 : arrete le timer1
**  ISR: appelle reset_timer1 ou delay_timer1 dependamment si le temps total est ecoule ou non
**
**Variables:
**  delayTimer1_cycles : nombre de cycle a effectuer pour avoir un delais de duree_ms
**  timer1done : sait si le delais total est termine
**************************************************************************************
**************************************************************************************/

extern volatile uint32_t delayTimer1_cycles;
extern volatile bool timer1done;

void init_timer1(uint16_t duree_ms);

void delay_timer1();

void reset_timer1();