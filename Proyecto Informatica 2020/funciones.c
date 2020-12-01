#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "funciones.h"

struct Datos {
  char Fecha [15];
  char Hora [15];
  float Temperatura;
  short Tendencia;
};
struct Datos DATOS[1000];

enum Colors { // Listado de colores (La letra "L" al inicio, indica que es un color más claro que su antecesor).
 BLACK = 0,
 BLUE = 1,
 GREEN = 2,
 CYAN = 3,
 RED = 4,
 MAGENTA = 5,
 YELLOW = 6,
 LGREY = 7,
 DGREY = 8,
 LBLUE = 9,
 LGREEN = 10,
 LCYAN = 11,
 LRED = 12,
 LMAGENTA = 13,
 LYELLOW = 14,
 WHITE = 15
};

void Color (int Background, int Text){ // Función para cambiar el color del fondo y/o pantalla
  HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE); // Tomamos la consola.
  // Para cambiar el color, se utilizan números desde el 0 hasta el 255.
  // Pero, para convertir los colores a un valor adecuado, se realiza el siguiente cálculo.
  int    New_Color= Text + (Background * 16);
  SetConsoleTextAttribute(Console, New_Color); // Guardamos los cambios en la Consola.
}

float Mtemperatura(float tempAnterior){ //funcion que varia la temperatura
  float t,temper;
  t = ((float)rand()/(float)(RAND_MAX))*2; //numeros aleatorios de 0 a 2
  if (t<1){
    temper= tempAnterior -t;
  }
  else if(t>1){
    temper= tempAnterior + t -1;
  }
  else {
    temper=tempAnterior;
  }
  return temper; 
}

short Leds (float promedio,float temperatura, int Porcentaje){
    float porc5,resultado;
    porc5=(Porcentaje/(float)100)*promedio; //% del promedio
    resultado=temperatura-promedio;
    printf("\nPromedio de temperaturas: %.2f\n",promedio);
    if (resultado>porc5){
        Color(BLACK,RED); printf("\nTEMPERATURA CON TENDENCIA ALTA\n\n");
        Color(BLACK, WHITE); // Devolvemos el color original de la consola.
        return 1;
    }
    else if (resultado< -porc5){
        Color(BLACK, LGREEN);printf("\nTEMPERATURA CON TENDENCIA BAJA\n\n");
        Color(BLACK, WHITE); // Devolvemos el color original de la consola.
        return 2;
    }
    else {
        Color (BLACK,YELLOW);printf("\nTEMPERATURA ESTABLE\n\n");
       Color(BLACK, WHITE); // Devolvemos el color original de la consola.
       return 3;
    }
    return 9;
}

void Fecha (int i) {
  time_t tempo;
  tempo = time(NULL);
  struct tm *tlocal = localtime(&tempo);
  strftime(DATOS[i].Fecha,15,"%d/%m/%Y",tlocal);
  strftime(DATOS[i].Hora,15,"%H:%M:%S",tlocal);
  printf("Fecha: %s -- Hora: %s\n",DATOS[i].Fecha, DATOS[i].Hora);
}

void Escribir ( FILE *archivo, int i){

  if (DATOS[i].Tendencia==1) {
    fprintf(archivo,"%s %s %.2f alta\n",DATOS[i].Fecha,DATOS[i].Hora ,DATOS[i].Temperatura);
  }
  else if(DATOS[i].Tendencia==2){
    fprintf(archivo,"%s %s %.2f baja\n",DATOS[i].Fecha,DATOS[i].Hora ,DATOS[i].Temperatura);
  }
  else if(DATOS[i].Tendencia==3) {
    fprintf(archivo,"%s %s %.2f estable\n",DATOS[i].Fecha,DATOS[i].Hora ,DATOS[i].Temperatura);
  }
  else {
    fprintf(archivo,"%s %s %.2f sin\n",DATOS[i].Fecha,DATOS[i].Hora ,DATOS[i].Temperatura);
  }
}