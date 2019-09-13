/*
 * Nom : William Trépanier et Benjamin Theriault 
 * TP2
 * Problème 1
 * Date : 13 septembre 2019
 * Polytechnique Montréal
 * Cours : INF1900
 * Groupe laboratoire : 2

 * Table des états :
+--------------+----------------+-----------+------------------------+
| currentState | input (button) | nextState |      output (LED)      |
+--------------+----------------+-----------+------------------------+
| INIT         |        0       | INIT      |         nothing        |
+--------------+----------------+-----------+------------------------+
| INIT         |        1       | ONE       |         nothing        |
+--------------+----------------+-----------+------------------------+
| ONE          |        0       | ONE       |         nothing        |
+--------------+----------------+-----------+------------------------+
| ONE          |        1       | TWO       |         nothing        |
+--------------+----------------+-----------+------------------------+
| TWO          |        0       | TWO       |         nothing        |
+--------------+----------------+-----------+------------------------+
| TWO          |        1       | THREE     |         nothing        |
+--------------+----------------+-----------+------------------------+
| THREE        |        0       | THREE     |         nothing        |
+--------------+----------------+-----------+------------------------+
| THREE        |        1       | FOUR      |         nothing        |
+--------------+----------------+-----------+------------------------+
| FOUR         |        0       | FOUR      |         nothing        |
+--------------+----------------+-----------+------------------------+
| FOUR         |        1       | INIT      | flashRedLedOneSecond() |
+--------------+----------------+-----------+------------------------+
*/

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

/*
 * Liste des états
*/
enum State
{
    INIT,
    ONE,
    TWO,
    THREE,
    FOUR
};

/* 
 * Vérifie le statut du bouton en prenant deux lectures avec un délai de 10 ms.
 * 
 * @return true si le bouton est relaché suite à être enfoncée pendant 10ms, faux sinon
*/
bool returnButtonDebounced()
{
    const double DELAY = 10;

    if (PIND & 0x04)
    {
        _delay_ms(DELAY);
        if (PIND & 0x04)
        {
            while (PIND & 0x04)
            {
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

/*
 * Affecte la valeur correspondante à la couleur rouge aux pins 0 et 1 du port A. 
*/
void turnLedRed()
{
    PORTA = (PORTA | 0b00000010) & 0b11111110; // set to xxxxxx10
}

/*
 * Affecte aucune tension sur les pins 0 et 1 pour fermer la LED.
*/
void turnLedOff()
{
    PORTA &= 0b11111100; // set to xxxxxx00
}

/*
 * Affecte la couleur rouge sur la LED pendant une seconde.
*/
void flashRedLedOneSecond()
{
    const double ONE_SECOND = 1000;

    turnLedRed();
    _delay_ms(ONE_SECOND);
    turnLedOff();
}

/*
 * Met à jour l'état de la machine.
 * 
 * @param currentState état à modifier
 * @param inputPressed true si le bouton est relachée, false sinon
*/
void changeState(State &currentState, const bool &inputPressed)
{
    switch (currentState)
    {
    case INIT:
        if (inputPressed)
        {
            currentState = ONE;
        }
        break;

    case ONE:
        if (inputPressed)
        {
            currentState = TWO;
        }
        break;

    case TWO:
        if (inputPressed)
        {
            currentState = THREE;
        }
        break;

    case THREE:
        if (inputPressed)
        {
            currentState = FOUR;
        }
        break;

    case FOUR:
        if (inputPressed)
        {
            currentState = INIT;
        }
    }
}

/*
 * Effectue la ou les actions correspondant à l'état de la machine et du bouton
 * 
 * @param currentState l'état actuel 
 * @param inputPressed inputPressed true si le bouton est relachée, false sinon
*/
void doAction(const State &currentState, const bool &inputPressed)
{
    if (currentState == State::FOUR && inputPressed)
    {
        flashRedLedOneSecond();
    }
}

int main()
{
    DDRA = 0xff; // PORTA set to output
    DDRD = 0x00; // PORTD set to input

    State currentState = State::INIT;
    bool buttonPressed = false;

    while (true)
    {
        buttonPressed = returnButtonDebounced();
        doAction(currentState, buttonPressed);
        changeState(currentState, buttonPressed);
    }
}