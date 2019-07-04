#include <msp430.h> 

// configure leds
int a = 0xFF;       //
int b = BIT7;       //
int c = BIT6;       //
int d = BIT5;       //
int e = BIT4;       //
int f = BIT3;       //
int g = BIT2;       //

void yak(int led);
void sondur(int led);
void tumLedleriSondur();

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= 0xFC; // set p1 output
    P3DIR |= 0x10; // set p3.4 output

    tumLedleriSondur();

    int dongu = 5; // "dongu" means "loop" in turkish

    while(1)
    {
        tumLedleriSondur();

        if (dongu == 5) //0
        {
            yak(a);
            dongu =0;
        }
        else if (dongu == 0) //1
        {
            yak(b);
            dongu=1;
        }
        else if (dongu == 1) //2
        {
            yak(c);
            dongu=2;
        }
        else if (dongu == 2) //3
        {
            yak(d);
            dongu=3;
        }
        else if (dongu == 3) //4
        {
            yak(e);
            dongu=4;
        }
        else if (dongu == 4) //5'
        {
            yak(f);
            dongu=5;
        }


        __delay_cycles(37000); // wait for 500 ms
    }

    return 0;
}

/*
	Note:
	All LEDs can be activated bu summing except a.
	eg. b+c+d
*/

void tumLedleriSondur()
{
    sondur(a);
    sondur(b+c+d+e+f+g);
}

void sondur(int led)
{
    if (led == a)
        P3OUT |= BIT4;
    else
        P1OUT |= led;
}

void yak(int led)
{
    if (led == a)
        P3OUT &= ~BIT4;
    else
        P1OUT &= ~led;
}

