#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    // LED'LERI OUTPUT YAP
    P1DIR |= BIT0;
    P4DIR |= BIT6;

    // SWITCHLERI INPUT YAP
    P1DIR &= ~BIT1;
    P4DIR &= ~BIT5;

    // SWITCHLERIN RESISTORLERINI ENABLE ET
    P1REN |= BIT1;
    P4REN |= BIT5;

    // SWITCHLERIN OUTPUTLARINI 1 YAP
    P1OUT |= BIT1;
    P4OUT |= BIT5;

    // YESIL RED'I 1 HZ FREKANSLA YAK EGER SWITCH 2'YE BASILIRSA IPTAL ET
    int yak = 1;

    while(yak)
    {
        __delay_cycles(20000); // debouncing icin 20 ms bekle
        if(!(P1IN & BIT1)) {
            yak = 0; // eger s2'ye basilirsa yanip sonme isini birak ve diger asamaya gec
        }
        __delay_cycles(480000); // debouncing icin bekledigimizi de goz onunde bulundurarak 20 ms'in üstüne 480 ms daha bekle ki 1 hz'e tamamlayalim
        P1OUT ^= BIT0; // led'i toggle et
    }

    // LEDLERI  SONDUR
    P1OUT &= ~BIT0;

    // 2. ASAMA

    while(1)
    {
        __delay_cycles(20000); // debouncing icin 20 ms bekle
        if (!(P1IN & BIT1)) // butona basarsa eger
        {
            while (!(P1IN & BIT1)); // butonu birakmasini bekle
            P1OUT ^= BIT0; // led'i toggle et
        }
    }

	return 0;
}
