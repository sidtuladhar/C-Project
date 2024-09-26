#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/hash.h"
#include "../include/block.h"

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

void verify_block(Block *block) {
    hash_block(block);
    if (strcmp(block->hash, block->prev_hash) != 0) {
        printf("Block hash does not match previous hash\n");
        exit(1);
    }
}

void add_block(Blockchain *blockchain, Block *block) {
    blockchain->blocks = (Block *)realloc(blockchain->blocks, (blockchain->block_count + 1) * sizeof(Block));
    blockchain->blocks[blockchain->block_count] = *block;
    blockchain->block_count++;
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
    hash_block(block);
}
