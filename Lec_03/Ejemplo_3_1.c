//--- Bits de configuración ---
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config FNOSC = PRIPLL           // Oscillator Select (Primary Oscillator with PLL module (HSPLL, ECPLL))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)
//-----------------------------

#include "xc.h"

void gpio_init(void);

void __attribute__((interrupt, auto_psv)) _T1Interrupt (void){
  _T1IF = 0;			// Limpiar bandera irq 
  LATBbits.LATB10 ^= 1; // Toggle del LED 
}

int main(void) {
//--- Setup ---
    gpio_init();
    // Timer
    T1CON = 0x00;          // Detiene temporizador
    T1CONbits.TCS = 0;     // Entrada por reloj interno (FCY) (pag. 150)
    TMR1 = 0x00;           //Limpia el regitro de temporizador
    PR1 = 333;             //Carga el periodo 20 us (48 kHz)
    IPC0bits.T1IP = 0x01;  //Prioridad de interrupción
    IFS0bits.T1IF = 0;     //Limpia bandera de periodo
    IEC0bits.T1IE = 1;     //Habilita la interrupción por TMR1
    T1CONbits.TON = 1;     //Inicia TMR1    
 //-------------
    
    while(1)
    {
     //--------//
    }
    
    return 0;
}

void gpio_init(void){
    TRISBbits.TRISB10 = 0; // LED
}
