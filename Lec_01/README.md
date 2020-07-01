# Lección 1: Reloj de sistema y puertos I/O

## Configuración de oscilador principal
Esta serie de microcontroladores trabajan a 3.3v lo que los hace más susceptibles al ruido si no se hace un buen conexionado. Es estrictamente necesario colocar capacitores de 0.1 uF entre cada par de pines Vdd-Vss como se muestra en la Figura 2-1 de la datasheet (yo estaré usando en este ejemplo un [PIC24FJ32GA002](http://ww1.microchip.com/downloads/en/DeviceDoc/39881e.pdf)):
<p align="center">
<img src="https://1.bp.blogspot.com/-U7qTi1OyQnA/Xscfy6lwBDI/AAAAAAAACQ8/b1U6awHRlzc-yVnJ9_K-zqCTBJmxDiZLwCLcBGAsYHQ/s1600/PIC24_Circuit.png" alt="alt text" width="550">
</p>

Si no se colocan estos capacitores el PIC tendrá un comportamiento errático debido al ruido. Usaré en este ejemplo un cristal de 8MHz con capacitores de 22pF. Una vez conectado el circuito podemos avanzar a la configuración del oscilador. Configuraremos el oscilador externo con PLL activado con la frecuencia de reloj FOSC máxima de 32 MHz (recordemos que FCY = FOSC/2). He marcado el camino que nos interesa sobre el diagrama de la Figura 8-1 de la página 95:



<p align="center">
<img src="https://1.bp.blogspot.com/-BotvCpbGnXw/XvoaxB-RycI/AAAAAAAACU0/8y7Vt3hDk-w3BpFFYbqoD6R-UgRkjO5hACLcBGAsYHQ/s1600/PIC24FJXXGA002_XTPLL.png" alt="alt text" width="540">
</p>


 Si estamos usando un cristal de 8 MHz ¿Qué modo es el adecuado? Eso lo ponemos encontrar en el [“PIC24F Family Reference Manual”,
“Oscillator” (DS39700)](http://ww1.microchip.com/downloads/en/devicedoc/39700c.pdf), tabla 6-2 de la pag. 13, el cual dice que es XT. EN el caso del GA002 si queremos usar el PLL deberemos poner la configuración FNOSC = PRIPLL. Ahora sólo necesitamos saber que bits de configuración necesitamos modificar. En la tabla 8-1 de la página 96 (del datasheet) podemos ver que son POSCMD y FNOSC. Para encontrar los macros necesarios podemos ir a Compiler Help en el dashboard de MPLAB X:

<p align="center">
<img src="https://1.bp.blogspot.com/-IgKQzTWcTx8/XscnggvYR2I/AAAAAAAACRU/Ewt5Bepko4okUATNAumV7PU5olFs0g6gwCLcBGAsYHQ/s320/compiler_help_MPLABX.png" alt="alt text">
</p>

Abrirá un archivo HTML donde debemos buscar Configuration Settings Reference. De ahí podrán copiar los pragmas requeridos. Ahora solo falta un ajuste más pero se hará escribiendo en un registro. Lo que falta es asegurarnos que FOSC tenga un frecuencia de 32 MHz. Para esto debemos revisar el registro CLKDIV (pág. 99) dónde podremos ver que el valor de división del último postcaler es de 0. En el [poster de infromación](http://ww1.microchip.com/downloads/en/DeviceDoc/50002010B.pdf) del programador PICkit 3 menciona que el JTAG debe estar desactivado. tambien es posible generar automaticamente los bits de configuración como se muestra en [este video](https://www.youtube.com/watch?v=bFaUxLTh9kk) (en ese ejemplo lo hacen para ensamblador pero si usan XC8 o XC16 aparecerán los bits de configuración para C). Las opciones de configuración minimas necesarias son:

```C
//--- Bits de configuración ---
#pragma config POSCMOD = XT             // Primary Oscillator Select (XT Oscillator mode selected)
#pragma config FNOSC = PRIPLL           // Oscillator Select (Primary Oscillator with PLL module (HSPLL, ECPLL))
#pragma config FWDTEN = OFF             // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config JTAGEN = OFF             // JTAG Port Enable (JTAG port is disabled)
//-----------------------------
```
Ahora tenemos toda la información necesaria para continuar con nuestro primer programa.

## Configuración de pines de entrada o salida
Todos los pines de puerto tienen 3 registros aosciados a su operación entrada/salida. El registro de dirección de datos TRISX determina si un pin es de entrada (1) o salida (0). Todos los puertos estan definidos como entrada despues de un reset. Para lectura/escritura están LATX y PORTX. Aunque es posible leer y escribir en cualquiera de ellos, como regla general *se escribe en LATX y se lee en PORTX*. El diagrama interneno de cada pin es el siguiente (FIG 10-1, pag. 105):

<p align="center">
<img src="https://1.bp.blogspot.com/-vU4O3I5XNcY/XvupzA4DB-I/AAAAAAAACVA/T33Rk8v4vK4zsZY1oKuB_UkKXRUy4LxnwCLcBGAsYHQ/s1600/GA002_IO.png" alt="alt text">
</p>

El voltaje de operación de los PIC24FJ es de 3.3V pero algunos pines son tolerantes a entrada de 5V (ver Tabla 10-1, pag. 106). Para tener salidas de 5V hay un 4to registro llamado *Open-Dran Control* (ODCX) donde se debe asiganar '1' para habilitar (si la opcion está disponible para ese pin) y colocar un [resistor pull-up](https://i.stack.imgur.com/W1Iwa.png) a 5V. 

## Ejemplo 1.1 Verificar frecuecuencia de oscilador con un LED

En este primer ejemplo (Ejemplo1_1_Prueba_OSC.c) verificaremos que el oscilador tenga la frecuencia correcta (32 MHz en este caso). El circuito que vamos a utilizar es el siguiente:

<p align="center">
<img src="https://1.bp.blogspot.com/-va-Bzj47O3Q/XvuwN4fHEjI/AAAAAAAACVM/KjHdEgLidJ0zAeqlvjjYB7uOq9bMsm2kQCLcBGAsYHQ/s1600/P1_1.png" alt="alt text" width="800">
</p>

Haremos que el LED se mantenga encendido 500 ms y apagado otros 500 ms. Para esto usaremos la función __delay_ms() que debemos tomar de <libpic30.h>.

## Ejemplo 1.2 Lectura sin rebote de un botón para toggle de un LED
En este ejemplo (Ejemplo1_2_Toggle.c) vamos a usar un push-button para invertir el estado de un led cada vez que se presione. El circuito utilizado es el siguiente:
<p align="center">
<img src="https://4.bp.blogspot.com/-d7IW2s7ghkc/XvvIPM05AqI/AAAAAAAACVk/xP_-JU2PfiEDW7UUdsMLL278fVPauTN5gCLcBGAsYHQ/s1600/P1_2.png" alt="alt text" width="850">
</p>

Parece un problema sencillo pero hay varios problemas que resolver. Primero hay que eliminar el fenómeno de rebote en el botón. Debido a la estructura mecánica del push-button, se producen vibraciones a la hora de presionarlo que provocan una intermitencia en la lectura del estado del botón. Para corregir este problema debemos tomar como lectura confiable el estado del pin de entrada en la zona que se encuentra justo en medio de los transientes por rebotes como se muestra en la siguiente imágen:

<p align="center">
<img src="https://1.bp.blogspot.com/---d0VgkwU6w/V7E9hSjEkdI/AAAAAAAABn8/jvqZJxAkAsIlOFOKC-GfnV7U8wRevz0iwCLcB/s400/switch_antirebote.png" alt="alt text">
</p>

Esto se reseulve vía software con la siguiente función de lectura del botón:
```C
char boton(){
    char estado = 0;
    if(PORTBbits.RB7 == 1){
        __delay_ms(5);
        if(PORTBbits.RB7 == 1)
            estado = 1;
    }
    return estado;
}
```
La variable de retorno es un *char* para ahorrar memoria durante su ejecución. Para invertir el estado del LED (operación toggle) podemos usar el siguiente macro:

```C
#define LED_Toggle()  (LATBbits.LATB10 ^= 1) // A^B = A XOR B
```

Ahora tenemos un último problema por resolver. No podemos simplemente *togglear* cuando el botón este presionado porque cambiaría el estado del led una y otra vez mientras el botón esté presionado. Lo que podemos hacer es solo *togglear* durante la transición de un apagado a encendido (flanco de subida) de la siguiente manera:

```C
char edo_viejo=0,edo_nuevo=0;
    
    while(1){
        edo_nuevo = boton();
        
        if(edo_nuevo==1 && edo_viejo==0)
            LED_Toggle();
        
        edo_viejo = edo_nuevo;
    }
```
