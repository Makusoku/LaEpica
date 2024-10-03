#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Colocar el prototipo del calling conventions
extern void statPokeASM (double* finalStats,double* baseStats,double* instructionValues,double* NTVs,int numPoke);
void statPokeC(double* finalStats,double* baseStats,double* instructionValues,double* NTVs,int numPoke);
void fillArrays(double* baseStats,double* instructionValues, double* NTVs, int numPoke);
void printArray(char str[],double* array,int lenArray);

int main(int argc, char **argv){
    srandom(time(NULL));
    struct timespec ti, tf;
    double elapsed1;
    double *finalStats, *baseStats, *instructionValues, *NTVs;
    int numPoke;
    printf("Ingrese la cantidad de pokemones: ");
    scanf("%d",&numPoke);
    finalStats = malloc((numPoke)*sizeof(double));
    baseStats = malloc((numPoke)*sizeof(double));
    instructionValues = malloc((numPoke)*sizeof(double));
    NTVs = malloc((numPoke)*sizeof(double));
    fillArrays(baseStats,instructionValues,NTVs,numPoke);   
    printArray("BaseStats:         ",baseStats,numPoke);
    printArray("InstructionValues: ",instructionValues,numPoke);
    printArray("NTVs:              ",NTVs,numPoke);

    clock_gettime(CLOCK_REALTIME, &ti);
    statPokeC(finalStats,baseStats,instructionValues,NTVs,numPoke);
    clock_gettime(CLOCK_REALTIME, &tf);
    elapsed1 = (tf.tv_sec - ti.tv_sec) * 1e9 + (tf.tv_nsec - ti.tv_nsec);
    printArray("FinalStats C:      ",finalStats,numPoke);

    //Codigo de statPokeASM
    
    printf("El tiempo en milisegundos que toma la funcion en C es %.2lfns\n",elapsed1);
    printArray("Arreglo de c: ", finalStats, numPoke);

    printf("\n\n");
    

    clock_gettime(CLOCK_REALTIME, &ti);
    statPokeASM(finalStats,baseStats,instructionValues,NTVs,numPoke);
    clock_gettime(CLOCK_REALTIME, &tf);
    elapsed1 = (tf.tv_sec - ti.tv_sec) * 1e9 + (tf.tv_nsec - ti.tv_nsec);
    
    printf("El tiempo en milisegundos que toma la funcion en ASM es %.2lfns\n",elapsed1);
    printArray("Arreglo de ASM: ", finalStats, numPoke);
    return 0;
}

void statPokeC(double* finalStats,double* baseStats,double* instructionValues,double* NTVs,int numPoke){
    for(int i=0;i<numPoke;i++){
        finalStats[i] = 5 + (baseStats[i] * 2 + instructionValues[i] * 4) + NTVs[i];
    }
}

void fillArrays(double* baseStats,double* instructionValues, double* NTVs, int numPoke){
    for(int i=0;i<numPoke;i++){
        baseStats[i] = (double)rand()/RAND_MAX*245.0+10.0;
        instructionValues[i] = (double)rand()/RAND_MAX*10.0;
        NTVs[i] = (double)rand()/RAND_MAX*10.0+1.0;
    }
}

void printArray(char str[],double* array,int lenArray){
    printf("%s", str);
    for(int i=0;i<lenArray;i++){
        printf("%.4lf ",array[i]);
    }
    printf("\n");
}