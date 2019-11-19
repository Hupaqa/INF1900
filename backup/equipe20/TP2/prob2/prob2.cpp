/*
 * Nom : William Trépanier et Benjamin Theriault 
 * TP2
 * Problème 2
 * Date : 13 septembre 2019
 * Polytechnique Montréal
 * Cours : INF1900
 * Groupe laboratoire : 2

 * Table des états :
+--------------+----------------+-----------+----------------+
| currentState | input (button) | nextState |  output (LED)  |
+--------------+----------------+-----------+----------------+
| INIT         |        0       | INIT      |  turnLedRed()  |
+--------------+----------------+-----------+----------------+
| INIT         |        1       | AMBER     |  turnLedRed()  |
+--------------+----------------+-----------+----------------+
| AMBER        |        0       | GREEN     | turnLedAmber() |
+--------------+----------------+-----------+----------------+
| AMBER        |        1       | AMBER     | turnLedAmber() |
+--------------+----------------+-----------+----------------+
| GREEN1       |        0       | GREEN1    | turnLedGreen() |
+--------------+----------------+-----------+----------------+
| GREEN1       |        1       | RED       | turnLedGreen() |
+--------------+----------------+-----------+----------------+
| RED          |        0       | OFF       |  turnLedRed()  |
+--------------+----------------+-----------+----------------+
| RED          |        1       | RED       |  turnLedRed()  |
+--------------+----------------+-----------+----------------+
| OFF          |        0       | OFF       |  turnLedOff()  |
+--------------+----------------+-----------+----------------+
| OFF          |        1       | GREEN2    |  turnLedOff()  |
+--------------+----------------+-----------+----------------+
| GREEN2       |        0       | INIT      | turnLedGreen() |
+--------------+----------------+-----------+----------------+
| GREEN2       |        1       | GREEN2    | turnLedGreen() |
+--------------+----------------+-----------+----------------+
*/

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

/*
 * Liste des états
*/
enum State
{
    INIT_STATE,
    AMBER_STATE,
    GREEN1_STATE,
    GREEN2_STATE,
    RED_STATE,
    OFF_STATE
};

/* 
 * Vérifie le statut du bouton en prenant deux lectures avec un délai de 10 ms.
 * 
 * @return true si le bouton est enfoncé pendant 10ms, faux sinon
*/
bool returnInputDebounced()
{
    const double DELAY = 10;

    if (PIND & 0x04)
    {
        _delay_ms(DELAY);
        if (PIND & 0x04)
        {
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
 * Affecte la valeur correspondante à la couleur verte aux pins 0 et 1 du port A.
*/
void turnLedGreen()
{
    PORTA = (PORTA | 0b00000001) & 0b11111101; // set to xxxxxx01
}

/*
 * Affecte aucune tension sur les pins 0 et 1 pour fermer la LED.
*/
void turnLedOff()
{
    PORTA &= 0b11111100; // set to xxxxxx00
}

/*
 * Affecte en alternance les couleurs rouges et vertes pour obtenir la couleur
 * ambre. 
*/
void turnLedAmber()
{
    const double VERY_SHORT_DELAY = 1;
    const double SHORT_DELAY = 2;

    turnLedRed();
    _delay_ms(VERY_SHORT_DELAY);
    turnLedGreen();
    _delay_ms(SHORT_DELAY); // Add a little more green to achieve amber
}

/*
 * Effectue la ou les actions correspondant à l'état en cours
 * 
 * @param currentState l'état actuel 
*/
void doAction(const State &currentState)
{
    switch (currentState)
    {
    case INIT_STATE:
        turnLedRed();
        break;
    case AMBER_STATE:
        turnLedAmber();
        break;
    case GREEN1_STATE:
    case GREEN2_STATE:
        turnLedGreen();
        break;
    case RED_STATE:
        turnLedRed();
        break;
    case OFF_STATE:
        turnLedOff();
    }
}

/*
 * Met à jour l'état de la machine.
 * 
 * @param currentState état à modifier
 * @param inputPressed true si le bouton est enfoncé, false sinon
*/
void changeState(State &currentState, const bool &inputPressed)
{
    switch (currentState)
    {
    case INIT_STATE:
        if (inputPressed)
        {
            currentState = AMBER_STATE;
        }
        break;

    case AMBER_STATE:
        if (!inputPressed)
        {
            currentState = GREEN1_STATE;
        }
        break;

    case GREEN1_STATE:
        if (inputPressed)
        {
            currentState = RED_STATE;
        }
        break;

    case RED_STATE:
        if (!inputPressed)
        {
            currentState = OFF_STATE;
        }
        break;

    case OFF_STATE:
        if (inputPressed)
        {
            currentState = GREEN2_STATE;
        }
        break;

    case GREEN2_STATE:
        if (!inputPressed)
        {
            currentState = INIT_STATE;
        }
    }
}

int main()
{
    DDRA = 0xff; // PORTA to output
    DDRD = 0x00; // PORTD to input

    State currentState = State::INIT_STATE;

    while (true)
    {
        doAction(currentState);
        changeState(currentState, returnInputDebounced());
    }
}
