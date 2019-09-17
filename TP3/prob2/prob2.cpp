#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

void setMotorFoward()
{
    PORTA = 0x01;
}

void setMotorBackward()
{
    PORTA = 0x03;
}

void setMotorOff()
{
    PORTA = 0x00;
}

void delayNbCycles(uint32_t nCycles) 
{

    if (nCycles != 0)
    {
        nCycles /= 4;
        _delay_loop_2(nCycles);
    }
}

void doOnePeriod(uint32_t high, uint32_t low)
{
    setMotorFoward();
    delayNbCycles(high);
    setMotorOff();
    delayNbCycles(low);
}

void moveRobot(uint32_t frequency, uint8_t ratio, uint32_t seconds)
{
    uint32_t nbCycles = (8000000 / frequency);
    uint32_t high = (nbCycles / 100) * ratio;
    uint32_t low = nbCycles - high;
    uint32_t nbPeriods = frequency * seconds;
    
    for (uint32_t i = 0; i < nbPeriods; i++)
    {
        doOnePeriod(high, low);
    }
}

int main()
{
    DDRA = 0xff;  // PORTA set to output

    moveRobot(60, 0, 2);
    moveRobot(60, 25, 2);
    moveRobot(60, 50, 2);
    moveRobot(60, 75, 2);
    moveRobot(60, 100, 2);

    moveRobot(400, 0, 2);
    moveRobot(400, 25, 2);
    moveRobot(400, 50, 2);
    moveRobot(400, 75, 2);
    moveRobot(400, 100, 2);
}