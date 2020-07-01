/*
 * File:   Ejemplo1_2_Toggle.c
 * Author: Rodolfo
 *
 * Created on June 30, 2020, 6:36 PM
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

#define LED_Toggle()  (LATBbits.LATB10 ^= 1) // A^B = A XOR B

char boton(){
    char estado = 0;
    if(PORTBbits.RB7 == 1){
        __delay_ms(5);
        if(PORTBbits.RB7 == 1)
            estado = 1;
    }
    return estado;
}

int main(void) {
    // --- Setup ---
    TRISBbits.TRISB10 = 0; // LED
    TRISBbits.TRISB7  = 1; // Botón
   // -------------
    
    char edo_viejo=0,edo_nuevo=0;
    
    while(1){
        edo_nuevo = boton();
        
        if(edo_nuevo==1 && edo_viejo==0)
            LED_Toggle();
        
        edo_viejo = edo_nuevo;
    }
            
    return 0;
}
