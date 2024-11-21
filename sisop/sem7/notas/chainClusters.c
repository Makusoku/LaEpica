#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <math.h>
#include "exFATstruct.h"

#define SIZE 32
#define CLUSTER_END 0xFFFFFFF8 
char name[500];
int contCpy;
int clusterNumIni;


void obtenerCadenaCluster(const char *image_file,exFatBootSector boot, int first_cluster){
    int bytes_per_sector = 1 << boot.BytePerSector;
    int sectors_per_cluster = 1 << boot.SectorPerCluster;
    int fd;

    
    long fat_start = boot.FATOffset * bytes_per_sector;
    if((fd = open(image_file, O_RDONLY)) < 0){
        perror("No se pudo abrir la imagen del disco\n");
        exit(1);
    }
    int current_cluster = first_cluster;
    printf("%d",first_cluster);
    while (1) {
        // Calcular la posición en la FAT
        long fat_entry_offset = fat_start + (current_cluster * 4);

        // Mover el puntero al inicio de la entrada FAT
        if (lseek(fd, fat_entry_offset, SEEK_SET) < 0) {
            perror("Error al mover el puntero a la entrada FAT");
            exit(1);
        }

        // Leer la entrada FAT
        unsigned int next_cluster;
        if (read(fd, &next_cluster, sizeof(next_cluster)) != sizeof(next_cluster)) {
            perror("Error al leer la entrada FAT");
            exit(1);
        }

        // Mostrar el clúster actual

        // Verificar si es el fin de la cadena
        if (next_cluster == 0xFFFFFFFF || next_cluster == 0x00000000) {
            printf("\n");
            break;
        }
        else{
            printf(" -> %d",next_cluster);
        }

        // Actualizar el clúster actual
        current_cluster = next_cluster;
    }
    close(fd);
}
void continuarImpresion(const char *entry){
    int dobCero=0,i;
    for(i = 2 ;i< 32;i ++){
        if(dobCero==2) break;
        if(entry[i]!=0){
            name[contCpy] = entry[i];
            contCpy++;
            dobCero=0;
        }
        else{
            dobCero++;
        }   
    }
    name[contCpy] = '\0';
}
void printNameDirect(const char *entry){
    int dobCero=0,i;
    contCpy=0;
    for(i = 2 ;i< 32;i ++){
        if(dobCero==2) break;
        if(entry[i]!=0){
            name[contCpy] = entry[i];
            contCpy++;
            dobCero=0;
        }
        else{
            dobCero++;
        }   
    }
    name[contCpy] = '\0';
}

void readRootDir(const char *image_file){
    int fd, n1, n2;
    exFatBootSector boot;
    char entry[SIZE];

    if((fd = open(image_file, O_RDONLY)) < 0){
        perror("No se pudo abrir la imagen del disco\n");
        exit(1);
    }

    if(read(fd, &boot, sizeof(boot) ) < 0){
        perror("No se pudo leer el sector de arranque del disco\n");
        exit(1);
    }

    printf("La data inicia en el sector: %d\n", boot.ClusterHeapOffset);
    n1 = boot.BytePerSector;
    printf("El tamaño de un sector en bytes es de: %d\n", (int)pow(2.0, n1));
    n2 = boot.SectorPerCluster;
    printf("El tamaño de sectores por cluster es de: %d\n", (int)pow(2.0, n2));
    printf("El directorio raiz se encuentra en el cluster: %d\n", boot.RootDirFirstCluster);
    printf("La FAT se encuentra en el sector: %d\n", boot.FATOffset);
    printf("Tamaño de la FAT en sectores: %d\n", boot.FATlen);
    printf("Numero de FAT's en el archivo: %d\n", boot.numberFats);
    int bytes_per_sector = 1 << boot.BytePerSector;
    int sectors_per_cluster = 1 << boot.SectorPerCluster;

    long rootDirOffset = (boot.ClusterHeapOffset * bytes_per_sector)+((boot.RootDirFirstCluster-2) * bytes_per_sector * sectors_per_cluster);

    if(lseek(fd, rootDirOffset, SEEK_SET)< 0){
        perror("Error al mover el puntero del archivo al inicio del del roorDir\n");
        close(fd);
        exit(1);
    }

    //printf("Estamos en la posicion: %ld\n", rootDirOffset);
    int anterC1 = 0;
    while(read(fd, entry, SIZE) == SIZE){
        if((unsigned char)entry[0] == 0x00) break;
        if((unsigned char)entry[0] == 0xc0){
            clusterNumIni = (unsigned char)entry[20];
        }
        else if((unsigned char)entry[0] == 0xC1){
            if(anterC1 == 1){
                continuarImpresion(entry);
            }
            else{
                printNameDirect(entry);
                anterC1=1;
            }
            continue;
        }
        else if(anterC1==1){
            if(strcmp(name,"Win98.png")==0 || strcmp(name,"leeClustersFAT32.c.jpg")== 0 ){
                printf("\nArchivo %s:\n",name);
                printf("Cadena de clusteres: ");
                obtenerCadenaCluster(image_file,boot, clusterNumIni);
            }
            contCpy=0;
            memset(name,0,sizeof(name));
        }
        anterC1=0;
    }
    anterC1=0;
    close(fd);
    return;    
}



void main(int argc, char *argv[]){
    int fd;

    char *image_file = argv[1];
    
    readRootDir(image_file);

    exit(1);
}



