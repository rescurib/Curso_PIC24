/*
 * File:   Ejemplo_4_1.c
 * Author: Rodolfo Escobar
 *
 * Created on 13 de diciembre de 2020, 04:38 PM
 */

//--- Bits de configuración ---
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config FNOSC = PRIPLL           // Oscillator Select (Primary Oscillator with PLL module (HSPLL, ECPLL))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)
//-----------------------------

#include<stdio.h>
#include <p24FJ32GA002.h>
#include "lcd.h"
#include "xc.h"
#define FCY 32000000UL 
#include "libpic30.h" // Para retardos por software

int main(void) {
//--- Setup ---
    AD1PCFGbits.PCFG2 = 1; // ADC2 dehabilitado (pag. 199)
    AD1PCFGbits.PCFG3 = 1; // ADC3 dehabilitado (pag. 199)
    AD1PCFGbits.PCFG4 = 1; // ADC4 dehabilitado (pag. 199)
    AD1PCFGbits.PCFG5 = 1; // ADC5 dehabilitado (pag. 199)
    //--- LCD ---
    LCD lcd = { &PORTB, 0, 1, 2, 3, 4, 5 }; // RS->A5, EN->A4, D4->A0, D5->A1, D6->A2, D7->A3
    LCD_Init(lcd);
       
    const double pi = 3.141592653;
    const double e  = 2.718281828;
    char buff[11];
    
    while(1){
        __delay_ms(100);
        sprintf(buff,"%.4f",pi); //.Xf -> X: cifras significativas
        LCD_Set_Cursor(0,2); // Primer renglón, segunda columna
        LCD_putrs("Pi = ");
        LCD_Set_Cursor(0,8); // Primer renglón, octava columna
        LCD_putrs(buff);
        
        sprintf(buff,"%.4f",e); //.Xf -> X: cifras significativas
        LCD_Set_Cursor(1,3); // Segundo renglón, tercera columna
        LCD_putrs("e = ");
        LCD_Set_Cursor(1,8); // Segundo renglón, octava columna
        LCD_putrs(buff);
    }
    return 0;
}
