#ifndef BLOCK_H
#define BLOCK_H

#include <time.h>

#define HASH_SIZE 65
#define DATA_SIZE 256

typedef struct Block {
    time_t timestamp;
    int index;
    char hash[HASH_SIZE];
    char prev_hash[HASH_SIZE];
    char data[DATA_SIZE]; 
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