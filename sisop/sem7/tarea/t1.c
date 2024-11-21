#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "exFATstruct.h"

int main(int argc, char *argv[]) {
    int fd, clusterNum;
    exFatBootSector boot;
    unsigned char fatEntry[4];

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

    // Mover al sector de la FAT
    lseek(fd, boot.FATOffset * (1 << boot.BytePerSector) + clusterNum * 4, SEEK_SET);

    if (read(fd, fatEntry, sizeof(fatEntry)) < 0) {
        perror("No se pudo leer la entrada de la FAT\n");
        exit(1);
    }

    // Verificar si el valor de la entrada FAT es libre o ocupado (0x00 para libre, otro valor para ocupado)
    if (fatEntry[0] == 0x00 && fatEntry[1] == 0x00 && fatEntry[2] == 0x00 && fatEntry[3] == 0x00) {
        printf("El cluster %d está libre.\n", clusterNum);
    } else {
        printf("El cluster %d está ocupado.\n", clusterNum);
    }

    close(fd);
    return 0;
}
