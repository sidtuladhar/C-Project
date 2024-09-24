#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"

typedef struct Block {
    time_t timestamp;
    int index;
    char hash[64];
    char prev_hash[64];
    char data[256]; 
    int nonce;
} Block;

void hash_block(Block *block) {
    unsigned char hash_output[32];  // 256 bits = 32 bytes for the raw output
    unsigned int output_len;

    // Concatenate block data into a string to hash (simplified for the example)
    char block_data[512];
    sprintf(block_data, "%d%ld%s%s%d", block->index, block->timestamp, block->prev_hash, block->data, block->nonce);

    // Compute the hash
    compute_hash(block_data, hash_output, &output_len);

    // Convert the raw output to a hexadecimal string and store it in block->hash
    for (int i = 0; i < output_len; i++) {
        sprintf(block->hash + (i * 2), "%02x", hash_output[i]);
    }
}

int main() {
    Block *myblock = (Block *)malloc(sizeof(Block));

    // Initialize test data for the Block
    myblock->index = 1;  // This is block #1
    myblock->timestamp = time(NULL);  // Use the current time as the timestamp
    strcpy(myblock->prev_hash, "000000000000000000000000000000000000000000000000000000000000000");  // Genesis block hash (usually all zeros)
    strcpy(myblock->data, "This is some test data for the block");  // Custom test data
    myblock->nonce = 12345;

    hash_block(myblock);

    printf("Block Index: %d\n", myblock->index);
    printf("Timestamp: %ld\n", myblock->timestamp);
    printf("Previous Hash: %s\n", myblock->prev_hash);
    printf("Data: %s\n", myblock->data);
    printf("Nonce: %d\n", myblock->nonce);
    printf("Hash: %s\n", myblock->hash);

    free(myblock);

    return 0;
}
