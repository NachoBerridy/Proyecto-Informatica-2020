#include <stdio.h>
#include <stdlib.h>
#include <math.h>
    
struct Datos {
    char Fecha [15];
    char Hora [15];
    float Temperatura;
    char Tendencia[15];
};
typedef struct Datos datos;
struct Datos DATOS[1000];

//struct Datos DATOS2[1000];
int main(int argc, char const *argv[])
{
	FILE *archivo;
    datos datAuxiliar;
	char caracter;
    char temperaturas[8];
    int i,j,cont,modas,h;
	int min,mediana1,mediana2,moda1,modmax;
    float media,mediana;
    double CV;
    int MODA[1000];
    for (i=0;i<1000;i++){
        MODA[i]=0;
    }

	i=0;
    j=0;
    cont=1;
    modas=0;
    min=0;
    moda1=0;
    modmax=0;
    CV=0;
    media=0;
	archivo = fopen("fichero.txt","r");
    
    if (archivo == NULL){
        printf("\nError de apertura del archivo. \n\n");
    }
    else{
        while ((caracter = fgetc(archivo)) != EOF){
            if (caracter=='\n'){
                cont++;
            }
        }
    }

    //printf("el contador es %d \n",cont);
    fclose(archivo); 
    archivo = fopen("fichero.txt","r");
    //struct Datos* DATOS=(struct Datos*)malloc(sizeof(struct Datos)*cont);
	
    if (archivo == NULL){
        printf("\nError de apertura del archivo. \n\n");
    }
    else{
        printf("\n --------LOS DATOS DEL ARCHIVO SON:--------\n");
        while ((caracter = fgetc(archivo)) != EOF){
            DATOS[j].Fecha[0]=caracter;
            i=1;
            while((caracter = fgetc(archivo)) != ' '){
                DATOS[j].Fecha[i]=caracter;
                i++;
            }
            i=0;
            while((caracter = fgetc(archivo)) != ' ')//fgetc lee de donde quedo el fgetc desde donde quedo el anterior
            {
                DATOS[j].Hora[i]=caracter;
                i++;
            }
            i=0;
            while((caracter = fgetc(archivo)) != ' ')
            {
                temperaturas[i]=caracter;
                i++;
            }
            DATOS[j].Temperatura=atof(temperaturas);
            i=0;
            while((caracter = fgetc(archivo)) != '\n')
            { 
                DATOS[j].Tendencia[i]=caracter;
                i++;
            }
            i=0;
            printf("%s %s %.2f %s\n",DATOS[j].Fecha,DATOS[j].Hora,DATOS[j].Temperatura,DATOS[j].Tendencia);                                 
            j++;
        }
    }

    for(i=0;i<cont-1;i++){
        media+=DATOS[i].Temperatura;
    }

    media=media/(float)(cont-1);
    //printf("\n\n---------DATOS ORDENADOS DE MANERA ASCENDENTE------\n");
    for (i = 0; i < cont-1; i++){
        for (j = i+1; j < cont-1 ;j++){
            if(DATOS[i].Temperatura>DATOS[j].Temperatura){
                datAuxiliar = DATOS[i];
                DATOS[i]=DATOS[j];
                DATOS[j]=datAuxiliar;
            }    
        } 
    }

    /*for (i=0; i<cont-1;i++){
        printf("%s %s %.2f %s\n",DATOS[i].Fecha,DATOS[i].Hora,DATOS[i].Temperatura,DATOS[i].Tendencia);
    }*/
    if((cont)%2==0){
        mediana1=((cont-1)/2);
        mediana=DATOS[mediana1].Temperatura;
    }
    else{
        mediana1=(((cont-1)/2))-1; 
        mediana2=((cont-1)/2);
        mediana=(DATOS[mediana1].Temperatura+DATOS[mediana2].Temperatura)/(float)2;
    }
    h=0;
    for (i=0; i<cont-1; i++){
        for (j=h;j<cont-1;j++){
            if (DATOS[i].Temperatura==DATOS[j].Temperatura && i!=j){ 
                moda1++;
            }
        }
        MODA[i]=moda1;
        moda1=1;
        h++;
    }
    
    for (i=1;i<cont-1;i++){
        if(MODA[i]>MODA[modmax]){
            modmax=i;
        }
    }
    for(i=0;i<cont-1;i++){
        if(MODA[i]==MODA[modmax]){
            modas++;
        }
    }
    //printf("Hay %i modas\n",modas);
    for (size_t i = 0; i < cont-1; i++){
        CV+=pow((DATOS[i].Temperatura-media),2);
    }
        CV=(sqrt(CV/(cont-1)))/(double)media;
        printf("\n");
        printf("La media es: %.2f\n",media);
        printf("La mediana es: %.2f\n",mediana);
        for (i=0;i<cont-1;i++){
            if(MODA[modmax]!=1 && MODA[modmax]!=(cont-1)/modas){ //cuando todo los valores se repiten 
                if (MODA[i]==MODA[modmax]){
                printf("la moda es: %.2f \n",DATOS[i].Temperatura);
                }
            }
        }
        if(MODA[modmax]==1 || MODA[modmax]==(cont-1)/modas){
            printf("No hay moda\n");
        }
        printf("el coeficiente de variacion VC=%.3f \n",CV);
        printf("La temperatura minima fue: %.2f y se registro el dia %s a las %s\n",DATOS[0].Temperatura,DATOS[0].Fecha,DATOS[0].Hora);
        printf("La temperatura maxima fue: %.2f y se registro el dia %s a las %s\n",DATOS[cont-2].Temperatura,DATOS[cont-2].Fecha,DATOS[cont-2].Hora);
        fclose(archivo);
    return 0;
}
