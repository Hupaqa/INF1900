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

void delayNbCycles(int nCycles) 
{

    if (nCycles != 0)
    {
        nCycles /= 4;
        _delay_loop_2(nCycles);
    }
}

void doOnePeriod(int high, int low)
{
    setMotorFoward();
    delayNbCycles(high);
    setMotorOff();
    delayNbCycles(low);
}

void moveRobot(int frequency, int ratio, int seconds)
{
    int nbCycles = (8000000 / frequency);
    int high = (nbCycles / 100) * ratio;
    int low = nbCycles - high;
    int nbPeriods = (8000000 / nbCycles) * seconds;

    for (int i = 0; i < nbPeriods; i++)
    {
        doOnePeriod(high, low);
    }
}

int main()
{
    DDRA = 0xff;  // PORTA set to output

    moveRobot(60, 100, 2);
    moveRobot(60, 75, 2);
    moveRobot(60, 50, 2);
    moveRobot(60, 25, 2);
    moveRobot(60, 0, 2);
    moveRobot(400, 100, 2);
    moveRobot(400, 75, 2);
    moveRobot(400, 50, 2);
    moveRobot(400, 25, 2);
    moveRobot(400, 0, 2);
}