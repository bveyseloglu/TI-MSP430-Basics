#include <msp430.h>

float array[100];
int i=0;

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // Stop WDT
    PM5CTL0 &= ~LOCKLPM5; // Enable IO

    // IO Setup - Configure P1.2 for ADC
    P1SEL1 |= BIT2;
    P1SEL0 |= BIT2;

    // Configure ADC12
    ADC12CTL0 = ADC12SHT0_2; // Sampling time, S&H=16 (ADC12 Sample Hold 0 Select Bit: 2)
    ADC12CTL0 = ADC12ON; // ADC12 on

    /* ADC12SHP: ADC12_B sample-and-hold pulse-mode select. This bit selects the source of the
    sampling signal (SAMPCON) to be either the output of the sampling timer or the
    sample-input signal directly.
    0b = SAMPCON signal is sourced from the sample-input signal.
    1b = SAMPCON signal is sourced from the sampling timer.*/
    ADC12CTL1 = ADC12SHP; // Use sampling timer (Sample/Hold Pulse Mode)

    ADC12CTL2 |= ADC12RES_2; // Set conversion resolution to 12 bit.
    ADC12MCTL0 |= ADC12INCH_2 + ADC12VRSEL_1; // A1 ADC input select (ADC12 Input Channel 2) + Vref=AVCC (ADC12 Select Reference 1)

    // Configure Timer Interupts
    TA0CCR0 = 327; // Counter value
    TA0CCTL0 |= CCIE; // Enable Timer interrupts
    TA0CTL |= TASSEL_1 + MC_1 + ID_0; // Source: ACLK, Up Mode (Counts to TA0CCR0), input divider by 1
    _BIS_SR(GIE); // Enter Low power mode 0 with interrupts enabled

    // (TA0CCR0 + 1) / (ACLK_FREQ / ID) = (327 + 1) / (32768 / 1) = 10 miliseconds between each interrupt

        while (1)
        {
            //__delay_cycles(5000); // interrupt ettigimizden dolayi bunun bir onemi oldugunu sanmiyorum

            ADC12CTL0 |= ADC12ENC; // Enable the ADC
            ADC12CTL0 &= ~ADC12SC; // Clear the start bit (as a precaution)
            ADC12CTL0 |= ADC12SC; // Enable and start a single conversion

            __bis_SR_register(LPM0_bits | GIE); // Go to LPM0. We'll exit the LMP at interrupt.

            if(i == 100)
            {
                i = 0; // reset i if
            }

            __no_operation(); // For debugger
        }

        __no_operation(); // For debugger
}

#pragma vector=TIMER0_A0_VECTOR // Timer0 A0 interrupt service routine
__interrupt void Timer0_A0 (void)
{
    array[i] = ADC12MEM0 * 0.02847; // Read the output of the ADC
    i++; // Increment the counter
    __bic_SR_register_on_exit(LPM0_bits); // Exit LPM
}

