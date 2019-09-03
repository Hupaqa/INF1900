/*
ETAT PRESENT | BOUTON | ETAT SUIVANT | COULEUR LED
INIT         |    0   |    INIT      |    0x00    
INIT         |    1   |     ONE      |    0x00    
ONE          |    0   |     ONE      |    0x00    
ONE          |    1   |     TWO      |    0x00    
TWO          |    0   |     TWO      |    0x00    
TWO          |    1   |    THREE     |    0x00    
THREE        |    0   |    THREE     |    0x00    
THREE        |    1   |    FOUR      |    0x00    
FOUR         |    0   |    FOUR      |    0x00   
FOUR         |    1   |    INIT      |    0x02 
*/


#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

bool boutonDebounced()
{
	if (PIND & 0x04) {
		_delay_ms(10);
		if (PIND & 0x04) {
			while (PIND & 0x04);
            return true;
		}
		else return false;
	}
	else return false;
}

enum Etat{
    INIT,
    ONE,
    TWO,
    THREE,
    FOUR
};

uint8_t changeState(Etat &currentState, bool inputPressed) {
    const double ONE_SECOND = 1000; // 1000ms = 1sec
    const uint8_t NO_COLOR = 0x00; // Pas de couleur
    const uint8_t COLOR_RED = 0x02; // Couleur rouge

    switch(currentState) {
        case INIT:
            if (inputPressed) {
                currentState = ONE;
                return NO_COLOR;    
                }
            else {
                currentState = INIT;
                return NO_COLOR;
            }
            break;
        case ONE:
            if (inputPressed) {
                currentState = TWO;
                return NO_COLOR;
            }
            else {
                currentState = ONE;
                return NO_COLOR;
            }
            break;
        case TWO:
            if (inputPressed) {
                currentState = THREE;
                return NO_COLOR;
            }
            else {
                currentState = TWO;
                return NO_COLOR;
            }
            break;
        case THREE:
            if (inputPressed) {
                currentState = FOUR;
                return NO_COLOR;
            }
            else {
                currentState = THREE;
                return NO_COLOR;
            }
            break;
        case FOUR:
            if (inputPressed) {
                currentState = INIT;
                return COLOR_RED;
            }
            else {
                currentState = FOUR;
                return NO_COLOR;
            }
            break;
    }
}

int main() {
    const double ONE_SECOND = 1000; // 1000ms = 1sec
    const uint8_t NO_COLOR = 0x00; // Pas de couleur
    const uint8_t COLOR_RED = 0x02; // Couleur rouge

    DDRA = 0xff; // Mode sortie pour le port A
    DDRD = 0x00; // Mode entrée pour le port D

    Etat currentState = INIT;
    while(true) {
        PORTA = changeState(currentState, boutonDebounced());
        if (PORTA == COLOR_RED) {
            _delay_ms(ONE_SECOND);
        }
    }
}