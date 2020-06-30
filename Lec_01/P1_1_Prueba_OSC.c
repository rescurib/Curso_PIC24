/*
 * File:   P1_1_Prueba_OSC.c
 * Author: Rodolfo E. Escobar U
 *
 * Created on 23 de enero de 2020, 10:16 PM
 */

//--- Bits de configuración ---
#pragma config POSCMOD = XT       // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config FNOSC = PRIPLL     // Oscillator Select (Primary Oscillator with PLL module (HSPLL, ECPLL))
#pragma config FWDTEN = OFF       // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config JTAGEN = OFF       // JTAG Port Enable (JTAG port is disabled)
//-----------------------------

#include "xc.h"
#define FCY  32000000UL
#include "libpic30.h"

int main(void) {
   // --- Setup ---
    TRISBbits.TRISB10 = 0; // LED
   // -------------
   
    while(1){
        __delay_ms(500);
        LATBbits.LATB10 = 1;
        __delay_ms(500);
        LATBbits.LATB10 = 0;
    }
    return 0;
}
