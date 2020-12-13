# Interrupciones por temporizador 
## Módulos de temporizador
Un temporizador es basicamente un contador. La fuente de los eventos de conteo carateriza su operación:
* **Timer** (contador de ciclos de reloj pre-escalados)
* **Contador** (contador de cambios de estado en un pin externo [TXCK])

En la familia PIC24, el temporizador TMR1 (de 16 bits) tiene la siguiente estructura:

<p align="center">
<img src="https://2.bp.blogspot.com/-C-9g_KGEqE4/XxIqOiqUJrI/AAAAAAAACXc/pOReC0jxqZMoG3ATyjy93eefWDwRQV7lwCLcBGAsYHQ/s1600/TMR1_PIC24.png" alt="alt text" width="700">
</p>

En ambos casos, el conteo es almacenado en el registro TMRx (la *x* hace referencia al número de módulo) y puede ser leido y sobre escrito en cualquier momento. La bandera TxIF se levanta (se pone en 1 lógico) si el valor del registro TMRx es igual al valor del registro PRx [*Period Register*] (a diferencia de la familia PIC18 en donde la bandera se levanta cuando TMRx se desborda). El comparador tambien resetea el valor de TMRx cuando se igualan los valores. La formula para obtener el valor de PR1 para levantar la bandera en el periodo deseado: 

<p align="center">
<img src="https://1.bp.blogspot.com/-dobHiZLPLwM/X9VbzU5YO-I/AAAAAAAACcI/hRcYBL5japUNQyHJxp4BCmhL4kIA1itGQCLcBGAsYHQ/s16000/PR1_TMRX_Int_PIC24.png">
</p>


## Interrupción por TxIF

En la leccción anterior se explicó lo que es una interrupción y se dio un ejemplo de una interrupción activada por un cambio de estado en uno de los pines. Es posible establecer una interrupción cuyo evento de activación sea el levantamiento de la bandera TxIF. Este es uno de los tipos de interrupción más utilizados ya que permite tener control determinista de la ejecución de una tarea, como lo es una rutina de un controlador digital o un administrador de tareas concurrentes. La sección 11.0 de la hoja de datos muestra todos los detalles de la operación del módulo TMR1.

Para incializar el múdulo como temporizador con interrupción habilitada:
```C
 T1CON = 0x00;           // Detiene temporizador
 T1CONbits.TCS = 0;      // Entrada por reloj interno (FCY) (pag. 150)
 T1CONbits.TCKPS = 0b00; // Prescaler 1:1  (pag. 130)
 TMR1 = 0x00;            //Limpia el regitro de temporizador
 PR1 = 333;              //Carga el periodo para una interrupción de 48 kHz
 IPC0bits.T1IP = 0x01;   //Prioridad de interrupción
 IFS0bits.T1IF = 0;      //Limpia bandera de periodo
 IEC0bits.T1IE = 1;      //Habilita la interrupción por TMR1
 T1CONbits.TON = 1;      //Inicia TMR1 
```

## Ejemplo 3.1 Generar un pulso cuadrado de 48 kHz
Vamos a escribir una rutina de interupción que togglee el estado de un pin para ser visualizado en un osciloscio. Podemos utilizar la herrmienta de analísis analógico del simulador de Proteus. En la Lección 2 se explicó que los nombres de las rutinas de interrupución se encuetran en un listado especial en la documentación del compilador XC16. Cada nombre está asociado a un tipo particular de interrupción y el hardware que la activa. En este caso, al utilizar la interrupción por TMR1 la rutina que escribiremos será la seguiente:

```C
void __attribute__((interrupt, auto_psv)) _T1Interrupt (void){
  _T1IF = 0;			// Limpiar bandera irq 
  LATBbits.LATB10 ^= 1; // Toggle del LED 
}
````
El circuito utilizado y los resultados de la simulación del programa en el microcotrolador son los siguientes:
<p align="center">
<img src="https://1.bp.blogspot.com/-rdt9ahuUFqQ/X9V9VnnwbRI/AAAAAAAACcU/OJMLMd4TB4obaJNpAsyuGONpmEue0BmTACLcBGAsYHQ/s0/Ejemplo_Interrupt_TMR_PIC24.png" alt="alt text" width="700">
</p>


