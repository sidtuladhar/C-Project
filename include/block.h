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

void hash_block(Block *block);

void verify_block(Block *block);

void add_block(Blockchain *blockchain, Block *block);

void mine_block(Block *block);


#endif