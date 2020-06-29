# Lección 1: Reloj de sistema y puertos I/O

Esta serie de microcontroladores trabajan a 3.3v lo que los hace más susceptibles al ruido si no se hace un buen conexionado. Es estrictamente necesario colocar capacitores de 0.1 uF entre cada par de pines Vdd-Vss como se muestra en la Figura 2-1 de la datasheet (yo estaré usando en este ejemplo un [PIC24FJ32GA002](http://ww1.microchip.com/downloads/en/DeviceDoc/39881e.pdf)):
<p align="center">
<img src="https://1.bp.blogspot.com/-U7qTi1OyQnA/Xscfy6lwBDI/AAAAAAAACQ8/b1U6awHRlzc-yVnJ9_K-zqCTBJmxDiZLwCLcBGAsYHQ/s1600/PIC24_Circuit.png" alt="alt text" width="540">
</p>

Si no se colocan estos capacitores el PIC tendrá un comportamiento errático debido al ruido. Usaré en este ejemplo un cristal de 8MHz con capacitores de 22pF. Una vez conectado el circuito podemos avanzar a la configuración del oscilador. Configuraremos el oscilador externo con PLL activado con la frecuencia de reloj FOSC máxima de 32 MHz (recordemos que FCY = FOSC/2). He marcado el camino que nos interesa sobre el diagrama de la Figura 8-1 de la página 95:

 Si estamos usando un cristal de 8 MHz ¿Qué modo es el adecuado? Eso lo ponemos encontrar en el [“PIC24F Family Reference Manual”,
“Oscillator” (DS39700)](http://ww1.microchip.com/downloads/en/devicedoc/39700c.pdf), tabla 6-2 de la pag. 13, el cual dice que es XT. EN el caso del GA002 si queremos usar el PLL el modo sería XTPLL. Ahora sólo necesitamos saber que bits de configuración necesitamos modificar. En la tabla 8-1 de la página 96 (del datasheet) podemos ver que son POSCMD y FNOSC. Para encontrar los macros necesarios podemos ir a Compiler Help en el dashboard de MPLAB X:

<p align="center">
<img src="https://1.bp.blogspot.com/-IgKQzTWcTx8/XscnggvYR2I/AAAAAAAACRU/Ewt5Bepko4okUATNAumV7PU5olFs0g6gwCLcBGAsYHQ/s320/compiler_help_MPLABX.png" alt="alt text">
</p>

Abrirá un archivo HTML donde debemos buscar Configuration Settings Reference. De ahí podrán copiar los pragmas requeridos. Ahora solo falta un ajuste más pero se hará escribiendo en un registro. Lo que falta es asegurarnos que FOSC tenga un frecuencia de 32 MHz. Para esto debemos revisar el registro CLKDIV (pág. 111) dónde podremos ver que el valor de división del último postcaler es de 0. Ahora tenemos toda la información necesaria para escribir nuestro programa:
