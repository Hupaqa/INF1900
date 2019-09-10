#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

void turnLedRed()
{
    PORTA = (PORTA | 0b00000010) & 0b11111110; // set to xxxxxx10
}

void turnLedOff()
{
    PORTA &= 0b11111100; // set to xxxxxx00
}

void delayNumberOfCycles(uint16_t nCycles) 
{
    if (nCycles != 0)
    {
        nCycles /= 4;
        _delay_loop_2(nCycles);
    } 
}

void turnLedAccordingToBrightness(uint8_t ratio) 
{
    uint16_t red = 0x50 * ratio; // 80 * ratio
    uint16_t off = 0x1F40 - red; // 8000 - red

    turnLedRed();
    delayNumberOfCycles(red);
    turnLedOff();
    delayNumberOfCycles(off);
}

void dimRedLed() 
{
    uint8_t brightness = 0x64; // 100
    for (uint16_t i = 0; i <= 0xBB8; i++)
    {
        turnLedAccordingToBrightness(brightness);
        if (i % 0x1E == 0) 
        {
            brightness -= 0b1; // decrease brightness by 1 every 30 iterations
        }
    }
}

int main()
{
    DDRA = 0xff; // PORTA set to output
    
    dimRedLed();
}