#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

bool boutonDebounced()
{
	if (PIND & 0x04) {
		_delay_ms(10);
		if (PIND & 0x04) {
            return true;
		}
		else return false;
	}
	else return false;
}

enum Etat {
    INIT,
    AMBRE,
    VERT1,
    VERT2,
    ROUGE,
    OFF
};

void changeState(Etat &currentState, bool inputPressed) {

    switch(currentState) {
        case INIT:
            if (inputPressed) {
                currentState = AMBRE;
            }
            else {
                currentState = INIT;
            }
            break;
        case AMBRE:
            if (inputPressed) {
                currentState = AMBRE;
            }
            else {
                currentState = VERT1;
            }
            break;
        case VERT1:
            if (inputPressed) {
                currentState = ROUGE;
            }
            else {
                currentState = VERT1;
            }
            break;
        case ROUGE:
            if (inputPressed) {
                currentState = ROUGE;
            }
            else {
                currentState = OFF;
            }
            break;
        case VERT2:
            if (inputPressed) {
                currentState = VERT2;
            }
            else {
                currentState = INIT;
            }
            break;
        case OFF:
            if (inputPressed) {
                currentState = VERT2;
            }
            else {
                currentState = OFF;
            }
            break;
    }
}

uint8_t outputColor(const Etat &currentState) {

}

int main() {
    return 0;
}