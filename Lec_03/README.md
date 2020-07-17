# Interrucpiones por temporizador 
## Módulos de temporizador
Un temporizador es basicamente un contador. La fuente de los eventos de conteo carateriza su operación:
* **Timer** (contador de ciclos de reloj pre-escalados)
* **Contador** (contador de cambios de estado en un pin externo [TXCK])

En la familia PIC24, el temporizador TMR1 tiene la siguiente estructura:

<p align="center">
<img src="https://2.bp.blogspot.com/-C-9g_KGEqE4/XxIqOiqUJrI/AAAAAAAACXc/pOReC0jxqZMoG3ATyjy93eefWDwRQV7lwCLcBGAsYHQ/s1600/TMR1_PIC24.png" alt="alt text" width="700">
</p>

En ambos casos, el conteo es almacenado en el registro TMRx (la *x* hace referencia al número de módulo) y puede ser leido y sobre escrito en cualquier momento. La bandera TxIF se levanta (se pone en 1 lógico) si el valor del registro TMRx es igual al valor del registro PRx [*Period Register*] (a diferencia de la familia PIC18 en donde la bandera se levanta cuando TMRx se desborda). El comparador tambien resetea el valor de TMRx cuando se igualan los valores. 

## Interrupción por periodo

En la seccción anterior se explico lo que es una interrupción y se dio un ejemplo de interrupción activada por un cambio de estado en uno de los pines. Es posible establecer una interrupción cuyo evento de activación sea el levantamiento de la bandera TxIF.
