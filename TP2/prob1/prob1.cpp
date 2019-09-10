/*
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

void turnLedRed()
{
    PORTA = (PORTA | 0b00000010) & 0b11111110; // set to xxxxxx10
}

void turnLedOff()
{
    PORTA &= 0b11111100; // set to xxxxxx00
}

void flashRedLedOneSecond()
{
    const double ONE_SECOND = 1000; // 1000ms = 1sec

    turnLedRed();
    _delay_ms(ONE_SECOND);
    turnLedOff();
}

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
        buttonPressed = buttonDebounced();
        doAction(currentState, buttonPressed);
        changeState(currentState, buttonPressed);
    }
}