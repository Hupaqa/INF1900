/*
+--------------+----------------+-----------+--------------+
| currentState | input (button) | nextState | output (LED) |
+--------------+----------------+-----------+--------------+
| INIT         |        0       | INIT      |   NO_COLOR   |
+--------------+----------------+-----------+--------------+
| INIT         |        1       | ONE       |   NO_COLOR   |
+--------------+----------------+-----------+--------------+
| ONE          |        0       | ONE       |   NO_COLOR   |
+--------------+----------------+-----------+--------------+
| ONE          |        1       | TWO       |   NO_COLOR   |
+--------------+----------------+-----------+--------------+
| TWO          |        0       | TWO       |   NO_COLOR   |
+--------------+----------------+-----------+--------------+
| TWO          |        1       | THREE     |   NO_COLOR   |
+--------------+----------------+-----------+--------------+
| THREE        |        0       | THREE     |   NO_COLOR   |
+--------------+----------------+-----------+--------------+
| THREE        |        1       | FOUR      |   NO_COLOR   |
+--------------+----------------+-----------+--------------+
| FOUR         |        0       | FOUR      |   NO_COLOR   |
+--------------+----------------+-----------+--------------+
| FOUR         |        1       | INIT      |   COLOR_RED  |
+--------------+----------------+-----------+--------------+
*/

#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

enum State
{
    INIT,
    ONE,
    TWO,
    THREE,
    FOUR
};

bool buttonDebounced()
{
    if (PIND & 0x04)
    {
        _delay_ms(10);
        if (PIND & 0x04)
        {
            while (PIND & 0x04)
            {
            }
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

void turnLedRed()
{
    PORTA = (PORTA |= 0b00000010) & 0b11111110; // set to xxxxxx10
}


void turnLedOff()
{
    PORTA &= 0b11111100; // set to xxxxxx00
}


bool changeState(State &currentState, bool inputPressed)
{
    switch (currentState)
    {
    case INIT:
        if (inputPressed)
        {
            currentState = ONE;
            return true;
        }
        else
        {
            currentState = INIT;
            return false;
        }

    case ONE:
        if (inputPressed)
        {
            currentState = TWO;
            return true;
        }
        else
        {
            currentState = ONE;
            return false;
        }

    case TWO:
        if (inputPressed)
        {
            currentState = THREE;
            return true;
        }
        else
        {
            currentState = TWO;
            return false;
        }

    case THREE:
        if (inputPressed)
        {
            currentState = FOUR;
            return true;
        }
        else
        {
            currentState = THREE;
            return false;
        }

    case FOUR:
        if (inputPressed)
        {
            currentState = INIT;
            return true;
        }
        else
        {
            currentState = FOUR;
            return false;
        }
    
    default:
        return false;
    }
}

void doAction(const State &currentState, const bool inputPressed)
{
    const double ONE_SECOND = 1000; // 1000ms = 1sec

    switch (currentState)
    {
    case INIT:
    case ONE:
    case TWO:
    case THREE:
        break;

    case FOUR:
        if (inputPressed)
        {
            turnLedRed();
            _delay_ms(ONE_SECOND);
            turnLedOff();
        }
        break;
    }
}

int main()
{
    DDRA = 0xff; // Mode sortie pour le port A
    DDRD = 0x00; // Mode entrée pour le port D

    State currentState = State::INIT;
    bool buttonPressed = false;

    while (true)
    {
        doAction(currentState, buttonPressed);
        buttonPressed = changeState(currentState, buttonDebounced());
    }
}