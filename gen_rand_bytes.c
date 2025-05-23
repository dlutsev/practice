#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <bits> <output_file>\n", argv[0]);
        return 1;
    }

    long long bits = atoll(argv[1]);
    FILE *f = fopen(argv[2], "wb");
    if (!f) {
        perror("fopen");
        return 1;
    }

    srand(time(NULL));

    long long bytes = (bits + 7) / 8;
    for (long long i = 0; i < bytes; ++i) {
        unsigned char byte = rand() & 0xFF;
        fputc(byte, f);
    }

    fclose(f);
    return 0;
}
