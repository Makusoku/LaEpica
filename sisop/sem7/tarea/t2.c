#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "exFATstruct.h"

int main(int argc, char *argv[]) {
    int fd, clusterNum, bytePos, bitPos;
    exFatBootSector boot;
    unsigned char byte;

    if (argc != 3) {
        printf("Uso: %s <Image File System> <Cluster Number>\n", argv[0]);
        exit(1);
    }

    clusterNum = atoi(argv[2]);

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror("No se pudo abrir la imagen del disco\n");
        exit(1);
    }

    if (read(fd, &boot, sizeof(boot)) < 0) {
        perror("No se pudo leer la imagen del disco\n");
        exit(1);
    }

    // Calcular la posición en el mapa de bits
    bytePos = boot.ClusterHeapOffset + (clusterNum / 8);
    bitPos = clusterNum % 8;

    // Leer el byte correspondiente al cluster
    lseek(fd, bytePos * (1 << boot.BytePerSector), SEEK_SET);
    if (read(fd, &byte, sizeof(byte)) < 0) {
        perror("No se pudo leer el mapa de bits\n");
        exit(1);
    }

    // Verificar si el bit correspondiente al cluster está seteado (ocupado) o no (libre)
    if (byte & (1 << bitPos)) {
        printf("El cluster %d está ocupado.\n", clusterNum);
    } else {
        printf("El cluster %d está libre.\n", clusterNum);
    }

    close(fd);
    return 0;
}
