#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "funciones.h"

int main(int argc, char const *argv[]) {
    srand(time(NULL));

    //abrimos archivo donde guardamos los datos
    FILE *archivo;
    archivo = fopen ( "fichero.txt", "a+" ); //abrimos archivo y agregamos nuevos datos
    
    //declaraciones de variables
    time_t begin,end,primero,ultimo;
    int a,x,i,N,t,Eventos,porcentajeE,comparar;
    float tprom;

    //medicion de tiempos
    begin=time(NULL);
    end=time(NULL);
    a=end-begin;

    //Inicializo valores
    x=3; //tiempo de medicion por defecto
    N=1; //contador para empezar a calcular el promedio
    i=0; //posicion inicial de los vectores
    t=9; //valor de tendencia
    DATOS[0].Temperatura=rand()%3+19; //temperatura para iniciar
    comparar=-1; //numero para que entre al while
    Eventos=-1; //numero para que entre al while
    porcentajeE=-1; //numero para que entre al while

    //Pido datos de entrada al usuario antes de entrar al loop
    while (Eventos<=0){ //tiene que ser positivo
        printf("Ingrese los eventos minimos para calcular el promedio: ");
        scanf("%d",&Eventos);
    }   
    while (porcentajeE<=0){ //tiene que ser positivo
        printf("\nIngrese el porcentaje con el que se medira la Tendencia: ");
        scanf("%d",&porcentajeE);
    }
    while (comparar>Eventos || comparar<0){
        printf("\nIngrese la cantidad de datos con los que quiere comparar la ultima temperatura para calcular el promedio.");
        printf("\nRecuerde que este valor debe ser menor o igual a los Eventos  Minimos");
        printf("\nEn caso de querer comparar con todos los datos ingrese 0: ");
        scanf("%d",&comparar);
    }

    while (1){
        if (kbhit()!=0){
            primero = time (NULL);
            getch();
            Color(DGREY,WHITE);printf("\nInicia medicion de nuevo tiempo de lectura ");
            printf("(Presione nuevamente para terminar medicion)\n");
            getch();
            ultimo = time(NULL);
            x= ultimo - primero;
            if (x<=2.5){
                printf("\nEl nuevo es menor a 2.5 segundos\n");
                Color(BLACK,WHITE);
                printf("\nFinal del programa\n");
                break;
            }
            else if (x>=10){
                x=10;
                printf("\nEl nuevo tiempo es mayor a 10 segundos ");
                printf("(Se utilizara 10 segundos como tiempo de lectura)\n");
            }
            else{
                printf("\nEl nuevo tiempo es de %d segundos\n",x);
            }
            Color(BLACK,WHITE);
        }

        end=time(NULL); //actualizo el tiempo final
        a=end-begin; //diferencia de tiempos

        if (a>=x){
            Color (BLACK,CYAN);printf("\n----- LECTURA NUMERO [%i] -----\n\n",N);
            Color (BLACK,WHITE);
            Fecha(i); //Imprime en pantalla la fecha y hora actual
            DATOS[i+1].Temperatura=Mtemperatura(DATOS[i].Temperatura); //Guardo en un vector los datos de temperatura
            printf("Temperatura medida: %.2f\n",DATOS[i].Temperatura);
            if (N>=Eventos){ //Empiezo a calcular el promedio a partir de los Eventos minimos
                tprom=0;
                if (comparar==0){
                    for(int j=0;j<i;j++){
                        tprom+=DATOS[j].Temperatura; //suma de las temperaturas
                    }
                    printf("\ntprom = %f",tprom);
                    tprom=tprom/(float)(N-1); //promedio
                }
                else {
                    for(int j=i-(comparar);j<i;j++){
                        tprom+=DATOS[j].Temperatura; //suma de las temperaturas       
                    }
                    //printf("\ntprom = %f",tprom);
                    tprom=tprom/(float)comparar;                  
                }
                  
                DATOS[i].Tendencia = Leds (tprom,DATOS[i].Temperatura,porcentajeE);
                //funcion que prende los Leds segun corresponda
                
            }else {
                Color(BLACK,RED); printf("\nLED ROJO PRENDIDO");
                Color(BLACK,YELLOW); printf("\nLED AMARILLO PRENDIDO");
                Color(BLACK, LGREEN); printf("\nLED VERDE PRENDIDO\n\n");
                Color(BLACK, WHITE); // Devolvemos el color original de la consola.
            }
            Escribir(archivo,i);   
            N++;
            i++;
            begin=time(NULL); //inicio el contador nuevamente
        }
    }
    fclose ( archivo ); 
    return 0;
}
