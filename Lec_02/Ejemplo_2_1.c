/*
 * File:   Ejemplo_2_1.c
 * Author: Rodolfo Escobar
 *
 * Created on 3 de julio de 2020, 10:54 AM
 */

//--- Bits de configuración ---
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config FNOSC = PRIPLL           // Oscillator Select (Primary Oscillator with PLL module (HSPLL, ECPLL))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)
//-----------------------------

#include <p24FJ32GA002.h>

#include "xc.h"

#define FCY  16000000UL
#include "libpic30.h"


int sentido = 1; // Variable global de sentido

void __attribute__((interrupt(auto_psv))) _INT1Interrupt(void){
    if (IFS1bits.INT1IF && IEC1bits.INT1IE){
        sentido ^= 1;
        IFS1bits.INT1IF = 0;
    }
}

int main(void) {
    //-- Setup --
    TRISB &= 0xFF00; // RB0 - RB7 como salidas
    TRISBbits.TRISB14 = 1; // RB15 como entrada
    AD1PCFGbits.PCFG10 = 1; // ADC10 dehabilitado (pag. 199)
    
    // Mapeo de pines
    RPINR0bits.INT1R = 14; // INT1 <- RB14 (Tabla 10-2, pag. 108)
    
    IEC1bits.INT1IE = 1;    //INT1 habilitada (pag. 74)
    IPC5bits.INT1IP1 = 7;   // Prioridad máxima (pag. 32)
    INTCON2bits.INT1EP = 0; // Interrupción en flanco de subida (positiva) (pag. 65)
    //-----------
    
    while(1){
        if(!sentido){
            if(LATB==0)
                LATB = 1;
            __delay_ms(500);
            LATB = (LATB<<1)%255; // Corrimiento a la izquierda 
        }
        
        else{
            if(LATB==0)
                LATB = 128;
            __delay_ms(500);
            LATB = (LATB>>1)%255; // Corrimiento a la derecha
        }  
    }
    
    return 0;
}
