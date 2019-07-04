#include <msp430.h> 

// configure your connections here

int a = 0xFF;       //
int b = BIT7;       //
int c = BIT6;       //
int d = BIT5;       //
int e = BIT4;       //
int f = BIT3;       //
int g = BIT2;       //

int state = 9; // initial state
int stateEski = 9; // to check the changes in state

void yak(int led);
void sondur(int led);
void tumLedleriSondur();
void displayState();

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;

    P1DIR |= 0xFC; // set p1 output
    P3DIR |= 0x10; // set p3.4 output

    // Timer0_A setup
    TA0CCR0 = 32767; // Counter value
    TA0CCTL0 |= CCIE; // Enable Timer interrupts
    TA0CTL |= TASSEL_1 + MC_1 + ID_0; // Source: ACLK, Up Mode (Counts to TA0CCR0), input divider by 2
    _BIS_SR(GIE); // interrupts enabled

    displayState();

    while(1)
    {
           if (state != stateEski)
           {
               stateEski = state;
               displayState();
           }
    }

    return 0;
}

#pragma vector=TIMER0_A0_VECTOR // Timer0 A0 interrupt service routine
__interrupt void Timer0_A0 (void)
{
    if (state != 9)
        state++;
    else
        state = 0;
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

void displayState()
{
    tumLedleriSondur();
    if (state == 9) //0
    {
        yak(a);
        yak(b+c+d+e+f);
    }
    else if (state == 0) //1
    {
        yak(b+c);
    }
    else if (state == 1) //2
    {
        yak(a);
        yak(b+g+e+d);
    }
    else if (state == 2) //3
    {
        yak(a);
        yak(b+c+d+g);
    }
    else if (state == 3) //4
    {
        yak(f+g+b+c);
    }
    else if (state == 4) //5
    {
        yak(a);
        yak(f+g+c+d);
    }
    else if (state == 5) //6
    {
        yak(a);
        yak(c+d+e+f+g);
    }
    else if (state == 6) //7
    {
        yak(a);
        yak(b+c);
    }
    else if (state == 7) //8
    {
        yak(a);
        yak(b+c+d+e+f+g);
    }
    else if (state == 8) //9
    {
        yak(a);
        yak(b+c+d+f+g);
    }
}

void sondur(int led)  // anode
{
    if (led == a)
        P3OUT &= ~BIT4;
    else
        P1OUT &= ~led;
}

void yak(int led)     // anode
{
    if (led == a)
            P3OUT |= BIT4;
    else
            P1OUT |= led;
}

