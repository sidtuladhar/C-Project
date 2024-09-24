#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Block {
    time_t timestamp;
    int index;
    char hash[64];
    char prev_hash[64];
    char data[256]; 
    int nonce;
} Block;

