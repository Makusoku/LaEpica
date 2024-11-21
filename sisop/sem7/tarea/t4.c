#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "exFATstruct.h"

void printNameDirect(const char *entry, char *name) {
    int i, contCpy = 0;
    for (i = 2; i < 32; i++) {
        if (entry[i] != 0) {
            name[contCpy] = entry[i];
            contCpy++;
        } else {
            break;
        }
    }
    name[contCpy] = '\0';
}

int main(int argc, char *argv[]) {
    int fd;
    exFatBootSector boot;
    char entry[32], name[500];
    int cluster, size;
    char response[3];

    if (argc != 2) {
        printf("Uso: %s <Image File System>\n", argv[0]);
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror("No se pudo abrir la imagen del disco\n");
        exit(1);
    }

    if (read(fd, &boot, sizeof(boot)) < 0) {
        perror("No se pudo leer la imagen del disco\n");
        exit(1);
    }

    // Mover al directorio raíz
    lseek(fd, boot.ClusterHeapOffset * (1 << boot.BytePerSector) + (boot.RootDirFirstCluster - 2) * (1 << boot.SectorPerCluster) * (1 << boot.BytePerSector), SEEK_SET);

    while (read(fd, entry, sizeof(entry)) == sizeof(entry)) {
        if ((unsigned char)entry[0] == 0x00) break;  // Fin de las entradas

        if ((unsigned char)entry[0] == 0xC1 || entry[0] == 0x83) {  // Entrada válida
            printNameDirect(entry, name);
            cluster = (entry[20] << 8) | entry[21];  // Primer cluster
            size = (entry[24] << 24) | (entry[25] << 16) | (entry[26] << 8) | entry[27];  // Tamaño del archivo
            printf("Nombre: %s, Tamaño: %d bytes, Primer cluster: %d\n", name, size, cluster);

            // Preguntar si desea mostrar la cadena de clusters
            printf("¿Desea mostrar la cadena de clusters? (Si/No): ");
            scanf("%s", response);

            if (response[0] == 'S' || response[0] == 's') {
                printf("Mostrando clusters...\n");
                // Mostrar los clusters asociados al archivo
                // (Aquí es necesario agregar código que lea los clusters sucesivos de la FAT)
            }
        }
    }

    close(fd);
    return 0;
}
