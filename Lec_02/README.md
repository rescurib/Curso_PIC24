# Lección 2: Interrupciones externas
## Concepto de interrupción 
Dada una secuencia prinpcipal de instrucciones (programa principal), una interupción es un salto hacia una secuecia especial que ocurre si un evento particualar ocurre. Este evento está definido por el tipo de interrupción. En esta lección trataremos el tipo más sencillo el cual se trata de un cambio de estado en alguno de los pines provocado por un cambio externo. 

## Ejemplo 2.1 Cambio de dirección de una secuencia de LEDs
Tenemos un serie de 8 leds con una secuencia de encedido de 1 segundo por led y debemos cambiar el sentido de la secuencia con un push-button como se muetra en el siguiente circuito:

<p align="center">
<img src="https://2.bp.blogspot.com/-pt6lpnid1_c/Xv_RUB6qq6I/AAAAAAAACV0/YB1JiDSUGlwK0t_dNpJcctjJykKqfNmjQCLcBGAsYHQ/s1600/P21.png" alt="alt text" width="850">
</p>
 
Este es un ejemplo sencillo que ejemplifica bastante bien la necesidad de las interrupciones. Hasta ahora la única forma de hacer retardos que hemos mostrado es mediante la función _\_delay_ms(). Hay otras formas (que verémos en la próxima lección), pero seguiremos usandola para este ejemplo. Esta funcíón crea un tiempo muerto en el cual el procesador del PIC pierde tiempo mientras dura el retardo elegido. Si no usamos una interrupción externa que realice el cambio de dirección tenemos el probelma de que tenemos una ventana de tiempo pequeñisima entre la ejecución de los retardos. Lo que necesitamos es que el procesador ejecute una rutina que invierta el giro en el momento que se necesite y no cuando él *pueda*.   

De acuerdo a la [guía de usuario del compilador XC16](http://ww1.microchip.com/downloads/en/DeviceDoc/MPLAB_XC16_C_Compiler_UG_52071.pdf) (Sec. 10.3.3 pag. 131), la manera que declaramos el prototipo de rutina de interrupción es la siguiente:

```C
void __attribute__((__interrupt__,__auto_psv__)) isr0(void);
```
El nombre adecuado de la rutina para la interrupción externa se puede encontrar en la ayuda del compilador:

<p align="center">
<img src="https://1.bp.blogspot.com/-IgKQzTWcTx8/XscnggvYR2I/AAAAAAAACRU/Ewt5Bepko4okUATNAumV7PU5olFs0g6gwCLcBGAsYHQ/s320/compiler_help_MPLABX.png" alt="alt text">
</p>

y ir la sección *Interrupt Vector Tables Reference* y buscar el dispositivo que se esté utilizando. En la tabla que aparece se puede encontrr el nombre *_INT0Interrupt*. La rutina completa nos queda:

```C
void __attribute__((interrupt, auto_psv)) _INT1Interrupt(void){
    if (IFS1bits.INT1IF && IEC1bits.INT1IE){
        sentido ^= 1;
        IFS1bits.INT1IF = 0;
    }
}
```
