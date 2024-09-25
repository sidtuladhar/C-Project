#ifndef BLOCK_H
#define BLOCK_H

#include <time.h>

typedef struct Block {
    time_t timestamp;
    int index;
    char hash[65];
    char prev_hash[65];
    char data[256]; 
    int nonce;
} Block;

typedef struct Blockchain {
    Block *blocks;
    int block_count;
} Blockchain;


#endif