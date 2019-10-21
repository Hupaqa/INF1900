#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

#include <memoire_24.h>

void turnLedRed()
{
    PORTA = (PORTA | 0b00000010) & 0b11111110; // set to xxxxxx10
}

void turnLedGreen()
{
    PORTA = (PORTA | 0b00000001) & 0b11111101; // set to xxxxxx01
}

int main() 
{
    DDRA = 0xff;

    uint8_t TAILLE = 46;
    uint8_t chaine[TAILLE] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    Memoire24CXXX memoire;

    memoire.ecriture(0, &chaine[0], TAILLE);
    _delay_ms(5);

    uint8_t lecture[TAILLE];
    memoire.lecture(0, &lecture[0], TAILLE);

    bool pareil = true;
    int j = 0;
    while (j < TAILLE && pareil)
    {
        if (lecture[j] != chaine[j])
        {
            pareil = false;
        }
        j++;
    }

    if (pareil)
    {
        turnLedGreen();
    }
    else
    {
        turnLedRed();
    }
    
}