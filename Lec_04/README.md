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
