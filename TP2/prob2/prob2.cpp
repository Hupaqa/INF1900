/*
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

enum State
{
    INIT_STATE,
    AMBER_STATE,
    GREEN1_STATE,
    GREEN2_STATE,
    RED_STATE,
    OFF_STATE
};

bool inputDebounced()
{
    if (PIND & 0x04)
    {
        _delay_ms(10);
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

void turnLedRed()
{
    PORTA = (PORTA | 0b00000010) & 0b11111110; // set to xxxxxx10
}

void turnLedGreen()
{
    PORTA = (PORTA | 0b00000001) & 0b11111101; // set to xxxxxx01
}

void turnLedOff()
{
    PORTA &= 0b11111100; // set to xxxxxx00
}

void turnLedAmber()
{
    turnLedRed();
    _delay_ms(1);
    turnLedGreen();
    _delay_ms(2);
}

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

void changeState(State &currentState, bool inputPressed)
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
        changeState(currentState, inputDebounced());
    }
}
