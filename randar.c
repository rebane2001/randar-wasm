#include <stdio.h>
#include <math.h>
#include <emscripten/emscripten.h>

long long WORLD_SEED = -4172144997902289642LL;

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN EMSCRIPTEN_KEEPALIVE int crackItemDropCoordinate(double dropX, double dropY, double dropZ) {
    float spawnX = ((float) (dropX - (int) floor(dropX) - ((double)0.25))) * 2;
    float spawnY = ((float) (dropY - (int) floor(dropY) - ((double)0.25))) * 2;
    float spawnZ = ((float) (dropZ - (int) floor(dropZ) - ((double)0.25))) * 2;
    if (spawnX <= 0 || spawnX >= 1 || spawnY <= 0 || spawnY >= 1 || spawnZ <= 0 || spawnZ >= 1) {
        //printf("Skipping this item because its coordinates are out of bounds. This probably means that the item only coincidentally looked like an item that was dropped from mining a block. Other ways to drop items (e.g. dropping from a player's inventory) can sometimes cause false positives like this.\n");
        return 1;
    }
    int measurement1 = (int) (spawnX * (1 << 24));
    int measurement2 = (int) (spawnY * (1 << 24));
    int measurement3 = (int) (spawnZ * (1 << 24));
    long long cubeCenterX = ((long long) measurement1 << 24) + 8388608L;
    long long cubeCenterY = ((long long) measurement2 << 24) + 8388597L;
    long long cubeCenterZ = ((long long) measurement3 << 24) - 277355554490L;
    double basisCoeff0 = 9.555378710501827E-11 * cubeCenterX + -2.5481838861196593E-10 * cubeCenterY + 1.184083942007419E-10 * cubeCenterZ;
    double basisCoeff1 = -1.2602185961441137E-10 * cubeCenterX + 6.980727107475104E-11 * cubeCenterY + 1.5362999761237006E-10 * cubeCenterZ;
    double basisCoeff2 = -1.5485213111787743E-10 * cubeCenterX + -1.2997958265259513E-10 * cubeCenterY + -5.6285642813236336E-11 * cubeCenterZ;
    long long seed = (long long) (round(basisCoeff0) * 1270789291L + round(basisCoeff1) * -2355713969L + round(basisCoeff2) * -3756485696L) & 281474976710655L;
    long long next = seed * 25214903917L + 11L & 281474976710655L;
    long long nextNext = next * 25214903917L + 11L & 281474976710655L;
    if ((seed >> 24 ^ measurement1 | next >> 24 ^ measurement2 | nextNext >> 24 ^ measurement3) != 0L) {
        //printf("Failed to crack the seed. This probably means that the item only coincidentally looked like an item that was dropped from mining a block. Other ways to drop items (e.g. dropping from a player's inventory) can sometimes cause false positives like this.\n");
        return 2;
    }
    long long origSeed = seed;
    for (int i = 0; i < 5000; i++) {
        for (int x = -23440; x <= 23440; x++) {
            long long z = (((seed ^ 25214903917L) - WORLD_SEED - 10387319 - x * 341873128712L) * 211541297333629L) << 16 >> 16;
            if (z >= -23440 && z <= 23440) {
                // printf("Item drop appeared at %f %f %f\n", dropX, dropY, dropZ);
                // printf("RNG measurements are therefore %d %d %d\n", measurement1, measurement2, measurement3);
                // printf("This indicates the java.util.Random internal seed must have been %lld\n", origSeed);
                // printf("Found a woodland match at woodland region %d %lld which would have set the seed to %lld\n", x, z, seed);
                // printf("Located someone between %d,%d and %d,%d\n", (int)(x * 1280 - 128), (int)(z * 1280 - 128), (int)(x * 1280 + 1151), (int)(z * 1280 + 1151));
                printf("c%d,%d\n", (int)(x), (int)(z));
                return 0;
            }
        }
        seed = (seed * 246154705703781L + 107048004364969L) & 281474976710655L;
    }
    //printf("Failed to crack. This probably means that your world seed is incorrect, or there were no chunk loads recently.\n");
    return 3;
}

int main() {
    return 0;
}
