# Lección 2: Interrupciones externas
## Concepto de interrupción 
Dada una secuencia prinpcipal de instrucciones (programa principal), una interupción es un salto hacia una secuecia especial (rutina o servicio de interrupción) a condición de que un evento particualar ocurra, para despues volver a la secuencia original del programa principal. 

<p align="center">
<img src="https://3.bp.blogspot.com/-pmfu-BEH9UM/Xv_zFRwELII/AAAAAAAACWA/hX-B3kd2OOs-gT38Qyy8jOMnPwhvMK2YwCLcBGAsYHQ/s1600/rutina_interrupcion_PIC.png" alt="alt text" width="850">
</p>

El evento que provoca el salto define el tipo de interrupción. En esta lección trataremos el tipo más sencillo el cual se trata de un cambio de estado externo en alguno de los pines de entrada. 

## Ejemplo 2.1 Cambio de dirección de una secuencia de LEDs
Tenemos un serie de 8 leds con una secuencia de encedido de 1 segundo por led y debemos cambiar el sentido de la secuencia con un push-button como se muetra en el siguiente circuito:

<p align="center">
<img src="https://2.bp.blogspot.com/-pt6lpnid1_c/Xv_RUB6qq6I/AAAAAAAACV0/YB1JiDSUGlwK0t_dNpJcctjJykKqfNmjQCLcBGAsYHQ/s1600/P21.png" alt="alt text" width="850">
</p>
 
Este es un ejemplo sencillo que ejemplifica bastante bien la necesidad de las interrupciones. Hasta ahora la única forma de hacer retardos que hemos mostrado es mediante la función _\_delay_ms(). Hay otras formas (que verémos en la próxima lección), pero seguiremos usandola para este ejemplo. Esta funcíón crea un tiempo muerto en el cual el procesador del PIC pierde tiempo mientras dura el retardo elegido. El segmento de código para la secuencia de luces es:

```C
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
```

Si no usamos una interrupción externa que realice el cambio de dirección tenemos el problema de que tenemos una ventana de tiempo pequeñisima entre la ejecución de los retardos. Lo que necesitamos es que el procesador ejecute una rutina que invierta el giro en el momento que se necesite y no cuando él *pueda*.   

De acuerdo a la [guía de usuario del compilador XC16](https://ww1.microchip.com/downloads/en/DeviceDoc/XC16%20C%20Compiler%20UG%20DS50002071J.pdf) (Sec. 14.3.3 pag. 215), la manera que declaramos el prototipo de rutina de interrupción es la siguiente:

```C
void __attribute__((interrupt(auto_psv))) isr0(void);
```
El atributo *auto_psv* le avisa al compilador que la función no debe tomar tomar parametros o retornar valores. El nombre de la rutuna *isr0* debe ser sustiudo por uno adecuado para la interrupción externa el cual se puede encontrar en la ayuda del compilador:

<p align="center">
<img src="https://1.bp.blogspot.com/-IgKQzTWcTx8/XscnggvYR2I/AAAAAAAACRU/Ewt5Bepko4okUATNAumV7PU5olFs0g6gwCLcBGAsYHQ/s320/compiler_help_MPLABX.png" alt="alt text">
</p>

Hay que ir a la sección *Interrupt Vector Tables Reference* y buscar el dispositivo que se esté utilizando. En la tabla que aparece se puede encontrr el nombre *_INT1Interrupt*. La rutina completa nos queda:

```C
void __attribute__((interrupt(auto_psv))) _INT1Interrupt(void){
    if (IFS1bits.INT1IF && IEC1bits.INT1IE){
        sentido ^= 1;
        IFS1bits.INT1IF = 0;
    }
}
```
El campo INT1IF del registro IFS1 (pag. 68) es la bandera que se levanta cuando la interrupción externa INT1 se activa. Ahora solo queda configurar el pin y habilitar la interrupción. Si se observa el diagrmama de pines del PIC24FJGA002 se notará que sólo aparece indicado  el pin de interrupcion INT0. ¿Dónde están los otros dos? La respuesta está en los *Periferial Pin Select*. Los PIC24 tienen la flexibilidad de colocar pines escenciales como los Rx/Tx del puerto serial o las interrupciones externas en cualquiera de los pines marcados con RPX. En este ejemplo colocaremos la INT1 en el pin RP14/RB14 como se muestra en el circuito. El mapeo se realiza de la siguiente manera:
```C
RPINR0bits.INT1R = 14; // INT1 <- RB14 (Tabla 10-2, pag. 108)
```
Para terminar de configurar el pin hay una última consideración. Solo hace falta configurarlo como entrada sino que hay que desactivar el canal 10 del modulo ADC que está asociado a ese mismo pin de la siguiente forma:
```C
TRISBbits.TRISB14 = 1;  // RB14 como entrada
AD1PCFGbits.PCFG10 = 1; // ADC10 dehabilitado (pag. 199)
```
Por último solo queda habilitar la interrupción:
```C
IEC1bits.INT1IE = 1;    //INT1 habilitada (pag. 74)
IPC5bits.INT1IP1 = 7;   // Prioridad máxima (pag. 32)
INTCON2bits.INT1EP = 0; // Interrupción en flanco de subida (positiva) (pag. 65)
```
