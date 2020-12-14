# Cadenas y pantalla LCD

Una cadena de texto es un caso particualar de array. Es un array de elementos de tipo de *char*. Una condición que debe cumplir es que el final de una palabra debe estar delimitado con un caracter nulo '\0'. Ejemplo:
```C
char MiCadena[10];
MiCadena[0] = 'H';
MiCadena[1] = 'O';
MiCadena[2] = 'L';
MiCadena[3] = 'A';
MiCadena[4] = '\0';
```
Nótese que el array *MiCadena* es de 10 elementos pero sólo se han asignado 5 elementos. Aunque el resto de los elementos estén inicilizados con valores basura no represetará un problema ya que el caracter nulo indica que la palabra ha termiando en ese punto. Este detalle importante cuando se utilizan arreglos *char* como buffers de salida para funciones de manipulación o conversión de cadenas.

Otras maneras de inicializar una cadena son las siguientes:

```C
char str1[] = "Microchip"; //10 chars "Microchip\0"
 
char str2[6] = "Hola";    //6 chars "Hello\0"
 
char str3[4] = {'P', 'I', 'C', '\0'}; // Esta forma simempre requiere asigan el tamaño de array
````

## Funciones utiles de manipulación y conversión de cadenas

### Conversión
Utilizando la función *sprintf()* contenida en *stdlib.h* podemos enviar a un arreglo de *char* la versión de texto de un número más un formato opcional de texto adicional. Ls sintaxis es la siguiente (misma que [*fprintf()*](http://www.cplusplus.com/reference/cstdio/fprintf/)):
```C
int sprintf ( char* strBuf, const char * format, ... );
```
Para una conversión simple se puede usar como en este ejemplo:
```C
float pi = 3.141592653;
char buff[11];
sprintf(buff,"%.4f",pi); //.Xf -> X: cifras significativas
```

El proceso inveso se puede hacer con *sscanf()* tambien en *stdlib.h*:
```C
int sscanf(const char* s, const char* format, ...)
```
Ejemplo:
```C
char s[] = "19.35 N 125.2 W";
int items;
char NS, EW;
float lat,lon;
items = sscanf(s, "%f %c %f %c", &lat, &NS,&lon, &EW);
````

### Comparación y *match*
Para verificar si dos cadenas son iguales podemos usar la función *strncmp()* que se ecuentra en *string.h*. Esta función compara llas primers N posiciones de dos cadenas:
```C
int strncmp(const char* s1, const char* s2, size_t n)
```
Retorna 0 si las cadenas son iguales y en caso contrario retorna enteros positivos o negatiovs dependiendo de la diferecnia númerica (ascii) entre las cadenas.

Para vericar si una cadena se encuentra detro de otra (más larga) se puede utilizar *strstr()*. Esta función retorna el puntero al primer caracter de la subcadena que hizo el *match* o *NULL* en caso contrario.
```C
char* strstr(const char* s1,const char* s2)
```
Para una referencia completa para la libreria *string.h* revisar [esta documentación](http://www.netcruzer.com/nz/v202/doc/html/string_8h.html).

## Pantalla LCD
[Gilberto Pasma](https://www.youtube.com/channel/UCPPvs4M26W8A6FLp8HXDdvQ) tiene [un video](https://www.youtube.com/watch?v=pgGKlqz8hQU) excelente donde explica todos los detalles de bajo nivel sobre el funcionamiento de un display de 16x2 (sólo la primer parte es suficiente). Para el ejemplo de esta sección utilizaremos una versión modificada de la librería creada por [magkopian](https://github.com/magkopian/pic-xc8-lcd-library). Lo que me parece genial de esta librería es que permite elegir con total libertad el puerto y los pines de comunicación y control de la LCD:

```C
LCD lcd = { &PORTA, 5, 4, 0, 1, 2, 3 }; // RS->A5, EN->A4, D4->A0, D5->A1, D6->A2, D7->A3
LCD_Init(lcd);
```

## Ejemplo 4.1 Mostrar números y texto en un LCD 16x2
En este programa escribiremos el LCD dos lineas que contengan letras y desplieguen dos valores numéricos en formato *double*. El LCD estara conectado al puerto A en la siguiente configuración:
```C
#include "lcd.h"
....
LCD lcd = { &PORTB, 0, 1, 2, 3, 4, 5 }; // RS->A5, EN->A4, D4->A0, D5->A1, D6->A2, D7->A3
LCD_Init(lcd);
```
La función *LCD_Init()* se encarga de realizar las configuraciones de entrada/salida necesarias para cada pin por lo que no es necesario hacerlo manualmente. El código de la librería requiere de retardos por sofware por lo que será necesario cambiar el valor del macro para FCY si se usa una frecuencia diferente de 30 MHz (en otro caso se puede dejar como está).

La escritura en la LCD se hace de la siguiente manera:
```C
const double PI = 3.141592653;
const double E  = 2.718281828;
char buff[11];
    
__delay_ms(100);
sprintf(buff,"%.4f",PI); //.Xf -> X: cifras significativas
LCD_Set_Cursor(0,2); // Primer renglón, segunda columna
LCD_putrs("Pi = ");
LCD_Set_Cursor(0,8); // Primer renglón, octava columna
LCD_putrs(buff);
        
sprintf(buff,"%.4f",E); //.Xf -> X: cifras significativas
LCD_Set_Cursor(1,3); // Segundo renglón, tercera columna
LCD_putrs("e = ");
LCD_Set_Cursor(1,8); // Segundo renglón, octava columna
LCD_putrs(buff);    
```
El circuito utilizado y los resultados de la simulación son los siguientes:
<p align="center">
<img src="https://1.bp.blogspot.com/-Cuk_GKPoYik/X9f0lliNtOI/AAAAAAAACcs/ezGq3rlHjXsOtpNfJjKQOlvpzIGl7-OQwCLcBGAsYHQ/s0/LCD_PIC24_Library.png" alt="alt text" width="750">
</p>
