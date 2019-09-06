#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

enum Etat
{
    INIT_STATE,
    AMBER_STATE,
    GREEN1_STATE,
    GREEN2_STATE,
    RED_STATE,
    OFF_STATE
};

bool boutonDebounced()
{
    if (PIND & 0x04)
    {
        _delay_ms(10);
        if (PIND & 0x04)
        {
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

void setLedToAmber()
{
    const uint8_t GREEN_COLOR = 0x01;
    const uint8_t RED_COLOR = 0x02;

    PORTA = RED_COLOR;
    _delay_ms(1);
    PORTA = GREEN_COLOR;
    _delay_ms(2);
}

uint8_t changeState(Etat &currentState, bool inputPressed)
{
    const uint8_t NO_COLOR = 0x00;
    const uint8_t GREEN_COLOR = 0x01;
    const uint8_t RED_COLOR = 0x02;
    const uint8_t AMBER_COLOR = 0x03;

    switch (currentState)
    {
    case INIT_STATE:
        if (inputPressed)
        {
            currentState = AMBER_STATE;
        }
        else
        {
            currentState = INIT_STATE;
        }
        return RED_COLOR;

    case AMBER_STATE:
        if (inputPressed)
        {
            currentState = AMBER_STATE;
        }
        else
        {
            currentState = GREEN1_STATE;
        }
        return AMBER_COLOR;

    case GREEN1_STATE:
        if (inputPressed)
        {
            currentState = RED_STATE;
        }
        else
        {
            currentState = GREEN1_STATE;
        }
        return GREEN_COLOR;

    case RED_STATE:
        if (inputPressed)
        {
            currentState = RED_STATE;
        }
        else
        {
            currentState = OFF_STATE;
        }
        return RED_COLOR;

    case GREEN2_STATE:
        if (inputPressed)
        {
            currentState = GREEN2_STATE;
        }
        else
        {
            currentState = INIT_STATE;
        }
        return GREEN_COLOR;

    case OFF_STATE:
        if (inputPressed)
        {
            currentState = GREEN2_STATE;
        }
        else
        {
            currentState = OFF_STATE;
        }
        return NO_COLOR;

    default:
        return NO_COLOR;
    }
}

int main()
{
    const uint8_t AMBER_COLOR = 0x03;

    DDRA = 0xff; // Mode sortie pour le port A
    DDRD = 0x00; // Mode entrée pour le port D

    Etat currentState = INIT_STATE;
    uint8_t outputColor;

    while (true)
    {
        outputColor = changeState(currentState, boutonDebounced());
        if (outputColor == AMBER_COLOR)
        {
            setLedToAmber();
        }
        else
        {
            PORTA = outputColor;
        }
    }
}
