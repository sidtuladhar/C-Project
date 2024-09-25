#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "block.h"

void verify_block(Block *block) {
    hash_block(block);
    if (strcmp(block->hash, block->prev_hash) != 0) {
        printf("Block hash does not match previous hash\n");
        exit(1);
    }
}

void add_block(Blockchain *blockchain, Block *block) {
    verify_block(block);
    blockchain->blocks = (Block *)realloc(blockchain->blocks, (blockchain->block_count + 1) * sizeof(Block));
    blockchain->blocks[blockchain->block_count] = *block;
    blockchain->block_count++;
}

void hash_block(Block *block) {
    unsigned char hash_output[32];  // 256 bits = 32 bytes for the raw output
    unsigned int output_len;

    char block_data[512];
    sprintf(block_data, "%d%ld%s%s%d", block->index, block->timestamp, block->prev_hash, block->data, block->nonce);

    // Compute the hash
    compute_hash(block_data, hash_output, &output_len);

    // Convert the raw output to a hexadecimal string and store it in block->hash
    for (int i = 0; i < output_len; i++) {
        sprintf(block->hash + (i * 2), "%02x", hash_output[i]);
    }
}

void mine_block(Block *block) {
    // Simple proof-of-work: find a nonce that makes the hash start with "00000"
    while (1) {
        block->nonce++;
        hash_block(block);
        if (block->hash[0] == '0' && block->hash[1] == '0' && block->hash[2] == '0' && block->hash[3] == '0' && block->hash[4] == '0') {
            printf("Block mined! Nonce: %d\n\n", block->nonce);
            break;
        }
    }
}

int main() {
    Block *myblock = (Block *)malloc(sizeof(Block));

    // Initialize test data for the Block
    myblock->index = 1;  // This is block #1
    myblock->timestamp = time(NULL);  // Use the current time as the timestamp
    strcpy(myblock->prev_hash, "0000000000000000000000000000000000000000000000000000000000000000");  // Genesis block hash (usually all zeros)
    strcpy(myblock->data, "This is some test data for the block");  // Custom test data
    myblock->nonce = 12345;

    hash_block(myblock);
    mine_block(myblock);

    printf("Block Index: %d\n", myblock->index);
    printf("Timestamp: %ld\n", myblock->timestamp);
    printf("Previous Hash: %s\n", myblock->prev_hash);
    printf("Data: %s\n", myblock->data);
    printf("Nonce: %d\n", myblock->nonce);
    printf("Hash: %s\n", myblock->hash);

    free(myblock);

    return 0;
}
