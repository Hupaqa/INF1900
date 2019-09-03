#define F_CPU 8000000
#include <util/delay.h>
#include <avr/io.h>

bool boutonDebounced()
{
	if (PIND & 0x04) {
		_delay_ms(10);
		if (PIND & 0x04) {
			return true;
		}
		else return false;
	}
	else return false;
}

int main()
{
	const uint8_t VERT = 0x01;
	const uint8_t ROUGE = 0x02;
	DDRA = 0xff; // Mode sortie
	DDRD = 0x00; // Mode entrée

	while(true)
	{
		PORTA = VERT;
		_delay_ms(250);
		while (!boutonDebounced()){};
		PORTA = ROUGE;
		_delay_ms(250);
		while (!boutonDebounced()){};
		_delay_ms(250);
		while (!boutonDebounced()){
			PORTA = VERT;
			_delay_ms(3);
			PORTA = ROUGE;
			_delay_ms(1);
		}
	}
}
