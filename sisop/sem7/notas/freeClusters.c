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

#define SECTOR_SIZE 512


void checkCluster(const char *image_file, int cluster_number){
    int fd, n1, n2;
    exFatBootSector boot;

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
    printf("El tamaño del volumen es : %ld\n", boot.sizeVol);

    int bytes_per_sector = 1 << boot.BytePerSector;
    int sectors_per_cluster = 1 << boot.SectorPerCluster;
    int cluster_number_cpy = cluster_number - 2;
    int byte_index = cluster_number_cpy / 8;
    int bit_index = cluster_number_cpy % 8;

    long bitmap_offset = boot.ClusterHeapOffset  + (byte_index/bytes_per_sector);

    if(lseek(fd, bitmap_offset* bytes_per_sector, SEEK_SET)< 0){
        perror("Error al mover el puntero del archivo al inicio del bitmap\n");
        close(fd);
        exit(1);
    }

    printf("Estamos en la posicion: %ld\n", bitmap_offset);

    char *bitmap = (char *)malloc(SECTOR_SIZE);
    if(read(fd, bitmap, SECTOR_SIZE) != SECTOR_SIZE){
        perror("Error al leer el bitmap");
        free(bitmap);
        close(fd);
        exit(1);
    }
    
    int isOccupied = (bitmap[byte_index] >> (bit_index)) & 1;

    if(isOccupied == 0){
        printf("El clúster %d está libre\n", cluster_number);
    }
    else{
        printf("El clúster %d está ocupado\n", cluster_number);
    }

    free(bitmap);
    close(fd);

    return;    
}

//gcc -o freeClusters freeClusters.c -lm
//./freeClusters usb20242.img 150
//./freeClusters usb20242.img 15
void main(int argc, char *argv[]){
    int fd;

    int cluster_number = atoi(argv[2]);
    char *image_file = argv[1];
    
    checkCluster(image_file, cluster_number);

    exit(1);
}
