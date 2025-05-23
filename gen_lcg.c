#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define A 1664525
#define C 1013904223

uint32_t lcg(uint32_t *state) {
    *state = (*state * A + C);
    return *state;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <bits> <output_file>\n", argv[0]);
        return 1;
    }

    long long bits = atoll(argv[1]);
    FILE *f = fopen(argv[2], "wb");
    if (!f) return 1;

    uint32_t s1 = 1, s2 = 123456;
    int byte = 0, count = 0;

    for (long long i = 0; i < bits; ++i) {
        uint32_t r1 = lcg(&s1);
        uint32_t r2 = lcg(&s2);
        int bit = ((r1 >> 1) ^ (r2 >> 2)) & 1;
        byte = (byte << 1) | bit;
        count++;
        if (count == 8) {
            fputc(byte, f);
            count = 0;
            byte = 0;
        }
    }
    if (count > 0) {
        byte <<= (8 - count);
        fputc(byte, f);
    }

    fclose(f);
    return 0;
}
